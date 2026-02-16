/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonsharenamecombobox.h"
#include "ollamacommonsettings.h"
#include <KLocalizedString>

OllamaCommonShareNameComboBox::OllamaCommonShareNameComboBox(QWidget *parent)
    : QComboBox(parent)
{
    fill();
}

OllamaCommonShareNameComboBox::~OllamaCommonShareNameComboBox() = default;

void OllamaCommonShareNameComboBox::fill()
{
    addItem(i18n("Do not Share"), QVariant::fromValue(OllamaCommonSettings::ShareNameType::DoNotShare));
    addItem(i18n("Username"), QVariant::fromValue(OllamaCommonSettings::ShareNameType::UserName));
    addItem(i18n("Full Name"), QVariant::fromValue(OllamaCommonSettings::ShareNameType::FullName));
}

OllamaCommonSettings::ShareNameType OllamaCommonShareNameComboBox::shareNameType() const
{
    return currentData().value<OllamaCommonSettings::ShareNameType>();
}

void OllamaCommonShareNameComboBox::setShareNameType(OllamaCommonSettings::ShareNameType type)
{
    const int index = findData(QVariant::fromValue(type));
    if (index != -1) {
        setCurrentIndex(index);
    }
}
#include "moc_ollamacommonsharenamecombobox.cpp"
