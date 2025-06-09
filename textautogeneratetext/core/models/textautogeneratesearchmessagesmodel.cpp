/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessagesmodel.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchMessagesModel::TextAutoGenerateSearchMessagesModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateSearchMessagesModel::~TextAutoGenerateSearchMessagesModel() = default;

QList<TextAutoGenerateSearchMessage> TextAutoGenerateSearchMessagesModel::searchMessages() const
{
    return mSearchMessages;
}

void TextAutoGenerateSearchMessagesModel::setSearchMessages(const QList<TextAutoGenerateSearchMessage> &newSearchMessages)
{
    beginResetModel();
    mSearchMessages = newSearchMessages;
    endResetModel();
}

int TextAutoGenerateSearchMessagesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mSearchMessages.count();
}

QVariant TextAutoGenerateSearchMessagesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mSearchMessages.count()) {
        return {};
    }
    const auto &message = mSearchMessages[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case MessageSearchRoles::PreviewText:
        return message.previewText();
    case MessageSearchRoles::ChatUuid:
        return message.chatId();
    case MessageSearchRoles::MessageUuid:
        return message.messageId();
    case MessageSearchRoles::DateTime:
        return message.dateTime();
    }
    return {};
}

bool TextAutoGenerateSearchMessagesModel::isEmpty() const
{
    return mSearchMessages.isEmpty();
}

#include "moc_textautogeneratesearchmessagesmodel.cpp"
