/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodelcreatecombobox.h"

OllamaModelCreateComboBox::OllamaModelCreateComboBox(QWidget *parent)
    : QComboBox(parent)
{
}

OllamaModelCreateComboBox::~OllamaModelCreateComboBox() = default;

QString OllamaModelCreateComboBox::modelName() const
{
    // TODO
    return {};
}

void OllamaModelCreateComboBox::fillEngine()
{
    // TODO
}
