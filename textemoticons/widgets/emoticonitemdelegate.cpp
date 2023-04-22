/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticonitemdelegate.h"
using namespace TextEmoticonsWidgets;
EmoticonItemDelegate::EmoticonItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

EmoticonItemDelegate::~EmoticonItemDelegate() = default;
