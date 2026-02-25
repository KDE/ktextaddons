/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaconfigurewidget.h"
#include "ollamacommonkeepaliveparameterswidget.h"
#include "ollamacommonnetworkurlbutton.h"
#include "ollamacommonoptionswidget.h"
#include "ollamacommonoverrideparameterswidget.h"
#include "ollamaconfigurecustomizewidget.h"
#include "ollamalogdialog.h"
#include "widgets/common/textautogeneratenotworkingmessagewidget.h"
#include "widgets/common/textautogenerateshowmodelinfodialog.h"

#include "ollamacommoncomboboxwidget.h"
#include "ollamamanager.h"
#include "ollamasettings.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KMessageBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPointer>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <TextAddonsWidgets/ExecutableUtils>

using namespace Qt::Literals::StringLiterals;
OllamaConfigureWidget::OllamaConfigureWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mPort(new QSpinBox(this))
    , mModelComboBoxWidget(new OllamaCommonComboBoxWidget(this))
    , mMessageWidget(new TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget(this))
    , mManager(manager)
    , mOllamaConfigureCustomizeWidget(new OllamaConfigureCustomizeWidget(this))
    , mOllamaCommonOverrideParametersWidget(new OllamaCommonOverrideParametersWidget(this))
    , mOllamaCommonKeepAliveParametersWidget(new OllamaCommonKeepAliveParametersWidget(this))
    , mOllamaCommonOptionsWidget(
          new OllamaCommonOptionsWidget(OllamaCommonOptionsWidget::ExtraOptions(OllamaCommonOptionsWidget::ExtraOption::ExposeToNetwork), this))
{
    auto centralLayout = new QVBoxLayout(this);
    centralLayout->setObjectName(u"centralLayout"_s);
    centralLayout->setContentsMargins({});

    auto area = new QScrollArea(this);
    centralLayout->addWidget(area);
    area->setWidgetResizable(true);

    auto mainWidget = new QWidget(this);
    area->setWidget(mainWidget);

    auto mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto formLayout = new QFormLayout;
    formLayout->setObjectName(u"formLayout"_s);
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

    mPort->setObjectName(u"mPort"_s);
    mPort->setMinimum(1);
    mPort->setMaximum(99999);
    formLayout->addRow(i18n("Port:"), mPort);

    auto ollamaWidget = new QWidget(this);
    auto ollamaWidgetHboxLayout = new QHBoxLayout(ollamaWidget);
    ollamaWidgetHboxLayout->setContentsMargins({});
    ollamaWidgetHboxLayout->setAlignment(Qt::AlignHCenter);

    mModelComboBoxWidget->setObjectName(u"mModelComboBoxWidget"_s);

    auto showLog = new QPushButton(i18n("Show Ollama Log"), this);
    showLog->setObjectName(u"showLog"_s);
    connect(showLog, &QPushButton::clicked, this, &OllamaConfigureWidget::slotShowOllamaLog);

    ollamaWidgetHboxLayout->addWidget(mModelComboBoxWidget);
    ollamaWidgetHboxLayout->addWidget(showLog);
    formLayout->addRow(i18n("Model:"), ollamaWidget);

    mOllamaCommonOverrideParametersWidget->setObjectName(u"mOllamaCommonOverrideParametersWidget"_s);
    mainLayout->addWidget(mOllamaCommonOverrideParametersWidget);

    mOllamaCommonKeepAliveParametersWidget->setObjectName(u"mOllamaCommonKeepAliveParametersWidget"_s);
    mainLayout->addWidget(mOllamaCommonKeepAliveParametersWidget);

    mOllamaCommonOptionsWidget->setObjectName(u"mOllamaCommonOptionsWidget"_s);
    mainLayout->addWidget(mOllamaCommonOptionsWidget);

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

    auto urlButton = new OllamaCommonNetworkUrlButton(this);
    urlButton->setObjectName(u"urlButton"_s);
    urlButton->setUrl(u"https://docs.ollama.com/gpu#overrides-on-linux"_s);
    hboxLayout->addWidget(urlButton);

    groupCustomizeGroupboxLayout->addLayout(hboxLayout);
    groupCustomizeGroupboxLayout->addWidget(mOllamaConfigureCustomizeWidget);

    mainLayout->addStretch(1);
    connect(mModelComboBoxWidget, &OllamaCommonComboBoxWidget::reloadModel, this, &OllamaConfigureWidget::fillModels);
    connect(mModelComboBoxWidget, &OllamaCommonComboBoxWidget::showModelInfoRequested, this, &OllamaConfigureWidget::showModelInfo);
    connect(this, &OllamaConfigureWidget::ollamaProcessOk, this, [showLog, this](bool state) {
        showLog->setEnabled(state);
        mModelComboBoxWidget->setEnabled(state);
    });

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
    connect(mManager, &OllamaManager::showModelInfoDone, this, &OllamaConfigureWidget::displayModelInfo);
    connect(mManager, &OllamaManager::ollamaStarted, this, &OllamaConfigureWidget::slotOllamaStarted);
    connect(mManager, &OllamaManager::ollamaFailed, this, &OllamaConfigureWidget::slotOllamaFailed);
    fillModels();
    connect(mMessageWidget, &TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget::startOllama, this, &OllamaConfigureWidget::slotStartOllama);
}

OllamaConfigureWidget::~OllamaConfigureWidget() = default;

void OllamaConfigureWidget::displayModelInfo(const QString &modelStr)
{
    TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog dlg(this);
    dlg.setText(modelStr);
    dlg.exec();
}

void OllamaConfigureWidget::showModelInfo(const QString &modelName)
{
    // qDebug() << " showModelInfo " << modelName;
    mManager->showModelInfo(modelName);
}

void OllamaConfigureWidget::slotOllamaStarted()
{
    mMessageWidget->animatedHide();
    Q_EMIT ollamaProcessOk(true);
}

void OllamaConfigureWidget::slotOllamaFailed(const QString &errorStr)
{
    KMessageBox::error(this, errorStr, i18n("Failed to start Ollama"));
}

void OllamaConfigureWidget::slotStartOllama()
{
    mManager->startOllama();
}

void OllamaConfigureWidget::loadSettings()
{
    mName->setText(mManager->ollamaSettings()->displayName());
    mPort->setValue(mManager->ollamaSettings()->serverUrl().port());

    mModelComboBoxWidget->setCurrentModel(mManager->ollamaSettings()->currentModel());
    const OllamaCommonOverrideParametersWidget::OverrideParametersInfo parametersInfo{
        .temperature = mManager->ollamaSettings()->temperature(),
        .seed = mManager->ollamaSettings()->seed(),
        .contextWindowSize = mManager->ollamaSettings()->contextWindowSize(),
    };
    mOllamaCommonOverrideParametersWidget->setParametersInfo(parametersInfo);
    const OllamaConfigureCustomizeWidget::CustomizeInfo info{
        .vulkanSupport = mManager->ollamaSettings()->vulkanSupport(),
        .cudaVisibleDevice = mManager->ollamaSettings()->cudaVisibleDevice(),
        .rocrVisibleDevice = mManager->ollamaSettings()->rocrVisibleDevice(),
        .overrideGfxVersion = mManager->ollamaSettings()->overrideGfxVersion(),
        .defaultModelPath = mManager->ollamaSettings()->defaultModelPath(),
    };
    mOllamaConfigureCustomizeWidget->setCustomizeInfo(info);

    const OllamaCommonKeepAliveParametersWidget::KeepAliveInfo keepAliveInfo{
        .keepAliveType = mManager->ollamaSettings()->keepAliveType(),
        .minutes = mManager->ollamaSettings()->keepAliveMinutes(),
    };
    mOllamaCommonKeepAliveParametersWidget->setKeepAliveInfo(keepAliveInfo);

    const OllamaCommonOptionsWidget::OllamaCommonOptionsInfo optionsInfo{
        .exposeToNetwork = mManager->ollamaSettings()->expose(),
        .thoughtProcessing = mManager->ollamaSettings()->thoughtProcessing(),
        .shareNameType = mManager->ollamaSettings()->shareNameType(),
    };
    mOllamaCommonOptionsWidget->setOptionsInfo(optionsInfo);
}

void OllamaConfigureWidget::saveSettings()
{
    mManager->ollamaSettings()->setDisplayName(mName->text());
    QUrl url = mManager->ollamaSettings()->serverUrl();
    url.setPort(mPort->value());
    mManager->ollamaSettings()->setServerUrl(url);
    mManager->ollamaSettings()->setCurrentModel(mModelComboBoxWidget->currentModel());
    const auto parametersInfo = mOllamaCommonOverrideParametersWidget->parametersInfo();
    mManager->ollamaSettings()->setTemperature(parametersInfo.temperature);
    mManager->ollamaSettings()->setSeed(parametersInfo.seed);
    mManager->ollamaSettings()->setContextWindowSize(parametersInfo.contextWindowSize);
    const OllamaConfigureCustomizeWidget::CustomizeInfo info = mOllamaConfigureCustomizeWidget->customizeInfo();
    mManager->ollamaSettings()->setCudaVisibleDevice(info.cudaVisibleDevice);
    mManager->ollamaSettings()->setRocrVisibleDevice(info.rocrVisibleDevice);
    mManager->ollamaSettings()->setOverrideGfxVersion(info.overrideGfxVersion);
    mManager->ollamaSettings()->setVulkanSupport(info.vulkanSupport);
    mManager->ollamaSettings()->setDefaultModelPath(info.defaultModelPath);

    const auto keepAliveInfo = mOllamaCommonKeepAliveParametersWidget->keepAliveInfo();
    mManager->ollamaSettings()->setKeepAliveMinutes(keepAliveInfo.minutes);
    mManager->ollamaSettings()->setKeepAliveType(keepAliveInfo.keepAliveType);

    const OllamaCommonOptionsWidget::OllamaCommonOptionsInfo optionsInfo = mOllamaCommonOptionsWidget->optionsInfo();
    mManager->ollamaSettings()->setExpose(optionsInfo.exposeToNetwork);
    mManager->ollamaSettings()->setThoughtProcessing(optionsInfo.thoughtProcessing);
    mManager->ollamaSettings()->setShareNameType(optionsInfo.shareNameType);
}

void OllamaConfigureWidget::restoreToDefaults()
{
    const OllamaCommonOverrideParametersWidget::OverrideParametersInfo parametersInfo{
        .temperature = mManager->ollamaSettings()->defaultTemperature(),
        .seed = mManager->ollamaSettings()->defaultSeed(),
        .contextWindowSize = mManager->ollamaSettings()->defaultContextWindowSize(),
    };
    mOllamaCommonOverrideParametersWidget->setParametersInfo(parametersInfo);
    const OllamaCommonKeepAliveParametersWidget::KeepAliveInfo keepAliveInfo{
        .keepAliveType = mManager->ollamaSettings()->defaultKeepAliveType(),
        .minutes = mManager->ollamaSettings()->defaultKeepAliveMinutes(),
    };
    mOllamaCommonKeepAliveParametersWidget->setKeepAliveInfo(keepAliveInfo);
    const OllamaCommonOptionsWidget::OllamaCommonOptionsInfo optionsInfo{
        .exposeToNetwork = false,
        .thoughtProcessing = mManager->ollamaSettings()->defaultThoughtProcessing(),
        .shareNameType = mManager->ollamaSettings()->defaultShareNameType(),
    };
    mOllamaCommonOptionsWidget->setOptionsInfo(optionsInfo);

    mManager->ollamaSettings()->setCudaVisibleDevice({});
    mManager->ollamaSettings()->setRocrVisibleDevice({});
    mManager->ollamaSettings()->setOverrideGfxVersion({});
    mManager->ollamaSettings()->setVulkanSupport({});
    mManager->ollamaSettings()->setDefaultModelPath({});
}

void OllamaConfigureWidget::fillModels()
{
    mMessageWidget->animatedHide();
    mManager->loadModels();
}

void OllamaConfigureWidget::showOllamaVersion()
{
    mManager->getVersion();
}

void OllamaConfigureWidget::slotShowOllamaLog()
{
    OllamaLogDialog dlg(this);
    dlg.setLog(mManager->ollamaOutputData());
    dlg.exec();
}

#include "moc_ollamaconfigurewidget.cpp"
