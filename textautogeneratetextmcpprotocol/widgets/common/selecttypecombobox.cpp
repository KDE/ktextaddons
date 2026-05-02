/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selecttypecombobox.h"

using namespace TextAutoGenerateTextMcpProtocolWidgets;

SelectTypeComboBox::SelectTypeComboBox(QWidget *parent)
    : QComboBox(parent)
{
}

SelectTypeComboBox::~SelectTypeComboBox() = default;

#include "moc_selecttypecombobox.cpp"
