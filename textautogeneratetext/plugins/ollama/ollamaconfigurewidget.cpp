/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaconfigurewidget.h"
#include "ollamacomboboxwidget.h"
#include "ollamamanager.h"
#include "ollamasettings.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KMessageWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>

OllamaConfigureWidget::OllamaConfigureWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mServerUrl(new QLineEdit(this))
    , mPrompt(new QPlainTextEdit(this))
    , mModelComboBoxWidget(new OllamaComboBoxWidget(this))
    , mMessageWidget(new KMessageWidget(this))
    , mManager(manager)
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

    mModelComboBoxWidget->setObjectName(QStringLiteral("mModelComboBoxWidget"));
    mainLayout->addRow(i18n("Model:"), mModelComboBoxWidget);

    mPrompt->setObjectName(QStringLiteral("mPrompt"));
    mainLayout->addRow(i18n("Prompt:"), mPrompt);
    mPrompt->setPlaceholderText(i18n("No system prompt"));

    connect(mModelComboBoxWidget, &OllamaComboBoxWidget::reloadModel, this, &OllamaConfigureWidget::fillModels);
    fillModels();
}

OllamaConfigureWidget::~OllamaConfigureWidget() = default;

void OllamaConfigureWidget::loadSettings()
{
    mServerUrl->setText(OllamaSettings::serverUrl().toString());
    mPrompt->setPlainText(OllamaSettings::systemPrompt());
    mModelComboBoxWidget->setCurrentModel(OllamaSettings::model());
}

void OllamaConfigureWidget::saveSettings()
{
    OllamaSettings::setSystemPrompt(mPrompt->toPlainText());
    OllamaSettings::setServerUrl(QUrl(mServerUrl->text()));
    OllamaSettings::setModel(mModelComboBoxWidget->currentModel());
    OllamaSettings::self()->save();
}

void OllamaConfigureWidget::fillModels()
{
    mMessageWidget->animatedHide();
    connect(mManager, &OllamaManager::modelsLoadDone, this, [this](const OllamaManager::ModelsInfo &modelinfo) {
        // qDebug() << " OllamaConfigureWidget::fillModels() " << modelinfo;
        if (modelinfo.hasError) {
            mMessageWidget->setText(modelinfo.errorOccured);
            mMessageWidget->animatedShow();
        } else {
            mModelComboBoxWidget->setModels(modelinfo.models);
            loadSettings();
        }
    });
    mManager->loadModels();
}

#include "moc_ollamaconfigurewidget.cpp"
