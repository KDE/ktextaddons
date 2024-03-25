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
    , mAutoCorrectionLanguageModel(new AutoCorrectionLanguageModel(this))
{
    auto sortFilterModel = new QSortFilterProxyModel(this);
    sortFilterModel->setSourceModel(mAutoCorrectionLanguageModel);
    sortFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortFilterModel->setFilterRole(AutoCorrectionLanguageModel::LocaleI18n);
    sortFilterModel->sort(0);

    setModel(sortFilterModel);
}

QString AutoCorrectionLanguage::language(int index) const
{
    return mAutoCorrectionLanguageModel->language(index);
}

AutoCorrectionLanguage::~AutoCorrectionLanguage() = default;

QString AutoCorrectionLanguage::language() const
{
    return itemData(currentIndex(), AutoCorrectionLanguageModel::Locale).toString();
}

void AutoCorrectionLanguage::setLanguage(const QString &language)
{
    const int index = findData(language);
    setCurrentIndex(index);
}
