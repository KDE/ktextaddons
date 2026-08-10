/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratepromptcombobox.h"
#include <KLocalizedString>

using namespace TextAutoGenerateText;
TextAutoGeneratePromptComboBox::TextAutoGeneratePromptComboBox(QWidget *parent)
    : QComboBox(parent)
{
    fill();
}

TextAutoGeneratePromptComboBox::~TextAutoGeneratePromptComboBox() = default;

void TextAutoGeneratePromptComboBox::fill()
{
    addItem(i18n("Code"), QVariant::fromValue(TextAutoGeneratePrompt::Category::Code));
    addItem(i18n("Misc"), QVariant::fromValue(TextAutoGeneratePrompt::Category::Misc));
    addItem(i18n("Travel"), QVariant::fromValue(TextAutoGeneratePrompt::Category::Travel));
}

TextAutoGeneratePrompt::Category TextAutoGeneratePromptComboBox::category() const
{
    return currentData().value<TextAutoGeneratePrompt::Category>();
}

void TextAutoGeneratePromptComboBox::setCategory(TextAutoGeneratePrompt::Category type)
{
    const int index = findData(QVariant::fromValue(type));
    if (index != -1) {
        setCurrentIndex(index);
    }
}
