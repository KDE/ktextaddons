/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticoncategorybuttons.h"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QToolButton>
using namespace TextEmoticonsWidgets;
EmoticonCategoryButtons::EmoticonCategoryButtons(QWidget *parent)
    : QWidget{parent}
{
    mMainLayout = new QHBoxLayout(this);
    mMainLayout->setObjectName(QStringLiteral("mMainLayout"));
    mMainLayout->setContentsMargins({});
}

EmoticonCategoryButtons::~EmoticonCategoryButtons()
{
}

void EmoticonCategoryButtons::setCategories(const QStringList &categories)
{
    // TODO initialize buttons
}
