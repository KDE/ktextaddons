/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessagesmodel.h"
#include "core/textautogeneratesearchmessagesettings.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
#include <QDateTime>
#include <QJsonObject>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginManager>
#include <TextUtils/TextUtilsCopyBlockIconCache>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateMessagesModel::TextAutoGenerateMessagesModel(QObject *parent)
    : QAbstractListModel{parent}
    , mSearchMessageSettings(new TextAutoGenerateSearchMessageSettings(this, this))
{
}

TextAutoGenerateMessagesModel::~TextAutoGenerateMessagesModel() = default;

int TextAutoGenerateMessagesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mMessages.count();
}

QVariant TextAutoGenerateMessagesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mMessages.count()) {
        return {};
    }
    const auto &messageElement = mMessages[index.row()];
    switch (role) {
    case MessagePointer:
        return QVariant::fromValue(&messageElement);
    case Qt::DisplayRole:
    case MessageHtmlGeneratedRole:
        return messageElement.htmlGenerated();
    case OriginalMessageRole:
        return messageElement.content();
    case DateTimeStrRole:
        return messageElement.dateTimeStr();
    case DateTimeRole:
        return messageElement.dateTime();
    case SenderRole:
        return QVariant::fromValue(messageElement.sender());
    case FinishedRole:
        return !messageElement.inProgress();
    case UuidRole:
        return messageElement.uuid();
    case MouseHoverRole:
        return messageElement.mouseHover();
    case EditingRole:
        return messageElement.editingMode();
    case WaitingAnswerRole:
        return waitingAnswer(messageElement);
    case ModelInfoRole:
        return generateModelInfo(messageElement);
    case ToolsRole:
        return QVariant::fromValue(messageElement.tools());
    case AnswerUuidRole:
        return messageElement.answerUuid();
    case TextToSpeechInProgressRole:
        return messageElement.textToSpeechInProgress();
    default:
        break;
    }
    return {};
}

QString TextAutoGenerateMessagesModel::generateModelInfo(const TextAutoGenerateMessage &m) const
{
    if (m.engineName().isEmpty() && m.modelName().isEmpty()) {
        return {};
    }
    QString toolTip = u"<qt>"_s + i18n("<b>Engine:</b> %1<br><b>Model:</b> %2<br><b>Instance Name:</b> %3", m.engineName(), m.modelName(), m.instanceName());
    if (m.messageInfo() && !m.messageInfo()->tools().isEmpty()) {
        const QString displayList =
            u"<ul>"_s + TextAutoGenerateText::TextAutoGenerateTextToolPluginManager::self()->convertIdentifierToDisplay(m.messageInfo()->tools()) + u"</ul>"_s;
        toolTip += i18n("<br><b>Tools:</b> %1", displayList);
    }
    if (const auto replyInfo = m.info(); replyInfo.isValid()) {
        if (const QString replyInfoToolTip = replyInfo.generateReplyInfo(); !replyInfoToolTip.isEmpty()) {
            toolTip += replyInfoToolTip;
        }
    }
    return toolTip + u"</qt>"_s;
}

QString TextAutoGenerateMessagesModel::searchText() const
{
    return mSearchText;
}

int TextAutoGenerateMessagesModel::setSearchText(const QString &newSearchText)
{
    int numberOfSearchStringFound = 0;
    if (mSearchText != newSearchText) {
        mSearchText = newSearchText;
        numberOfSearchStringFound = updateAllGeneratedMessages();
    }
    return numberOfSearchStringFound;
}

bool TextAutoGenerateMessagesModel::isEmpty() const
{
    return mMessages.isEmpty();
}

void TextAutoGenerateMessagesModel::regenerateHtmlMessage(const QByteArray &identifier, int index)
{
    if (auto it = findMessage(identifier); it != mMessages.end()) {
        (*it).generateHtml(searchText(), index);
        const int i = std::distance(mMessages.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {MessageHtmlGeneratedRole});
    }
}

int TextAutoGenerateMessagesModel::updateAllGeneratedMessages()
{
    int numberOfSearchStringFound = 0;
    beginResetModel();
    for (auto &m : mMessages) {
        m.generateHtml(mSearchText);
        numberOfSearchStringFound += m.numberOfTextSearched();
    }
    endResetModel();
    mSearchMessageSettings->setFoundSearchCount(numberOfSearchStringFound);
    return numberOfSearchStringFound;
}

TextAutoGenerateSearchMessageSettings *TextAutoGenerateMessagesModel::searchMessageSettings() const
{
    return mSearchMessageSettings;
}

QByteArray TextAutoGenerateMessagesModel::chatId() const
{
    return mChatId;
}

void TextAutoGenerateMessagesModel::setChatId(const QByteArray &newChatId)
{
    mChatId = newChatId;
}

QByteArray TextAutoGenerateMessagesModel::lastMessageUuid() const
{
    if (mMessages.isEmpty()) {
        return {};
    }
    if (const auto lastMessage = mMessages.constLast(); lastMessage.isValid()) {
        return lastMessage.uuid();
    }
    return {};
}

void TextAutoGenerateMessagesModel::refreshMessageColors()
{
    TextUtils::TextUtilsCopyBlockIconCache::self()->clear();
    (void)updateAllGeneratedMessages();
}

QList<TextAutoGenerateMessage> TextAutoGenerateMessagesModel::messages() const
{
    return mMessages;
}

void TextAutoGenerateMessagesModel::setMessages(const QList<TextAutoGenerateMessage> &newMessages)
{
    beginResetModel();
    mMessages = newMessages;
    endResetModel();
}

TextAutoGenerateMessage TextAutoGenerateMessagesModel::message(const QByteArray &uuid) const
{
    if (uuid.isEmpty()) {
        return {};
    }
    auto it = findMessage(uuid);
    if (it == mMessages.end()) {
        return {};
    }
    return *it;
}

QModelIndex TextAutoGenerateMessagesModel::refreshAnswer(const QByteArray &uuid) const
{
    if (uuid.isEmpty()) {
        return {};
    }
    auto it = findMessageByAnswerUuid(uuid);
    if (it == mMessages.end()) {
        return {};
    }
    const QModelIndex idx = createIndex(std::distance(mMessages.cbegin(), it), 0);
    return idx;
}

void TextAutoGenerateMessagesModel::resetConversation()
{
    beginResetModel();
    mMessages.clear();
    endResetModel();
    Q_EMIT conversationCleared();
}

void TextAutoGenerateMessagesModel::addMessage(const TextAutoGenerateMessage &msg)
{
    beginInsertRows(QModelIndex(), mMessages.count(), mMessages.count());
    mMessages.append(msg);
    if (msg.sender() == TextAutoGenerateMessage::Sender::Assistant) {
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(mMessages.count() - 1, {FinishedRole});
    }
    endInsertRows();
}

QByteArray TextAutoGenerateMessagesModel::editMessage(const QByteArray &uuid, const QString &str)
{
    if (uuid.isEmpty()) {
        return {};
    }
    if (const auto it = findMessage(uuid); it != mMessages.end()) {
        const int i = std::distance(mMessages.begin(), it);
        const QByteArray answerUuid = it->answerUuid();

        (*it).setContent(str);
        (*it).generateHtml();
        // Update date time
        const auto dt = QDateTime::currentSecsSinceEpoch();
        (*it).setDateTime(dt);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {MessageHtmlGeneratedRole});

        if (const auto answerIt = findMessage(answerUuid); answerIt != mMessages.end()) {
            const int idx = std::distance(mMessages.begin(), answerIt);
            (*answerIt).setInProgress(true);
            (*answerIt).setContent({});
            (*answerIt).setDateTime(dt);
            (*answerIt).generateHtml();
            emitChanged(idx, {MessageHtmlGeneratedRole, FinishedRole});
        }
        return answerUuid;
    }
    return {};
}

void TextAutoGenerateMessagesModel::changeInProgress(const QByteArray &uuid, bool inProgress)
{
    if (uuid.isEmpty()) {
        return;
    }
    if (auto it = findMessage(uuid); it != mMessages.end()) {
        (*it).setInProgress(inProgress);
        const int i = std::distance(mMessages.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {MessageHtmlGeneratedRole, FinishedRole});
    }
}

bool TextAutoGenerateMessagesModel::waitingAnswer(const TextAutoGenerateMessage &message) const
{
    const QByteArray answerUuid = message.answerUuid();
    if (answerUuid.isEmpty()) {
        return false;
    }
    if (const auto answerIt = findMessage(answerUuid); answerIt != mMessages.end()) {
        return (*answerIt).inProgress();
    }
    return false;
}

void TextAutoGenerateMessagesModel::updateMessageInfo(const QByteArray &uuid, const TextAutoGenerateAnswerInfo &messageInfo)
{
    if (uuid.isEmpty()) {
        return;
    }
    if (auto it = findMessage(uuid); it != mMessages.end()) {
        (*it).setMessageInfo(messageInfo);
        const int i = std::distance(mMessages.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {ModelInfoRole});
    }
}

void TextAutoGenerateMessagesModel::replaceContent(const QByteArray &uuid,
                                                   const TextAutoGenerateText::TextAutoGenerateReply::Response &content,
                                                   const QList<TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachementInfoList)
{
    if (uuid.isEmpty()) {
        return;
    }
    if (auto it = findMessage(uuid); it != mMessages.end()) {
        if (!content.response.isEmpty()) {
            (*it).setContent(content.response);
        } else if (!content.thinking.isEmpty()) {
            (*it).setContent(content.thinking);
        }
        if (content.replyInfo.isValid()) {
            (*it).setInfo(content.replyInfo);
        }
        (*it).generateHtml();
        TextAutoGenerateAttachments attachments;
        attachments.setMessageAttachments(TextAutoGenerateAttachmentUtils::generateAttachmentFromAttachmentElementInfos(attachementInfoList));
        (*it).setMessageAttachments(attachments);
        const int i = std::distance(mMessages.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {MessageHtmlGeneratedRole});
    }
}

QList<QByteArray> TextAutoGenerateMessagesModel::removeDiscussion(const QByteArray &uuid)
{
    if (uuid.isEmpty()) {
        return {};
    }
    const auto it = findMessage(uuid);
    QList<QByteArray> lst;
    if (it != mMessages.end()) {
        const int i = std::distance(mMessages.begin(), it);
        beginRemoveRows(QModelIndex(), i, mMessages.count() - 1);
        for (int j = mMessages.count() - 1; j >= i; --j) {
            auto m = mMessages.takeAt(j);
            lst.append(m.uuid());
        }
        endRemoveRows();
    }
    return lst;
}

void TextAutoGenerateMessagesModel::changeTextToSpeechInProgress(const QByteArray &uuid, bool inProgress)
{
    if (uuid.isEmpty()) {
        return;
    }
    if (auto it = findMessage(uuid); it != mMessages.end()) {
        (*it).setTextToSpeechInProgress(inProgress);
        const int i = std::distance(mMessages.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {TextToSpeechInProgressRole});
    }
}

bool TextAutoGenerateMessagesModel::cancelRequest(const QModelIndex &index)
{
    return setData(index, false, TextAutoGenerateMessagesModel::FinishedRole);
}

bool TextAutoGenerateMessagesModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "ERROR: invalid index";
        return false;
    }
    const int id = idx.row();
    TextAutoGenerateMessage &msg = mMessages[id];
    switch (role) {
    case MessageRoles::MouseHoverRole:
        msg.setMouseHover(value.toBool());
        Q_EMIT dataChanged(idx, idx, {MessageRoles::MouseHoverRole});
        return true;
    case MessageRoles::EditingRole:
        msg.setEditingMode(value.toBool());
        Q_EMIT dataChanged(idx, idx, {MessageRoles::EditingRole});
        return true;
    case MessageRoles::FinishedRole:
        msg.setInProgress(value.toBool());
        Q_EMIT dataChanged(idx, idx, {MessageRoles::FinishedRole});
        return true;
    case MessageRoles::TextToSpeechInProgressRole:
        msg.setInProgress(value.toBool());
        Q_EMIT dataChanged(idx, idx, {MessageRoles::TextToSpeechInProgressRole});
        return true;
    case MessageRoles::MessageHtmlGeneratedRole:
    case MessageRoles::SenderRole:
    case MessageRoles::DateTimeRole:
    case MessageRoles::UuidRole:
    case MessageRoles::WaitingAnswerRole:
    case MessageRoles::ModelInfoRole:
    case MessageRoles::OriginalMessageRole:
        return false;
    default:
        break;
    }
    return QAbstractListModel::setData(idx, value, role);
}

QModelIndex TextAutoGenerateMessagesModel::indexForUuid(const QByteArray &uuid) const
{
    auto it = findMessage(uuid);
    if (it == mMessages.cend()) {
        return {};
    }
    const QModelIndex idx = createIndex(std::distance(mMessages.cbegin(), it), 0);
    return idx;
}

QList<QJsonObject> TextAutoGenerateMessagesModel::convertToOllamaChat(bool hasSystemMessageSupport, bool hasTextOnlySupport) const
{
    QList<QJsonObject> lst;
    lst.reserve(mMessages.count());
    for (const auto &msg : mMessages) {
        if (const auto obj = msg.convertToOllamaChatJson(hasSystemMessageSupport, hasTextOnlySupport); !obj.isEmpty()) {
            lst.append(obj);
        }
    }
    return lst;
}

TextAutoGenerateMessage TextAutoGenerateMessagesModel::findLastMessageBefore(const QByteArray &messageId,
                                                                             const std::function<bool(const TextAutoGenerateMessage &)> &predicate) const
{
    auto it = findMessage(messageId); // if it == end, we'll start from there
    auto rit = QList<TextAutoGenerateMessage>::const_reverse_iterator(it); // this points to *it-1 already
    rit = std::find_if(rit, mMessages.rend(), predicate);
    return rit == mMessages.rend() ? TextAutoGenerateMessage() : *rit;
}

TextAutoGenerateMessage TextAutoGenerateMessagesModel::findNextMessageAfter(const QByteArray &messageId,
                                                                            const std::function<bool(const TextAutoGenerateMessage &)> &predicate) const
{
    auto it = findMessage(messageId);
    if (it == mMessages.end()) {
        return TextAutoGenerateMessage(); // no wrap around, otherwise Alt+Key_Up would edit the oldest msg right away
    } else {
        ++it;
    }
    it = std::find_if(it, mMessages.end(), predicate);
    return it == mMessages.end() ? TextAutoGenerateMessage() : *it;
}

// Messages are appended in chronological order and lookups overwhelmingly target the most recent
// ones -- while a reply streams in, every chunk received updates the message being written, which
// is the last one. Scanning backwards makes that common case O(1) instead of walking the whole
// conversation on each chunk. Uuids are unique, so the match found is the same either way.
QList<TextAutoGenerateMessage>::iterator TextAutoGenerateMessagesModel::findMessage(const QByteArray &messageId)
{
    const auto rit = std::find_if(mMessages.rbegin(), mMessages.rend(), [&messageId](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == messageId;
    });
    return rit == mMessages.rend() ? mMessages.end() : std::prev(rit.base());
}

QList<TextAutoGenerateMessage>::const_iterator TextAutoGenerateMessagesModel::findMessage(const QByteArray &messageId) const
{
    const auto rit = std::find_if(mMessages.crbegin(), mMessages.crend(), [&messageId](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == messageId;
    });
    return rit == mMessages.crend() ? mMessages.cend() : std::prev(rit.base());
}

QList<TextAutoGenerateMessage>::const_iterator TextAutoGenerateMessagesModel::findMessageByAnswerUuid(const QByteArray &answerUuid) const
{
    const auto rit = std::find_if(mMessages.crbegin(), mMessages.crend(), [&answerUuid](const TextAutoGenerateMessage &msg) {
        return msg.answerUuid() == answerUuid;
    });
    return rit == mMessages.crend() ? mMessages.cend() : std::prev(rit.base());
}

#include "moc_textautogeneratemessagesmodel.cpp"
