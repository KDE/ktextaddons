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

int TextAutoGenerateChatModel::rowCount(const QModelIndex &) const
{
    // TODO
    return 0;
}

QVariant TextAutoGenerateChatModel::data(const QModelIndex &index, int role) const
{
    // TODO
    return {};
}

#include "moc_textautogeneratechatmodel.cpp"
