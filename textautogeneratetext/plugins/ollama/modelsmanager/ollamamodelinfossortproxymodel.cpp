/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodelinfossortproxymodel.h"

OllamaModelInfosSortProxyModel::OllamaModelInfosSortProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

OllamaModelInfosSortProxyModel::~OllamaModelInfosSortProxyModel() = default;

#include "moc_ollamamodelinfossortproxymodel.cpp"
