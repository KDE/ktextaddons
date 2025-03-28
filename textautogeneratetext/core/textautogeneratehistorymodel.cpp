/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorymodel.h"

using namespace TextAutogenerateText;
TextAutoGenerateHistoryModel::TextAutoGenerateHistoryModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateHistoryModel::~TextAutoGenerateHistoryModel() = default;

int TextAutoGenerateHistoryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    // return mMessages.count();
    return 0;
}

QVariant TextAutoGenerateHistoryModel::data(const QModelIndex &index, int role) const
{
    /*
    if (index.row() < 0 || index.row() >= mMessages.count()) {
        return {};
    }
    const auto &message = mMessages[index.row()];
    switch (role) {
    case MessageRole:
        return message.content();
    case SenderRole:
        return QVariant::fromValue(message.sender());
    case FinishedRole:
        // TODO
        break;
    }
    */
    return {};
}

#include "moc_textautogeneratehistorymodel.cpp"
