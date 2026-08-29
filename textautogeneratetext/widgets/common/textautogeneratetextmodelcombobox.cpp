/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmodelcombobox.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextModelComboBox::TextAutoGenerateTextModelComboBox(QWidget *parent)
    : QComboBox(parent)
{
}

TextAutoGenerateTextModelComboBox::~TextAutoGenerateTextModelComboBox() = default;

void TextAutoGenerateTextModelComboBox::setModelList(const QList<TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> &lst)
{
    clear();
    for (const auto &item : lst) {
        addItem(item.modelName, item.identifier);
    }
}

QString TextAutoGenerateTextModelComboBox::currentModel() const
{
    return currentData().toString();
}

void TextAutoGenerateTextModelComboBox::setCurrentModel(const QString &identifier)
{
    if (const int index = findData(identifier); index != -1) {
        setCurrentIndex(index);
    }
}

#include "moc_textautogeneratetextmodelcombobox.cpp"
