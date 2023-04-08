/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticoncategorybuttons.h"
#include "emoticonutils.h"
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

void EmoticonCategoryButtons::addButton(const QString &name, const QString &category)
{
    auto button = new QToolButton(this);
    button->setText(name);
    mMainLayout->addWidget(button);
    mButtonGroup->addButton(button);
    button->setCheckable(true);
    button->setAutoRaise(true);
    connect(button, &QToolButton::clicked, this, [this, category](bool clicked) {
        if (clicked) {
            Q_EMIT categorySelected(category);
        }
    });
}

void EmoticonCategoryButtons::setCategories(const QList<TextEmoticonsCore::EmoticonCategory> &categories)
{
    addButton(QStringLiteral("⌛️"), TextEmoticonsWidgets::EmoticonUtils::recentIdentifier());
    for (const auto &cat : categories) {
        addButton(cat.name(), cat.category());
    }
    auto button = mButtonGroup->buttons().constFirst();
    button->setChecked(true);
    Q_EMIT categorySelected(TextEmoticonsWidgets::EmoticonUtils::recentIdentifier());
}
