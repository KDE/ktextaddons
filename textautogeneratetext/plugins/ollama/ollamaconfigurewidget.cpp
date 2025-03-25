/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaconfigurewidget.h"
#include "ollamamanager.h"
#include "ollamasettings.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KMessageWidget>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>

OllamaConfigureWidget::OllamaConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mServerUrl(new QLineEdit(this))
    , mPrompt(new QPlainTextEdit(this))
    , mModelComboBox(new QComboBox(this))
    , mMessageWidget(new KMessageWidget(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mMessageWidget->setObjectName(QStringLiteral("mMessageWidget"));
    mainLayout->addWidget(mMessageWidget);
    mMessageWidget->setVisible(false);
    mMessageWidget->setMessageType(KMessageWidget::MessageType::Error);

    mServerUrl->setObjectName(QStringLiteral("mServerUrl"));
    KLineEditEventHandler::catchReturnKey(mServerUrl);
    mainLayout->addRow(i18n("Server Url:"), mServerUrl);
    mServerUrl->setPlaceholderText(QStringLiteral("http://127.0.0.1:11434"));

    mModelComboBox->setObjectName(QStringLiteral("mModelComboBox"));
    mainLayout->addRow(i18n("Model:"), mModelComboBox);

    mPrompt->setObjectName(QStringLiteral("mPrompt"));
    mainLayout->addRow(i18n("Prompt:"), mPrompt);
    mPrompt->setPlaceholderText(i18n("No system prompt"));
    // TODO add setPlaceHolder

    // TODO fill model

    loadSettings();
}

OllamaConfigureWidget::~OllamaConfigureWidget() = default;

void OllamaConfigureWidget::loadSettings()
{
    mServerUrl->setText(OllamaSettings::serverUrl().toString());
    mPrompt->setPlainText(OllamaSettings::systemPrompt());
    fillModels();
}

void OllamaConfigureWidget::saveSettings()
{
}

void OllamaConfigureWidget::fillModels()
{
    connect(OllamaManager::self(), &OllamaManager::modelsLoadDone, this, [this](const OllamaManager::ModelsInfo &modelinfo) {
        qDebug() << " OllamaConfigureWidget::fillModels() " << modelinfo;
        if (modelinfo.hasError) {
            mMessageWidget->setText(modelinfo.errorOccured);
            mMessageWidget->animatedShow();
        } else {
            mModelComboBox->addItems(modelinfo.models);
        }
    });
    OllamaManager::self()->loadModels();
    // TODO
}

#include "moc_ollamaconfigurewidget.cpp"
