/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessagesmodel.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
#include <QDateTime>

using namespace TextAutogenerateText;
TextAutoGenerateMessagesModel::TextAutoGenerateMessagesModel(QObject *parent)
    : QAbstractListModel{parent}
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
    const auto &message = mMessages[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case MessageRole:
        return message.htmlGenerated();
    case DateTimeStrRole:
        return message.dateTimeStr();
    case DateTimeRole:
        return message.dateTime();
    case SenderRole:
        return QVariant::fromValue(message.sender());
    case FinishedRole:
        return !message.inProgress();
    case UuidRole:
        return message.uuid();
    case TopicRole:
        return message.topic();
    case MouseHoverRole:
        return message.mouseHover();
    case ArchivedRole:
        return message.archived();
    case EditingRole:
        return message.editingMode();
    case SectionRole:
        return QVariant::fromValue(section(message));
    case WaitingAnswerRole:
        return waitingAnswer(message);
    case ModelInfoRole:
        return generateModelInfo(message);
    }
    return {};
}

QString TextAutoGenerateMessagesModel::generateModelInfo(const TextAutoGenerateMessage &m) const
{
    if (m.engineName().isEmpty() && m.modelName().isEmpty()) {
        return {};
    }
    return i18n("Engine: %1\nModel: %2", m.engineName(), m.modelName());
}

TextAutoGenerateMessagesModel::SectionHistory TextAutoGenerateMessagesModel::section(const TextAutoGenerateMessage &m) const
{
    if (m.dateTime() == -1) {
        return TextAutoGenerateMessagesModel::SectionHistory::Unknown;
    }
    const QDate d = QDateTime::fromSecsSinceEpoch(m.dateTime()).date();
    if (d == QDate::currentDate()) {
        return TextAutoGenerateMessagesModel::SectionHistory::Today;
    } else if (d < QDate::currentDate().addDays(7)) {
        return TextAutoGenerateMessagesModel::SectionHistory::LessThanSevenDays;
    } else if (d < QDate::currentDate().addDays(30)) {
        return TextAutoGenerateMessagesModel::SectionHistory::LessThanThirtyDays;
    } else {
        return TextAutoGenerateMessagesModel::SectionHistory::Later;
    }
    return TextAutoGenerateMessagesModel::SectionHistory::Unknown;
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
    if (msg.sender() == TextAutoGenerateMessage::Sender::LLM) {
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
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {MessageRole});

        auto matchesAnswerUuid = [&](const TextAutoGenerateMessage &msg) {
            return msg.uuid() == answerUuid;
        };
        const auto answerIt = std::find_if(mMessages.begin(), mMessages.end(), matchesAnswerUuid);
        if (answerIt != mMessages.end()) {
            const int i = std::distance(mMessages.begin(), answerIt);
            (*answerIt).setInProgress(true);
            (*answerIt).setContent({});
            emitChanged(i, {MessageRole | FinishedRole});
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
        emitChanged(i, {MessageRole | FinishedRole});
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

void TextAutoGenerateMessagesModel::replaceContent(const QByteArray &uuid, const QString &content)
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
        const int i = std::distance(mMessages.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {MessageRole});
    }
}

void TextAutoGenerateMessagesModel::removeDiscussion(const QByteArray &uuid)
{
    if (uuid.isEmpty()) {
        return;
    }
    auto matchesUuid = [&](const TextAutoGenerateMessage &msg) {
        return msg.uuid() == uuid;
    };
    const auto it = std::find_if(mMessages.begin(), mMessages.end(), matchesUuid);
    if (it != mMessages.end()) {
        const int i = std::distance(mMessages.begin(), it);
        const QByteArray answerUuid = it->answerUuid();
        beginRemoveRows(QModelIndex(), i, i);
        mMessages.removeAt(i);
        endRemoveRows();

        auto matchesAnswerUuid = [&](const TextAutoGenerateMessage &msg) {
            return msg.uuid() == answerUuid;
        };
        const auto answerIt = std::find_if(mMessages.begin(), mMessages.end(), matchesAnswerUuid);
        if (answerIt != mMessages.end()) {
            const int i = std::distance(mMessages.begin(), answerIt);
            beginRemoveRows(QModelIndex(), i, i);
            mMessages.removeAt(i);
            endRemoveRows();
        }
    }
}

bool TextAutoGenerateMessagesModel::cancelRequest(const QModelIndex &index)
{
    return setData(index, false, TextAutoGenerateMessagesModel::FinishedRole);
}

QString TextAutoGenerateMessagesModel::sectionName(SectionHistory sectionId)
{
    switch (sectionId) {
    case TextAutoGenerateMessagesModel::SectionHistory::Favorite:
        return i18n("Favorite");
    case TextAutoGenerateMessagesModel::SectionHistory::Today:
        return i18n("Today");
    case TextAutoGenerateMessagesModel::SectionHistory::LessThanSevenDays:
        return i18n("7 days previous");
    case TextAutoGenerateMessagesModel::SectionHistory::LessThanThirtyDays:
        return i18n("30 days previous");
    case TextAutoGenerateMessagesModel::SectionHistory::Later:
        return i18n("Later");
    case TextAutoGenerateMessagesModel::SectionHistory::Unknown:
        return i18n("Unknown");
    case TextAutoGenerateMessagesModel::SectionHistory::NSections:
        break;
    }
    return QStringLiteral("ERROR");
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
    case MessageRoles::TopicRole: {
        msg.setTopic(value.toString());
        const QModelIndex newIndex = index(idx.row(), MessageRoles::TopicRole);
        Q_EMIT dataChanged(newIndex, newIndex);
        return true;
    }
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
    case MessageRoles::MessageRole:
    case MessageRoles::SenderRole:
    case MessageRoles::DateTimeRole:
    case MessageRoles::UuidRole:
    case MessageRoles::ArchivedRole:
    case MessageRoles::SectionRole:
    case MessageRoles::WaitingAnswerRole:
    case MessageRoles::ModelInfoRole:
        return false;
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

Qt::ItemFlags TextAutoGenerateMessagesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

#include "moc_textautogeneratemessagesmodel.cpp"
