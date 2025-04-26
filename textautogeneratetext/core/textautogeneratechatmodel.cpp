/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratechatmodel.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutogenerateText;
TextAutoGenerateChatModel::TextAutoGenerateChatModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateChatModel::~TextAutoGenerateChatModel() = default;

int TextAutoGenerateChatModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mMessages.count();
}

QVariant TextAutoGenerateChatModel::data(const QModelIndex &index, int role) const
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
    }
    return {};
}

QList<TextAutoGenerateMessage> TextAutoGenerateChatModel::messages() const
{
    return mMessages;
}

void TextAutoGenerateChatModel::setMessages(const QList<TextAutoGenerateMessage> &newMessages)
{
    beginResetModel();
    mMessages = newMessages;
    endResetModel();
}

void TextAutoGenerateChatModel::resetConversation()
{
    beginResetModel();
    mMessages.clear();
    endResetModel();
    Q_EMIT conversationCleared();
}

void TextAutoGenerateChatModel::addMessage(const TextAutoGenerateMessage &msg)
{
    beginInsertRows(QModelIndex(), mMessages.count(), mMessages.count());
    mMessages.append(msg);
    endInsertRows();
}

QByteArray TextAutoGenerateChatModel::editMessage(const QByteArray &uuid, const QString &str)
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

void TextAutoGenerateChatModel::changeInProgress(const QByteArray &uuid, bool inProgress)
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
        emitChanged(i, {MessageRole});
    }
}

void TextAutoGenerateChatModel::replaceContent(const QByteArray &uuid, const QString &content)
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

void TextAutoGenerateChatModel::removeDiscussion(const QByteArray &uuid)
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

bool TextAutoGenerateChatModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "ERROR: invalid index";
        return false;
    }
    const int id = idx.row();
    TextAutoGenerateMessage &msg = mMessages[id];
    switch (role) {
    case ChatRoles::TopicRole: {
        msg.setTopic(value.toString());
        const QModelIndex newIndex = index(idx.row(), ChatRoles::TopicRole);
        Q_EMIT dataChanged(newIndex, newIndex);
        return true;
    }
    case ChatRoles::MouseHoverRole:
        msg.setMouseHover(value.toBool());
        Q_EMIT dataChanged(idx, idx, {ChatRoles::MouseHoverRole});
        return true;
    case ChatRoles::MessageRole:
    case ChatRoles::SenderRole:
    case ChatRoles::FinishedRole:
    case ChatRoles::DateTimeRole:
    case ChatRoles::UuidRole:
        return false;
    }
    return QAbstractListModel::setData(idx, value, role);
}

#include "moc_textautogeneratechatmodel.cpp"
