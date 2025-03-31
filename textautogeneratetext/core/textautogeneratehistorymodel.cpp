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
    return mHistoryInfos.count();
}

QVariant TextAutoGenerateHistoryModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mHistoryInfos.count()) {
        return {};
    }
    const auto &info = mHistoryInfos[index.row()];
    /*
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

QList<TextAutoGenerateHistoryInfo> TextAutoGenerateHistoryModel::historyInfos() const
{
    return mHistoryInfos;
}

void TextAutoGenerateHistoryModel::setHistoryInfos(const QList<TextAutoGenerateHistoryInfo> &newHistoryInfos)
{
    mHistoryInfos = newHistoryInfos;
}

#include "moc_textautogeneratehistorymodel.cpp"
