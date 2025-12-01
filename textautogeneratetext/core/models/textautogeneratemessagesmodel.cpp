/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == identifier;
    };
    auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
    if (it != mMessages.end()) {
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
    const auto lastMessage = mMessages.constLast();
    if (lastMessage.isValid()) {
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
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == uuid;
    };
    auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
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
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.answerUuid() == uuid;
    };
    auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
    if (it == mMessages.end()) {
        return {};
    }
    const QModelIndex idx = createIndex(std::distance(mMessages.begin(), it), 0);
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
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == uuid;
    };
    const auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
    if (it != mMessages.end()) {
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

        auto matchesAnswerUuid = [&](const TextAutoGenerateMessage &msg) {
            return msg.uuid() == answerUuid;
        };
        const auto answerIt = std::find_if(mMessages.begin(), mMessages.end(), matchesAnswerUuid);
        if (answerIt != mMessages.end()) {
            const int idx = std::distance(mMessages.begin(), answerIt);
            (*answerIt).setInProgress(true);
            (*answerIt).setContent({});
            (*answerIt).setDateTime(dt);
            (*answerIt).generateHtml();
            emitChanged(idx, {MessageHtmlGeneratedRole | FinishedRole});
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
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == uuid;
    };
    auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
    if (it != mMessages.end()) {
        (*it).setInProgress(inProgress);
        const int i = std::distance(mMessages.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {MessageHtmlGeneratedRole | FinishedRole});
    }
}

bool TextAutoGenerateMessagesModel::waitingAnswer(const TextAutoGenerateMessage &message) const
{
    const QByteArray answerUuid = message.answerUuid();
    if (answerUuid.isEmpty()) {
        return false;
    }
    auto matchesAnswerUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == answerUuid;
    };
    const auto answerIt = std::find_if(mMessages.begin(), mMessages.end(), matchesAnswerUuid);
    if (answerIt != mMessages.end()) {
        return (*answerIt).inProgress();
    }
    return false;
}

void TextAutoGenerateMessagesModel::replaceContent(const QByteArray &uuid,
                                                   const QString &content,
                                                   const QList<TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachementInfoList)
{
    if (uuid.isEmpty()) {
        return;
    }
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == uuid;
    };
    auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
    if (it != mMessages.end()) {
        (*it).setContent(content);
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
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == uuid;
    };
    const auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
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
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == uuid;
    };
    auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
    if (it != mMessages.end()) {
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
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == uuid;
    };
    auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
    if (it == mMessages.end()) {
        return {};
    }
    const QModelIndex idx = createIndex(std::distance(mMessages.begin(), it), 0);
    return idx;
}

QList<QJsonObject> TextAutoGenerateMessagesModel::convertToOllamaChat() const
{
    QList<QJsonObject> lst;
    for (const auto &msg : mMessages) {
        const auto obj = msg.convertToOllamaChatJson();
        if (!obj.isEmpty()) {
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

QList<TextAutoGenerateMessage>::iterator TextAutoGenerateMessagesModel::findMessage(const QByteArray &messageId)
{
    return std::find_if(mMessages.begin(), mMessages.end(), [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == messageId;
    });
}

QList<TextAutoGenerateMessage>::const_iterator TextAutoGenerateMessagesModel::findMessage(const QByteArray &messageId) const
{
    return std::find_if(mMessages.cbegin(), mMessages.cend(), [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == messageId;
    });
}

#include "moc_textautogeneratemessagesmodel.cpp"
