/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelsearchwidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>

OllamaModelSearchWidget::OllamaModelSearchWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mainLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search Model…"));
    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &OllamaModelSearchWidget::searchText);
}

OllamaModelSearchWidget::~OllamaModelSearchWidget() = default;

#include "moc_ollamamodelsearchwidget.cpp"
