/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionlanguage.h"
#include "autocorrectionlanguagemodel.h"
#include <QSortFilterProxyModel>

using namespace TextAutoCorrectionWidgets;

AutoCorrectionLanguage::AutoCorrectionLanguage(QWidget *parent)
    : QComboBox(parent)
{
    auto sortFilterModel = new QSortFilterProxyModel(this);
    sortFilterModel->setSourceModel(new AutoCorrectionLanguageModel(this));
    sortFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortFilterModel->setFilterRole(AutoCorrectionLanguageModel::LocaleI18n);
    sortFilterModel->sort(0);

    setModel(sortFilterModel);
}

AutoCorrectionLanguage::~AutoCorrectionLanguage() = default;

QString AutoCorrectionLanguage::language() const
{
    return itemData(currentIndex()).toString();
}

void AutoCorrectionLanguage::setLanguage(const QString &language)
{
    const int index = findData(language);
    setCurrentIndex(index);
}
