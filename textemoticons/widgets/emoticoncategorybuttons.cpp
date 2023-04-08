/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticoncategorybuttons.h"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QToolButton>
#include <TextEmoticonsCore/EmoticonCategory>
using namespace TextEmoticonsWidgets;
EmoticonCategoryButtons::EmoticonCategoryButtons(QWidget *parent)
    : QWidget{parent}
    , mButtonGroup(new QButtonGroup(this))
{
    mMainLayout = new QHBoxLayout(this);
    mMainLayout->setObjectName(QStringLiteral("mMainLayout"));
    mMainLayout->setContentsMargins({});
    mButtonGroup->setObjectName(QStringLiteral("mButtonGroup"));
}

EmoticonCategoryButtons::~EmoticonCategoryButtons() = default;

void EmoticonCategoryButtons::setCategories(const QList<TextEmoticonsCore::EmoticonCategory> &categories)
{
    // TODO add recent
    for (const auto &cat : categories) {
        auto button = new QToolButton(this);
        button->setText(cat.name());
        mMainLayout->addWidget(button);
        mButtonGroup->addButton(button);
        button->setCheckable(true);
        button->setAutoRaise(true);
        connect(button, &QToolButton::clicked, this, [this, cat](bool clicked) {
            if (clicked) {
                Q_EMIT categorySelected(cat.category());
            }
        });
    }
}
