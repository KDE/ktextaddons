/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailablesearchwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "ollamamodelsearchlineedit.h"
#include "ollamamodelsinfoscategoriescombobox.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>

OllamaModelAvailableSearchWidget::OllamaModelAvailableSearchWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new OllamaModelSearchLineEdit(this))
    , mCategoriesComboBox(new OllamaModelsInfosCategoriesComboBox(this))
    , mAddModelButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    mainLayout->addWidget(mSearchLineEdit);
    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &OllamaModelAvailableSearchWidget::searchText);

    mCategoriesComboBox->setObjectName(u"mCategoriesComboBox"_s);
    mainLayout->addWidget(mCategoriesComboBox);
    connect(mCategoriesComboBox, &OllamaModelsInfosCategoriesComboBox::categoriesChanged, this, [this]() {
        Q_EMIT categoriesChanged(mCategoriesComboBox->categories());
    });
    mAddModelButton->setObjectName(u"mAddModelButton"_s);
    mainLayout->addWidget(mAddModelButton);
    mAddModelButton->setIcon(QIcon::fromTheme(u"list-add"_s));
    mAddModelButton->setToolTip(i18nc("@info:tooltip", "Add Model"));
    connect(mAddModelButton, &QToolButton::clicked, this, &OllamaModelAvailableSearchWidget::addModel);
}

OllamaModelAvailableSearchWidget::~OllamaModelAvailableSearchWidget() = default;

#include "moc_ollamamodelavailablesearchwidget.cpp"
