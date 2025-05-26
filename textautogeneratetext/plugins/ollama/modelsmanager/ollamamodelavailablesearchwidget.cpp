/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailablesearchwidget.h"
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
    , mRemoveModelButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mainLayout->addWidget(mSearchLineEdit);
    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &OllamaModelAvailableSearchWidget::searchText);

    mCategoriesComboBox->setObjectName(QStringLiteral("mCategoriesComboBox"));
    mainLayout->addWidget(mCategoriesComboBox);
    connect(mCategoriesComboBox, &OllamaModelsInfosCategoriesComboBox::categoriesChanged, this, [this]() {
        Q_EMIT categoriesChanged(mCategoriesComboBox->categories());
    });
    mRemoveModelButton->setObjectName(QStringLiteral("mRemoveModelButton"));
    mainLayout->addWidget(mRemoveModelButton);
    mRemoveModelButton->setIcon(QIcon::fromTheme(QStringLiteral("edit-delete")));
    connect(mRemoveModelButton, &QToolButton::clicked, this, &OllamaModelAvailableSearchWidget::removeModel);
}

OllamaModelAvailableSearchWidget::~OllamaModelAvailableSearchWidget() = default;

#include "moc_ollamamodelavailablesearchwidget.cpp"
