/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QSortFilterProxyModel>
namespace TextTranslator
{
class TranslatorConfigureLanguageSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TranslatorConfigureLanguageSortFilterProxyModel(QObject *parent = nullptr);
    ~TranslatorConfigureLanguageSortFilterProxyModel() override;
};
}
