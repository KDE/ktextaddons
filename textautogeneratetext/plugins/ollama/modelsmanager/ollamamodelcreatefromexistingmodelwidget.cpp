/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
OllamaModelCreateFromExistingModelWidget::OllamaModelCreateFromExistingModelWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mModelName(new QLineEdit(this))
    , mTagName(new QLineEdit(this))
    , mOllamaManager(manager)
    , mPromptPlainTextEdit(new QPlainTextEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    mModelName->setObjectName(QStringLiteral("mModelName"));
    mainLayout->addRow(i18n("Name:"), mModelName);

    mTagName->setObjectName(QStringLiteral("mTagName"));
    mainLayout->addRow(i18n("Tag:"), mTagName);

    mPromptPlainTextEdit->setObjectName(QStringLiteral("mPromptPlainTextEdit"));
    mainLayout->addRow(i18n("Prompt:"), mPromptPlainTextEdit);

    // TODO base

    // TODO prompt
}

OllamaModelCreateFromExistingModelWidget::~OllamaModelCreateFromExistingModelWidget() = default;

#include "moc_ollamamodelcreatefromexistingmodelwidget.cpp"
