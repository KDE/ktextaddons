/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "translatorconfigurelanguagesortfilterproxymodel.h"

using namespace TextTranslator;
TranslatorConfigureLanguageSortFilterProxyModel::TranslatorConfigureLanguageSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setSortCaseSensitivity(Qt::CaseInsensitive);
}

TranslatorConfigureLanguageSortFilterProxyModel::~TranslatorConfigureLanguageSortFilterProxyModel() = default;

#include "moc_translatorconfigurelanguagesortfilterproxymodel.cpp"
