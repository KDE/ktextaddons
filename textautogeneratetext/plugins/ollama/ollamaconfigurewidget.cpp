/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaconfigurewidget.h"
#include "ollamacomboboxwidget.h"
#include "ollamamanager.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KMessageWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSpinBox>

OllamaConfigureWidget::OllamaConfigureWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mServerUrl(new QLineEdit(this))
    , mPrompt(new QPlainTextEdit(this))
    , mModelComboBoxWidget(new OllamaComboBoxWidget(this))
    , mMessageWidget(new KMessageWidget(this))
    , mTemperature(new QDoubleSpinBox(this))
    , mSeed(new QSpinBox(this))
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

    mTemperature->setObjectName(QStringLiteral("mTemperature"));
    mainLayout->addRow(i18n("Temperature:"), mTemperature);
    mTemperature->setRange(0.0, 10.0);
    mTemperature->setSingleStep(0.01);
    mTemperature->setToolTip(i18nc("@info:tooltip", "The temperature of the model. Increasing the temperature will make the model answer more creatively."));

    mSeed->setObjectName(QStringLiteral("mSeed"));
    mainLayout->addRow(i18n("Seed:"), mSeed);
    mSeed->setToolTip(i18nc("@info:tooltip",
                            "Sets the random number seed to use for generation. Setting this to a specific number will make the model generate the same text "
                            "for the same prompt. (Default: 0)"));
    mSeed->setRange(0, 10);
    mSeed->setSingleStep(1);

    mPrompt->setObjectName(QStringLiteral("mPrompt"));
    mainLayout->addRow(i18n("Prompt:"), mPrompt);
    mPrompt->setPlaceholderText(i18n("No system prompt"));

    connect(mModelComboBoxWidget, &OllamaComboBoxWidget::reloadModel, this, &OllamaConfigureWidget::fillModels);
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
    connect(mManager, &OllamaManager::refreshInstalledModels, this, &OllamaConfigureWidget::fillModels);
    fillModels();
}

OllamaConfigureWidget::~OllamaConfigureWidget() = default;

void OllamaConfigureWidget::loadSettings()
{
    /*
    mServerUrl->setText(OllamaSettings::serverUrl().toString());
    mPrompt->setPlainText(OllamaSettings::systemPrompt());
    mModelComboBoxWidget->setCurrentModel(OllamaSettings::model());
    mTemperature->setValue(OllamaSettings::temperature());
    mSeed->setValue(OllamaSettings::seed());
    */
}

void OllamaConfigureWidget::saveSettings()
{
    /*
    OllamaSettings::setSystemPrompt(mPrompt->toPlainText());
    OllamaSettings::setServerUrl(QUrl(mServerUrl->text()));
    OllamaSettings::setModel(mModelComboBoxWidget->currentModel());
    OllamaSettings::setTemperature(mTemperature->value());
    OllamaSettings::setSeed(mSeed->value());
    OllamaSettings::self()->save();
    */
}

void OllamaConfigureWidget::fillModels()
{
    mMessageWidget->animatedHide();
    mManager->loadModels();
}

#include "moc_ollamaconfigurewidget.cpp"
