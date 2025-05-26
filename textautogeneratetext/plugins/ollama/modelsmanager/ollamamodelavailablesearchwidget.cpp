/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailablesearchwidget.h"
#include "ollamamodelsinfoscategoriescombobox.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>

OllamaModelAvailableSearchWidget::OllamaModelAvailableSearchWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mCategoriesComboBox(new OllamaModelsInfosCategoriesComboBox(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mainLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search Model…"));
    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &OllamaModelAvailableSearchWidget::searchText);

    mCategoriesComboBox->setObjectName(QStringLiteral("mCategoriesComboBox"));
    mainLayout->addWidget(mCategoriesComboBox);
    connect(mCategoriesComboBox, &OllamaModelsInfosCategoriesComboBox::categoriesChanged, this, [this]() {
        Q_EMIT categoriesChanged(mCategoriesComboBox->categories());
    });
}

OllamaModelAvailableSearchWidget::~OllamaModelAvailableSearchWidget() = default;

#include "moc_ollamamodelavailablesearchwidget.cpp"
