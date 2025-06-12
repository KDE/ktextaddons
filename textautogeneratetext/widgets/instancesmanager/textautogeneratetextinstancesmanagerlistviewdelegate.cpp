/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanagerlistviewdelegate.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerListViewDelegate::TextAutoGenerateTextInstancesManagerListViewDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

TextAutoGenerateTextInstancesManagerListViewDelegate::~TextAutoGenerateTextInstancesManagerListViewDelegate() = default;

#include "moc_textautogeneratetextinstancesmanagerlistviewdelegate.cpp"
