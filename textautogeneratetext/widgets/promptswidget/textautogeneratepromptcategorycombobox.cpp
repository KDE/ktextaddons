/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratepromptcategorycombobox.h"
#include <KLocalizedString>

using namespace TextAutoGenerateText;
TextAutoGeneratePromptCategoryComboBox::TextAutoGeneratePromptCategoryComboBox(QWidget *parent)
    : QComboBox(parent)
{
    fill();
}

TextAutoGeneratePromptCategoryComboBox::~TextAutoGeneratePromptCategoryComboBox() = default;

void TextAutoGeneratePromptCategoryComboBox::fill()
{
    addItem(i18n("Code"), QVariant::fromValue(TextAutoGeneratePrompt::Category::Code));
    addItem(i18n("Misc"), QVariant::fromValue(TextAutoGeneratePrompt::Category::Misc));
    addItem(i18n("Travel"), QVariant::fromValue(TextAutoGeneratePrompt::Category::Travel));
}

TextAutoGeneratePrompt::Category TextAutoGeneratePromptCategoryComboBox::category() const
{
    return currentData().value<TextAutoGeneratePrompt::Category>();
}

void TextAutoGeneratePromptCategoryComboBox::setCategory(TextAutoGeneratePrompt::Category type)
{
    if (const int index = findData(QVariant::fromValue(type)); index != -1) {
        setCurrentIndex(index);
    }
}

#include "moc_textautogeneratepromptcategorycombobox.cpp"
