/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorproxymodel.h"
#include "translatormodel.h"

TranslatorProxyModel::TranslatorProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

TranslatorProxyModel::~TranslatorProxyModel() = default;

bool TranslatorProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // TODO
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

#include "moc_translatorproxymodel.cpp"
