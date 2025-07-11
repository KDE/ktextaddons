/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticoncategorybuttons.h"
using namespace Qt::Literals::StringLiterals;

#include "emoticoncategorybutton.h"
#include "emoticonunicodeutils.h"
#include <KLocalizedString>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QToolButton>
#include <QWheelEvent>
#include <TextEmoticonsCore/EmoticonCategory>
#include <TextEmoticonsCore/EmoticonUnicodeUtils>

using namespace TextEmoticonsWidgets;
EmoticonCategoryButtons::EmoticonCategoryButtons(QWidget *parent)
    : QWidget{parent}
    , mMainLayout(new QHBoxLayout(this))
    , mButtonGroup(new QButtonGroup(this))
{
    mMainLayout->setObjectName(u"mMainLayout"_s);
    mMainLayout->setContentsMargins({});
    mButtonGroup->setObjectName(u"mButtonGroup"_s);
}

EmoticonCategoryButtons::~EmoticonCategoryButtons() = default;

void EmoticonCategoryButtons::wheelEvent(QWheelEvent *event)
{
    auto button = mButtonGroup->checkedButton();
    if (button) {
        const int index = mButtonGroup->buttons().indexOf(button);
        if (index != -1) {
            QAbstractButton *nextButton = nullptr;
            if (event->angleDelta().y() > 0) {
                if (index > 0) {
                    nextButton = mButtonGroup->buttons().at(index - 1);
                } else {
                    nextButton = mButtonGroup->buttons().constLast();
                }
            } else if (event->angleDelta().y() < 0) {
                if (index == (mButtonGroup->buttons().count() - 1)) {
                    nextButton = mButtonGroup->buttons().constFirst();
                } else {
                    nextButton = mButtonGroup->buttons().at(index + 1);
                }
            }
            if (nextButton) {
                nextButton->setChecked(true);
                nextButton->clicked(true);
            }
        }
    }

    QWidget::wheelEvent(event);
}

void EmoticonCategoryButtons::addButton(const QString &name, const QString &category, const QString &toolTip)
{
    auto button = new EmoticonCategoryButton(this);
    button->setText(name);
    button->setToolTip(toolTip);
    mMainLayout->addWidget(button);
    mButtonGroup->addButton(button);
    connect(button, &QToolButton::clicked, this, [this, category](bool clicked) {
        if (clicked) {
            Q_EMIT categorySelected(category);
        }
    });
}

bool EmoticonCategoryButtons::wasLoaded() const
{
    return mWasLoaded;
}

void EmoticonCategoryButtons::setCategories(const QList<TextEmoticonsCore::EmoticonCategory> &categories, bool hasCustomSupport)
{
    addButton(TextEmoticonsCore::EmoticonUnicodeUtils::recentName(),
              TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier(),
              i18nc("Previously used emojis", "History"));
    if (hasCustomSupport) {
        addButton(TextEmoticonsCore::EmoticonUnicodeUtils::customName(),
                  TextEmoticonsCore::EmoticonUnicodeUtils::customIdentifier(),
                  i18nc("'Custom' is a category of emoji", "Custom"));
    }
    for (const auto &cat : categories) {
        addButton(cat.name(), cat.category(), cat.i18nName());
    }
    // Initialize first button.
    auto button = mButtonGroup->buttons().constFirst();
    button->setChecked(true);
    Q_EMIT categorySelected(TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier());
    mWasLoaded = true;
}

#include "moc_emoticoncategorybuttons.cpp"
