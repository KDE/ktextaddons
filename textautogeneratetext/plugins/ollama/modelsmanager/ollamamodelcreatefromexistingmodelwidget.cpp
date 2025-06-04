/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidget.h"
#include "ollamamanager.h"
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

    auto cancelButton = new QPushButton(i18nc("@action:button", "Cancel"), this);
    cancelButton->setObjectName(QStringLiteral("cancelButton"));
    connect(cancelButton, &QPushButton::clicked, this, &OllamaModelCreateFromExistingModelWidget::cancelRequested);

    auto createNewModelButton = new QPushButton(i18nc("@action:button", "Create"), this);
    createNewModelButton->setObjectName(QStringLiteral("createNewModelButton"));
    createNewModelButton->setEnabled(false);
    connect(createNewModelButton, &QPushButton::clicked, this, &OllamaModelCreateFromExistingModelWidget::slotCreateModel);
    connect(mModelName, &QLineEdit::textChanged, this, [createNewModelButton](const QString &str) {
        createNewModelButton->setEnabled(!str.trimmed().isEmpty());
    });
}

OllamaModelCreateFromExistingModelWidget::~OllamaModelCreateFromExistingModelWidget() = default;

void OllamaModelCreateFromExistingModelWidget::slotCreateModel()
{
    if (mOllamaManager) {
        OllamaManager::CreateModelInfo info;
        info.modelName = mModelName->text().trimmed();
        info.systemPrompt = mPromptPlainTextEdit->toPlainText().trimmed();
        // TODO
        mOllamaManager->createModel(info);
        // TODO
    }
    Q_EMIT createNewModelRequested();
}

#include "moc_ollamamodelcreatefromexistingmodelwidget.cpp"
