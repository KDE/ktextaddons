/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidget.h"
#include "ollamamanager.h"
#include "ollamamodelcreatecombobox.h"
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
    , mOllamaModelCreateComboBox(new OllamaModelCreateComboBox(manager, this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mOllamaModelCreateComboBox->setObjectName(QStringLiteral("mOllamaModelCreateComboBox"));
    mainLayout->addRow(i18n("Base:"), mOllamaModelCreateComboBox);

    mModelName->setObjectName(QStringLiteral("mModelName"));
    mainLayout->addRow(i18n("Name:"), mModelName);

    mTagName->setObjectName(QStringLiteral("mTagName"));
    mainLayout->addRow(i18n("Tag:"), mTagName);

    mPromptPlainTextEdit->setObjectName(QStringLiteral("mPromptPlainTextEdit"));
    mainLayout->addRow(i18n("Prompt:"), mPromptPlainTextEdit);

    auto hboxLayout = new QHBoxLayout;
    mainLayout->addItem(hboxLayout);

    auto createNewModelButton = new QPushButton(i18nc("@action:button", "Create"), this);
    createNewModelButton->setObjectName(QStringLiteral("createNewModelButton"));
    createNewModelButton->setEnabled(false);
    connect(createNewModelButton, &QPushButton::clicked, this, &OllamaModelCreateFromExistingModelWidget::slotCreateModel);
    connect(mModelName, &QLineEdit::textChanged, this, [createNewModelButton, this](const QString &str) {
        createNewModelButton->setEnabled(!str.trimmed().isEmpty() && !mOllamaModelCreateComboBox->modelName().isEmpty());
    });
    hboxLayout->addWidget(createNewModelButton);

    auto cancelButton = new QPushButton(i18nc("@action:button", "Cancel"), this);
    cancelButton->setObjectName(QStringLiteral("cancelButton"));
    connect(cancelButton, &QPushButton::clicked, this, &OllamaModelCreateFromExistingModelWidget::cancelRequested);
    hboxLayout->addWidget(cancelButton);
}

OllamaModelCreateFromExistingModelWidget::~OllamaModelCreateFromExistingModelWidget() = default;

void OllamaModelCreateFromExistingModelWidget::slotCreateModel()
{
    if (mOllamaManager) {
        const OllamaManager::CreateModelInfo info{
            .modelName = mModelName->text().trimmed(),
            .fromModelName = mOllamaModelCreateComboBox->modelName(),
            .systemPrompt = mPromptPlainTextEdit->toPlainText().trimmed(),
        };
        qDebug() << " info " << info;
        mOllamaManager->createModel(std::move(info));
    }
    Q_EMIT createNewModelDone();
}

#include "moc_ollamamodelcreatefromexistingmodelwidget.cpp"
