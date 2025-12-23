/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaconfigurewidget.h"
#include "modelsmanager/ollamanetworkurlbutton.h"
#include "ollamaconfigurecustomizewidget.h"
#include "ollamastartprocessjob.h"
#include "widgets/common/textautogeneratenotworkingmessagewidget.h"

#include "ollamacomboboxwidget.h"
#include "ollamamanager.h"
#include "ollamasettings.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KMessageBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <TextAddonsWidgets/ExecutableUtils>

using namespace Qt::Literals::StringLiterals;
OllamaConfigureWidget::OllamaConfigureWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mServerUrl(new QLineEdit(this))
    , mModelComboBoxWidget(new OllamaComboBoxWidget(this))
    , mMessageWidget(new TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget(this))
    , mTemperature(new QDoubleSpinBox(this))
    , mSeed(new QSpinBox(this))
    , mManager(manager)
    , mOllamaConfigureCustomizeWidget(new OllamaConfigureCustomizeWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto formLayout = new QFormLayout;
    formLayout->setObjectName(u"mainLayout"_s);
    formLayout->setContentsMargins({});
    mainLayout->addLayout(formLayout);

    mMessageWidget->setObjectName(u"mMessageWidget"_s);
    formLayout->addWidget(mMessageWidget);
    mMessageWidget->setVisible(false);
    mMessageWidget->setCloseButtonVisible(false);
    mMessageWidget->setMessageType(KMessageWidget::MessageType::Error);

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);
    formLayout->addRow(i18n("Name:"), mName);

    mServerUrl->setObjectName(u"mServerUrl"_s);
    KLineEditEventHandler::catchReturnKey(mServerUrl);
    formLayout->addRow(i18n("Server Url:"), mServerUrl);
    mServerUrl->setPlaceholderText(u"http://127.0.0.1:11434"_s);

    mModelComboBoxWidget->setObjectName(u"mModelComboBoxWidget"_s);
    formLayout->addRow(i18n("Model:"), mModelComboBoxWidget);

    mTemperature->setObjectName(u"mTemperature"_s);
    formLayout->addRow(i18n("Temperature:"), mTemperature);
    mTemperature->setRange(0.0, 10.0);
    mTemperature->setSingleStep(0.01);
    mTemperature->setToolTip(i18nc("@info:tooltip", "The temperature of the model. Increasing the temperature will make the model answer more creatively."));

    mSeed->setObjectName(u"mSeed"_s);
    formLayout->addRow(i18n("Seed:"), mSeed);
    mSeed->setToolTip(i18nc("@info:tooltip",
                            "Sets the random number seed to use for generation. Setting this to a specific number will make the model generate the same text "
                            "for the same prompt. (Default: 0)"));
    mSeed->setRange(0, 10);
    mSeed->setSingleStep(1);

    auto groupCustomizeGroupbox = new QGroupBox(i18n("Customize Ollama"), this);
    groupCustomizeGroupbox->setObjectName(u"groupCustomizeGroupbox"_s);
    mainLayout->addWidget(groupCustomizeGroupbox);

    auto groupCustomizeGroupboxLayout = new QVBoxLayout(groupCustomizeGroupbox);
    groupCustomizeGroupboxLayout->setObjectName(u"groupCustomizeGroupboxLayout"_s);
    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(u"hboxLayout"_s);
    hboxLayout->setContentsMargins({});

    auto label = new QLabel(i18n("These entries are optional, they are used to troubleshoot GPU related problems with Ollama."), this);
    label->setObjectName(u"label"_s);
    auto font = label->font();
    font.setBold(true);
    font.setItalic(true);
    label->setFont(font);
    hboxLayout->addWidget(label);

    auto urlButton = new OllamaNetworkUrlButton(this);
    urlButton->setObjectName(u"urlButton"_s);
    urlButton->setUrl(u"https://docs.ollama.com/gpu#overrides-on-linux"_s);
    hboxLayout->addWidget(urlButton);

    groupCustomizeGroupboxLayout->addLayout(hboxLayout);
    groupCustomizeGroupboxLayout->addWidget(mOllamaConfigureCustomizeWidget);

    mainLayout->addStretch(1);
    connect(mModelComboBoxWidget, &OllamaComboBoxWidget::reloadModel, this, &OllamaConfigureWidget::fillModels);
    connect(mManager, &OllamaManager::modelsLoadDone, this, [this](const OllamaManager::ModelsInfo &modelinfo) {
        // qDebug() << " OllamaConfigureWidget::fillModels() " << modelinfo;
        if (modelinfo.hasError) {
            mMessageWidget->setMessageInfo(modelinfo.errorOccured);
            mMessageWidget->animatedShow();
            Q_EMIT ollamaProcessOk(false);
        } else {
            mModelComboBoxWidget->setModels(modelinfo.models);
            Q_EMIT ollamaProcessOk(true);
        }
    });
    connect(mName, &QLineEdit::textChanged, this, [this](const QString &str) {
        Q_EMIT enableOkButton(!str.trimmed().isEmpty());
    });
    loadSettings();
    connect(mManager, &OllamaManager::refreshInstalledModels, this, &OllamaConfigureWidget::fillModels);
    fillModels();
    connect(mMessageWidget, &TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget::startOllama, this, &OllamaConfigureWidget::slotStartOllama);
}

OllamaConfigureWidget::~OllamaConfigureWidget() = default;

void OllamaConfigureWidget::slotStartOllama()
{
    auto job = new OllamaStartProcessJob(mManager, this);
    connect(job, &OllamaStartProcessJob::ollamaStarted, this, [this]() {
        mMessageWidget->animatedHide();
        Q_EMIT ollamaProcessOk(true);
    });
    connect(job, &OllamaStartProcessJob::ollamaFailed, this, [this](const QString &errorStr) {
        KMessageBox::error(this, errorStr, i18n("Failed to start Ollama"));
    });
    job->start();
}

void OllamaConfigureWidget::loadSettings()
{
    mName->setText(mManager->ollamaSettings()->displayName());
    mServerUrl->setText(mManager->ollamaSettings()->serverUrl().toString());
    mModelComboBoxWidget->setCurrentModel(mManager->ollamaSettings()->currentModel());
    mTemperature->setValue(mManager->ollamaSettings()->temperature());
    mSeed->setValue(mManager->ollamaSettings()->seed());
    const OllamaConfigureCustomizeWidget::CustomizeInfo info{
        .vulkanSupport = mManager->ollamaSettings()->vulkanSupport(),
        .cudaVisibleDevice = mManager->ollamaSettings()->cudaVisibleDevice(),
        .rocrVisibleDevice = mManager->ollamaSettings()->rocrVisibleDevice(),
        .overrideGfxVersion = mManager->ollamaSettings()->overrideGfxVersion(),
        .defaultModelPath = mManager->ollamaSettings()->defaultModelPath(),
    };
    mOllamaConfigureCustomizeWidget->setCustomizeInfo(info);
}

void OllamaConfigureWidget::saveSettings()
{
    mManager->ollamaSettings()->setDisplayName(mName->text());
    mManager->ollamaSettings()->setServerUrl(QUrl(mServerUrl->text()));
    mManager->ollamaSettings()->setCurrentModel(mModelComboBoxWidget->currentModel());
    mManager->ollamaSettings()->setTemperature(mTemperature->value());
    mManager->ollamaSettings()->setSeed(mSeed->value());
    const OllamaConfigureCustomizeWidget::CustomizeInfo info = mOllamaConfigureCustomizeWidget->customizeInfo();
    mManager->ollamaSettings()->setCudaVisibleDevice(info.cudaVisibleDevice);
    mManager->ollamaSettings()->setRocrVisibleDevice(info.rocrVisibleDevice);
    mManager->ollamaSettings()->setOverrideGfxVersion(info.overrideGfxVersion);
    mManager->ollamaSettings()->setVulkanSupport(info.vulkanSupport);
    mManager->ollamaSettings()->setDefaultModelPath(info.defaultModelPath);
}

void OllamaConfigureWidget::fillModels()
{
    mMessageWidget->animatedHide();
    mManager->loadModels();
}

#include "moc_ollamaconfigurewidget.cpp"
