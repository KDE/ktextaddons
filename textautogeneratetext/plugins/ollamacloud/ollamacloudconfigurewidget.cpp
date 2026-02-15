/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacloudconfigurewidget.h"
#include "autogeneratetext_ollamacloud_debug.h"
#include "ollamacloudmanager.h"
#include "ollamacloudsettings.h"
#include "ollamacommoncomboboxwidget.h"
#include "ollamacommonkeepaliveparameterswidget.h"
#include "ollamacommonoverrideparameterswidget.h"
#include "widgets/common/textautogenerateshowmodelinfodialog.h"
#include <KAuthorized>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KPasswordLineEdit>
#include <QFormLayout>
#include <QLineEdit>
#include <QPointer>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
OllamaCloudConfigureWidget::OllamaCloudConfigureWidget(OllamaCloudManager *manager, QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mApiKey(new KPasswordLineEdit(this))
    , mManager(manager)
    , mOllamaComboBoxWidget(new OllamaCommonComboBoxWidget(this))
    , mOllamaCommonOverrideParametersWidget(new OllamaCommonOverrideParametersWidget(this))
    , mOllamaCommonKeepAliveParametersWidget(new OllamaCommonKeepAliveParametersWidget(this))
{
    connect(mManager, &OllamaCloudManager::modelsLoadDone, this, [this](const OllamaCloudManager::ModelsInfo &modelinfo) {
        // qDebug() << " OllamaConfigureWidget::fillModels() " << modelinfo;
        if (modelinfo.hasError) {
            qCWarning(AUTOGENERATETEXT_OLLAMACLOUD_LOG) << "load model failed";
        } else {
            mOllamaComboBoxWidget->setModels(modelinfo.models);
        }
    });

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto formLayout = new QFormLayout;
    formLayout->setObjectName(u"mainLayout"_s);
    formLayout->setContentsMargins({});
    mainLayout->addLayout(formLayout);

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);
    formLayout->addRow(i18n("Name:"), mName);

    mApiKey->setObjectName(u"mApiKey"_s);
    mApiKey->setRevealPasswordMode(KAuthorized::authorize(u"lineedit_reveal_password"_s) ? KPassword::RevealMode::OnlyNew : KPassword::RevealMode::Never);
    KLineEditEventHandler::catchReturnKey(mApiKey->lineEdit());
    formLayout->addRow(i18n("Api Key:"), mApiKey);

    mOllamaComboBoxWidget->setObjectName(u"mOllamaComboBoxWidget"_s);
    formLayout->addRow(i18n("Model:"), mOllamaComboBoxWidget);

    mOllamaCommonOverrideParametersWidget->setObjectName(u"mOllamaCommonOverrideParametersWidget"_s);
    mainLayout->addWidget(mOllamaCommonOverrideParametersWidget);

    mOllamaCommonKeepAliveParametersWidget->setObjectName(u"mOllamaCommonKeepAliveParametersWidget"_s);
    mainLayout->addWidget(mOllamaCommonKeepAliveParametersWidget);
    mainLayout->addStretch(1);

    connect(mOllamaComboBoxWidget, &OllamaCommonComboBoxWidget::showModelInfoRequested, this, &OllamaCloudConfigureWidget::showModelInfo);
    connect(mOllamaComboBoxWidget, &OllamaCommonComboBoxWidget::reloadModel, this, &OllamaCloudConfigureWidget::fillModels);
    connect(mManager, &OllamaCloudManager::showModelInfoDone, this, &OllamaCloudConfigureWidget::displayModelInfo);
    loadSettings();
    fillModels();
}

OllamaCloudConfigureWidget::~OllamaCloudConfigureWidget() = default;

void OllamaCloudConfigureWidget::fillModels()
{
    mManager->loadModels();
}

void OllamaCloudConfigureWidget::displayModelInfo(const QString &modelStr)
{
    QPointer<TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog> dlg = new TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog(this);
    dlg->setText(modelStr);
    dlg->exec();
    delete dlg;
}
void OllamaCloudConfigureWidget::showModelInfo(const QString &modelName)
{
    // qDebug() << " showModelInfo " << modelName;
    mManager->showModelInfo(modelName);
}

void OllamaCloudConfigureWidget::loadSettings()
{
    mName->setText(mManager->ollamaCloudSettings()->displayName());
    mApiKey->setPassword(mManager->apiKey());
    const OllamaCommonOverrideParametersWidget::OverrideParametersInfo parametersInfo{
        .temperature = mManager->ollamaCloudSettings()->temperature(),
        .seed = mManager->ollamaCloudSettings()->seed(),
        .contextWindowSize = mManager->ollamaCloudSettings()->contextWindowSize(),
    };
    mOllamaCommonOverrideParametersWidget->setParametersInfo(parametersInfo);

    const OllamaCommonKeepAliveParametersWidget::KeepAliveInfo keepAliveInfo{
        .keepAliveType = mManager->ollamaCloudSettings()->keepAliveType(),
        .minutes = mManager->ollamaCloudSettings()->keepAliveMinutes(),
    };
    mOllamaCommonKeepAliveParametersWidget->setKeepAliveInfo(keepAliveInfo);
}

void OllamaCloudConfigureWidget::saveSettings()
{
    mManager->ollamaCloudSettings()->setDisplayName(mName->text());
    mManager->setApiKey(mApiKey->password());
    const auto parametersInfo = mOllamaCommonOverrideParametersWidget->parametersInfo();
    mManager->ollamaCloudSettings()->setTemperature(parametersInfo.temperature);
    mManager->ollamaCloudSettings()->setSeed(parametersInfo.seed);
    mManager->ollamaCloudSettings()->setContextWindowSize(parametersInfo.contextWindowSize);

    const auto keepAliveInfo = mOllamaCommonKeepAliveParametersWidget->keepAliveInfo();
    mManager->ollamaCloudSettings()->setKeepAliveMinutes(keepAliveInfo.minutes);
    mManager->ollamaCloudSettings()->setKeepAliveType(keepAliveInfo.keepAliveType);
}

#include "moc_ollamacloudconfigurewidget.cpp"
