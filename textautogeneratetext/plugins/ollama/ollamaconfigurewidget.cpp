/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaconfigurewidget.h"
#include "modelsmanager/ollamanetworkurlbutton.h"
#include "ollamacommonkeepaliveparameterswidget.h"
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
#include <QSpinBox>
#include <TextAddonsWidgets/ExecutableUtils>

using namespace Qt::Literals::StringLiterals;
OllamaConfigureWidget::OllamaConfigureWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mServerUrl(new QLineEdit(this))
    , mModelComboBoxWidget(new OllamaCommonComboBoxWidget(this))
    , mMessageWidget(new TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget(this))
    , mManager(manager)
    , mOllamaConfigureCustomizeWidget(new OllamaConfigureCustomizeWidget(this))
    , mOllamaCommonOverrideParametersWidget(new OllamaCommonOverrideParametersWidget(this))
    , mOllamaCommonKeepAliveParametersWidget(new OllamaCommonKeepAliveParametersWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
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

    mServerUrl->setObjectName(u"mServerUrl"_s);
    KLineEditEventHandler::catchReturnKey(mServerUrl);
    formLayout->addRow(i18n("Server Url:"), mServerUrl);
    mServerUrl->setPlaceholderText(u"http://127.0.0.1:11434"_s);

    auto ollamaWidget = new QWidget(this);
    auto ollamaWidgetHboxLayout = new QHBoxLayout(ollamaWidget);

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
    connect(mModelComboBoxWidget, &OllamaCommonComboBoxWidget::reloadModel, this, &OllamaConfigureWidget::fillModels);
    connect(mModelComboBoxWidget, &OllamaCommonComboBoxWidget::showModelInfoRequested, this, &OllamaConfigureWidget::showModelInfo);
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
    QPointer<TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog> dlg = new TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog(this);
    dlg->setText(modelStr);
    dlg->exec();
    delete dlg;
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
    mServerUrl->setText(mManager->ollamaSettings()->serverUrl().toString());
    mModelComboBoxWidget->setCurrentModel(mManager->ollamaSettings()->currentModel());
    const OllamaCommonOverrideParametersWidget::OverrideParametersInfo parametersInfo{
        .temperature = mManager->ollamaSettings()->temperature(),
        .seed = mManager->ollamaSettings()->seed(),
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
}

void OllamaConfigureWidget::saveSettings()
{
    mManager->ollamaSettings()->setDisplayName(mName->text());
    mManager->ollamaSettings()->setServerUrl(QUrl(mServerUrl->text()));
    mManager->ollamaSettings()->setCurrentModel(mModelComboBoxWidget->currentModel());
    const auto parametersInfo = mOllamaCommonOverrideParametersWidget->parametersInfo();
    mManager->ollamaSettings()->setTemperature(parametersInfo.temperature);
    mManager->ollamaSettings()->setSeed(parametersInfo.seed);
    const OllamaConfigureCustomizeWidget::CustomizeInfo info = mOllamaConfigureCustomizeWidget->customizeInfo();
    mManager->ollamaSettings()->setCudaVisibleDevice(info.cudaVisibleDevice);
    mManager->ollamaSettings()->setRocrVisibleDevice(info.rocrVisibleDevice);
    mManager->ollamaSettings()->setOverrideGfxVersion(info.overrideGfxVersion);
    mManager->ollamaSettings()->setVulkanSupport(info.vulkanSupport);
    mManager->ollamaSettings()->setDefaultModelPath(info.defaultModelPath);

    const auto keepAliveInfo = mOllamaCommonKeepAliveParametersWidget->keepAliveInfo();
    mManager->ollamaSettings()->setKeepAliveMinutes(keepAliveInfo.minutes);
    mManager->ollamaSettings()->setKeepAliveType(keepAliveInfo.keepAliveType);
}

void OllamaConfigureWidget::fillModels()
{
    mMessageWidget->animatedHide();
    mManager->loadModels();
}

void OllamaConfigureWidget::slotShowOllamaLog()
{
    OllamaLogDialog dlg(this);
    dlg.setLog(mManager->ollamaOutputData());
    dlg.exec();
}

#include "moc_ollamaconfigurewidget.cpp"
