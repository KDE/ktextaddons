/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancemodel.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstanceModel::TextAutoGenerateTextInstanceModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateTextInstanceModel::~TextAutoGenerateTextInstanceModel() = default;

int TextAutoGenerateTextInstanceModel::rowCount(const QModelIndex &) const
{
    // TODO
    return {};
}

QVariant TextAutoGenerateTextInstanceModel::data(const QModelIndex &index, int role) const
{
    // TODO
    return {};
}

#include "moc_textautogeneratetextinstancemodel.cpp"
