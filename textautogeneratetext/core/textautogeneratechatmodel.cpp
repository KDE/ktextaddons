/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratechatmodel.h"

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
    case MessageRole:
        return message.content();
    case DateTimeRole:
        return message.dateTime();
    case SenderRole:
        return QVariant::fromValue(message.sender());
    case FinishedRole:
        return !message.inProgress();
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
}

void TextAutoGenerateChatModel::addMessage(const TextAutoGenerateMessage &msg)
{
    beginInsertRows(QModelIndex(), 0, mMessages.count() - 1);
    mMessages.append(msg);
    endInsertRows();
}

void TextAutoGenerateChatModel::replaceLastMessage(const TextAutoGenerateMessage &msg)
{
    beginInsertRows(QModelIndex(), 0, mMessages.count() - 1);
    mMessages.removeLast();
    mMessages.append(msg);
    endInsertRows();
}

#include "moc_textautogeneratechatmodel.cpp"
