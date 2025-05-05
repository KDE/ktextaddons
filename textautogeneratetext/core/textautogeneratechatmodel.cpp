/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratechatmodel.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
#include <QDateTime>

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
    case EditingRole:
        return message.editingMode();
    case SectionRole:
        return QVariant::fromValue(section(message));
    }
    return {};
}

TextAutoGenerateChatModel::SectionHistory TextAutoGenerateChatModel::section(const TextAutoGenerateMessage &m) const
{
    if (m.dateTime() == -1) {
        return TextAutoGenerateChatModel::SectionHistory::Unknown;
    }
    const QDate d = QDateTime::fromSecsSinceEpoch(m.dateTime()).date();
    if (d == QDate::currentDate()) {
        return TextAutoGenerateChatModel::SectionHistory::Today;
    } else if (d < QDate::currentDate().addDays(7)) {
        return TextAutoGenerateChatModel::SectionHistory::LessThanSevenDays;
    } else if (d < QDate::currentDate().addDays(30)) {
        return TextAutoGenerateChatModel::SectionHistory::LessThanThirtyDays;
    } else {
        return TextAutoGenerateChatModel::SectionHistory::Later;
    }
    return TextAutoGenerateChatModel::SectionHistory::Unknown;
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
    if (msg.sender() == TextAutoGenerateMessage::Sender::LLM) {
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(mMessages.count() - 1, {FinishedRole});
    }
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
        emitChanged(i, {MessageRole | FinishedRole});
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

bool TextAutoGenerateChatModel::cancelRequest(const QModelIndex &index)
{
    return setData(index, false, TextAutoGenerateChatModel::FinishedRole);
}

QString TextAutoGenerateChatModel::sectionName(SectionHistory sectionId)
{
    switch (sectionId) {
    case TextAutoGenerateChatModel::SectionHistory::Today:
        return i18n("Today");
    case TextAutoGenerateChatModel::SectionHistory::LessThanSevenDays:
        return i18n("7 days previous");
    case TextAutoGenerateChatModel::SectionHistory::LessThanThirtyDays:
        return i18n("30 days previous");
    case TextAutoGenerateChatModel::SectionHistory::Later:
        return i18n("Later");
    case TextAutoGenerateChatModel::SectionHistory::Unknown:
        return i18n("Unknown");
    case TextAutoGenerateChatModel::SectionHistory::NSections:
        break;
    }
    return QStringLiteral("ERROR");
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
    case ChatRoles::EditingRole:
        msg.setEditingMode(value.toBool());
        Q_EMIT dataChanged(idx, idx, {ChatRoles::EditingRole});
        return true;
    case ChatRoles::FinishedRole:
        msg.setInProgress(value.toBool());
        Q_EMIT dataChanged(idx, idx, {ChatRoles::FinishedRole});
        return true;
    case ChatRoles::MessageRole:
    case ChatRoles::SenderRole:
    case ChatRoles::DateTimeRole:
    case ChatRoles::UuidRole:
    case ChatRoles::ArchivedRole:
        return false;
    }
    return QAbstractListModel::setData(idx, value, role);
}

QModelIndex TextAutoGenerateChatModel::indexForUuid(const QByteArray &uuid) const
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

Qt::ItemFlags TextAutoGenerateChatModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

#include "moc_textautogeneratechatmodel.cpp"
