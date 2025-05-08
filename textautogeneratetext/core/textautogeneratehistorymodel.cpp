/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorymodel.h"
#include "textautogeneratemessagesmodel.h"
using namespace TextAutogenerateText;
TextAutoGenerateHistoryModel::TextAutoGenerateHistoryModel(QObject *parent)
    : QIdentityProxyModel{parent}
{
}

TextAutoGenerateHistoryModel::~TextAutoGenerateHistoryModel() = default;

QVariant TextAutoGenerateHistoryModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        const QModelIndex sourceIndex = mapToSource(index);
        QString text = sourceModel()->data(sourceIndex, TextAutoGenerateMessagesModel::TopicRole).toString();
        if (text.isEmpty()) {
            text = sourceModel()->data(sourceIndex, TextAutoGenerateMessagesModel::MessageRole).toString();
        }
        return text;
    }
    return QIdentityProxyModel::data(index, role);
}

#include "moc_textautogeneratehistorymodel.cpp"
