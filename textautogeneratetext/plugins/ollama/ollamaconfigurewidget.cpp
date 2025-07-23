/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaconfigurewidget.h"
#include "autogeneratetext_ollama_debug.h"
#include "core/textautogeneratetextutils.h"
#include "widgets/common/textautogeneratenotworkingmessagewidget.h"

#include "ollamacomboboxwidget.h"
#include "ollamamanager.h"
#include "ollamasettings.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QProcess>
#include <QSpinBox>

using namespace Qt::Literals::StringLiterals;
OllamaConfigureWidget::OllamaConfigureWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mServerUrl(new QLineEdit(this))
    , mPrompt(new QPlainTextEdit(this))
    , mModelComboBoxWidget(new OllamaComboBoxWidget(this))
    , mMessageWidget(new TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget(this))
    , mTemperature(new QDoubleSpinBox(this))
    , mSeed(new QSpinBox(this))
    , mManager(manager)
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mMessageWidget->setObjectName(u"mMessageWidget"_s);
    mainLayout->addWidget(mMessageWidget);
    mMessageWidget->setVisible(false);
    mMessageWidget->setCloseButtonVisible(false);
    mMessageWidget->setMessageType(KMessageWidget::MessageType::Error);

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);
    mainLayout->addRow(i18n("Name:"), mName);

    mServerUrl->setObjectName(u"mServerUrl"_s);
    KLineEditEventHandler::catchReturnKey(mServerUrl);
    mainLayout->addRow(i18n("Server Url:"), mServerUrl);
    mServerUrl->setPlaceholderText(u"http://127.0.0.1:11434"_s);

    mModelComboBoxWidget->setObjectName(u"mModelComboBoxWidget"_s);
    mainLayout->addRow(i18n("Model:"), mModelComboBoxWidget);

    mTemperature->setObjectName(u"mTemperature"_s);
    mainLayout->addRow(i18n("Temperature:"), mTemperature);
    mTemperature->setRange(0.0, 10.0);
    mTemperature->setSingleStep(0.01);
    mTemperature->setToolTip(i18nc("@info:tooltip", "The temperature of the model. Increasing the temperature will make the model answer more creatively."));

    mSeed->setObjectName(u"mSeed"_s);
    mainLayout->addRow(i18n("Seed:"), mSeed);
    mSeed->setToolTip(i18nc("@info:tooltip",
                            "Sets the random number seed to use for generation. Setting this to a specific number will make the model generate the same text "
                            "for the same prompt. (Default: 0)"));
    mSeed->setRange(0, 10);
    mSeed->setSingleStep(1);

    mPrompt->setObjectName(u"mPrompt"_s);
    mainLayout->addRow(i18n("Prompt:"), mPrompt);
    mPrompt->setPlaceholderText(i18n("No system prompt"));

    connect(mModelComboBoxWidget, &OllamaComboBoxWidget::reloadModel, this, &OllamaConfigureWidget::fillModels);
    connect(mManager, &OllamaManager::modelsLoadDone, this, [this](const OllamaManager::ModelsInfo &modelinfo) {
        // qDebug() << " OllamaConfigureWidget::fillModels() " << modelinfo;
        if (modelinfo.hasError) {
            mMessageWidget->setText(modelinfo.errorOccured);
            mMessageWidget->animatedShow();
            Q_EMIT ollamaProcessOk(false);
        } else {
            mModelComboBoxWidget->setModels(modelinfo.models);
            Q_EMIT ollamaProcessOk(true);
        }
    });
    loadSettings();
    connect(mManager, &OllamaManager::refreshInstalledModels, this, &OllamaConfigureWidget::fillModels);
    fillModels();
    connect(mMessageWidget, &TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget::startOllama, this, &OllamaConfigureWidget::slotStartOllama);
}

OllamaConfigureWidget::~OllamaConfigureWidget() = default;

void OllamaConfigureWidget::slotStartOllama()
{
    const QString ollamaPath = TextAutoGenerateText::TextAutoGenerateTextUtils::findExecutable(u"ollama"_s);
    if (ollamaPath.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Ollama doesn't exist";
        return;
    }
    const bool status = QProcess::startDetached(ollamaPath, {u"start"_s});
    if (!status) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Impossible to start ollama";
    } else {
        mMessageWidget->animatedHide();
        Q_EMIT ollamaProcessOk(true);
        // TODO activate it but we need to know that server is up. fillModels();
    }
}

void OllamaConfigureWidget::loadSettings()
{
    mName->setText(mManager->ollamaSettings()->displayName());
    mServerUrl->setText(mManager->ollamaSettings()->serverUrl().toString());
    mPrompt->setPlainText(mManager->ollamaSettings()->systemPrompt());
    mModelComboBoxWidget->setCurrentModel(mManager->ollamaSettings()->currentModel());
    mTemperature->setValue(mManager->ollamaSettings()->temperature());
    mSeed->setValue(mManager->ollamaSettings()->seed());
}

void OllamaConfigureWidget::saveSettings()
{
    mManager->ollamaSettings()->setDisplayName(mName->text());
    mManager->ollamaSettings()->setSystemPrompt(mPrompt->toPlainText());
    mManager->ollamaSettings()->setServerUrl(QUrl(mServerUrl->text()));
    mManager->ollamaSettings()->setCurrentModel(mModelComboBoxWidget->currentModel());
    mManager->ollamaSettings()->setTemperature(mTemperature->value());
    mManager->ollamaSettings()->setSeed(mSeed->value());
}

void OllamaConfigureWidget::fillModels()
{
    mMessageWidget->animatedHide();
    mManager->loadModels();
}

#include "moc_ollamaconfigurewidget.cpp"
