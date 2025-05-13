/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchlistviewdelegate.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchListViewDelegate::TextAutoGenerateSearchListViewDelegate(QObject *parent)
    : QItemDelegate{parent}
{
}

TextAutoGenerateSearchListViewDelegate::~TextAutoGenerateSearchListViewDelegate() = default;

#include "moc_textautogeneratesearchlistviewdelegate.cpp"
