/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacloudconfigurewidget.h"
#include "ollamacloudmanager.h"
#include "ollamacloudsettings.h"
#include "ollamacommoncomboboxwidget.h"
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
    , mServerUrl(new QLineEdit(this))
    , mApiKey(new KPasswordLineEdit(this))
    , mManager(manager)
    , mOllamaComboBoxWidget(new OllamaCommonComboBoxWidget(this))
{
    connect(mManager, &OllamaCloudManager::modelsLoadDone, this, [this](const OllamaCloudManager::ModelsInfo &modelinfo) {
        // qDebug() << " OllamaConfigureWidget::fillModels() " << modelinfo;
        if (modelinfo.hasError) {
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

    mServerUrl->setObjectName(u"mServerUrl"_s);
    KLineEditEventHandler::catchReturnKey(mServerUrl);
    formLayout->addRow(i18n("Server Url:"), mServerUrl);
    mServerUrl->setPlaceholderText(u"https://ollama.com"_s);

    mApiKey->setObjectName(u"mApiKey"_s);
    mApiKey->setRevealPasswordMode(KAuthorized::authorize(u"lineedit_reveal_password"_s) ? KPassword::RevealMode::OnlyNew : KPassword::RevealMode::Never);
    KLineEditEventHandler::catchReturnKey(mApiKey->lineEdit());
    formLayout->addRow(i18n("Api Key:"), mApiKey);

    mOllamaComboBoxWidget->setObjectName(u"mOllamaComboBoxWidget"_s);
    formLayout->addRow(i18n("Model:"), mOllamaComboBoxWidget);
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
    mServerUrl->setText(mManager->ollamaCloudSettings()->serverUrl().toString());
    mApiKey->setPassword(mManager->apiKey());
}

void OllamaCloudConfigureWidget::saveSettings()
{
    mManager->ollamaCloudSettings()->setDisplayName(mName->text());
    mManager->ollamaCloudSettings()->setServerUrl(QUrl(mServerUrl->text()));
    mManager->setApiKey(mApiKey->password());
}

#include "moc_ollamacloudconfigurewidget.cpp"
