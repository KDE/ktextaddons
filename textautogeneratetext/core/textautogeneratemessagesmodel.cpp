/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessagesmodel.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
#include <QDateTime>

using namespace TextAutoGenerateText;
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
    case OriginalMessageRole:
        return message.content();
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
    case MouseHoverRole:
        return message.mouseHover();
    case EditingRole:
        return message.editingMode();
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

QByteArray TextAutoGenerateMessagesModel::chatId() const
{
    return mChatId;
}

void TextAutoGenerateMessagesModel::setChatId(const QByteArray &newChatId)
{
    mChatId = newChatId;
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
    case MessageRoles::MessageRole:
    case MessageRoles::SenderRole:
    case MessageRoles::DateTimeRole:
    case MessageRoles::UuidRole:
    case MessageRoles::WaitingAnswerRole:
    case MessageRoles::ModelInfoRole:
    case MessageRoles::OriginalMessageRole:
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

#include "moc_textautogeneratemessagesmodel.cpp"
