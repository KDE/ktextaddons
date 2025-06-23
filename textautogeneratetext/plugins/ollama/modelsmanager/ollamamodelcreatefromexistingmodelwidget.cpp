/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "ollamamanager.h"
#include "ollamamodelcreatecombobox.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
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
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});

    mOllamaModelCreateComboBox->setObjectName(u"mOllamaModelCreateComboBox"_s);
    mainLayout->addRow(i18n("Base:"), mOllamaModelCreateComboBox);

    mModelName->setObjectName(u"mModelName"_s);
    mainLayout->addRow(i18n("Name:"), mModelName);

    mTagName->setObjectName(u"mTagName"_s);
    mainLayout->addRow(i18n("Tag:"), mTagName);

    mPromptPlainTextEdit->setObjectName(u"mPromptPlainTextEdit"_s);
    mainLayout->addRow(i18n("Prompt:"), mPromptPlainTextEdit);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    auto createNewModelButton = buttonBox->button(QDialogButtonBox::Ok);
    createNewModelButton->setText(i18nc("@action:button", "Create"));

    createNewModelButton->setEnabled(false);
    connect(createNewModelButton, &QPushButton::clicked, this, &OllamaModelCreateFromExistingModelWidget::slotCreateModel);
    connect(mModelName, &QLineEdit::textChanged, this, [createNewModelButton, this](const QString &str) {
        createNewModelButton->setEnabled(!str.trimmed().isEmpty() && !mOllamaModelCreateComboBox->modelName().isEmpty());
    });

    auto cancelButton = buttonBox->button(QDialogButtonBox::Cancel);
    connect(cancelButton, &QPushButton::clicked, this, &OllamaModelCreateFromExistingModelWidget::cancelRequested);
    mainLayout->addWidget(buttonBox);
}

OllamaModelCreateFromExistingModelWidget::~OllamaModelCreateFromExistingModelWidget() = default;

void OllamaModelCreateFromExistingModelWidget::clear()
{
    mModelName->clear();
    mTagName->clear();
    mPromptPlainTextEdit->clear();
}

void OllamaModelCreateFromExistingModelWidget::slotCreateModel()
{
    if (mOllamaManager) {
        const OllamaManager::CreateModelInfo info{
            .modelName = mModelName->text().trimmed(),
            .fromModelName = mOllamaModelCreateComboBox->modelName(),
            .systemPrompt = mPromptPlainTextEdit->toPlainText().trimmed(),
        };
        // qDebug() << " info " << info;
        mOllamaManager->createModel(std::move(info));
    }
    Q_EMIT createNewModelDone();
}

#include "moc_ollamamodelcreatefromexistingmodelwidget.cpp"
