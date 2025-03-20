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
    // TODO
    return {};
}

QList<TextAutoGenerateMessage> TextAutoGenerateChatModel::messages() const
{
    return mMessages;
}

void TextAutoGenerateChatModel::setMessages(const QList<TextAutoGenerateMessage> &newMessages)
{
    mMessages = newMessages;
}

void TextAutoGenerateChatModel::resetConversation()
{
    beginResetModel();
    mMessages.clear();
    endResetModel();
}

void TextAutoGenerateChatModel::addMessage(const TextAutoGenerateMessage &msg)
{
    // TODO
}

#include "moc_textautogeneratechatmodel.cpp"
