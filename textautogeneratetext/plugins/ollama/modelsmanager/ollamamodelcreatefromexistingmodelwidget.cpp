/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
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

    auto cancelButton = new QPushButton(i18n("Cancel"), this);
    cancelButton->setObjectName(QStringLiteral("cancelButton"));
    connect(cancelButton, &QPushButton::clicked, this, &OllamaModelCreateFromExistingModelWidget::cancelRequested);

    auto createNewModelButton = new QPushButton(i18n("Create"), this);
    createNewModelButton->setObjectName(QStringLiteral("createNewModelButton"));
    connect(createNewModelButton, &QPushButton::clicked, this, &OllamaModelCreateFromExistingModelWidget::slotCreateModel);
}

OllamaModelCreateFromExistingModelWidget::~OllamaModelCreateFromExistingModelWidget() = default;

void OllamaModelCreateFromExistingModelWidget::slotCreateModel()
{
    if (mOllamaManager) {
        // TODO
    }
    Q_EMIT createNewModelRequested();
}

#include "moc_ollamamodelcreatefromexistingmodelwidget.cpp"
