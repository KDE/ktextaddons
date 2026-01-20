/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaonlineconfigurewidget.h"
#include "ollamacommoncomboboxwidget.h"
#include "ollamaonlinemanager.h"
#include "ollamaonlinesettings.h"
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
OllamaOnlineConfigureWidget::OllamaOnlineConfigureWidget(OllamaOnlineManager *manager, QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mServerUrl(new QLineEdit(this))
    , mApiKey(new KPasswordLineEdit(this))
    , mManager(manager)
    , mOllamaComboBoxWidget(new OllamaCommonComboBoxWidget(this))
{
    connect(mManager, &OllamaOnlineManager::modelsLoadDone, this, [this](const OllamaOnlineManager::ModelsInfo &modelinfo) {
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
    connect(mOllamaComboBoxWidget, &OllamaCommonComboBoxWidget::showModelInfoRequested, this, &OllamaOnlineConfigureWidget::showModelInfo);
    connect(mOllamaComboBoxWidget, &OllamaCommonComboBoxWidget::reloadModel, this, &OllamaOnlineConfigureWidget::fillModels);
    connect(mManager, &OllamaOnlineManager::showModelInfoDone, this, &OllamaOnlineConfigureWidget::displayModelInfo);
    loadSettings();
    fillModels();
}

OllamaOnlineConfigureWidget::~OllamaOnlineConfigureWidget() = default;

void OllamaOnlineConfigureWidget::fillModels()
{
    mManager->loadModels();
}

void OllamaOnlineConfigureWidget::displayModelInfo(const QString &modelStr)
{
    QPointer<TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog> dlg = new TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog(this);
    dlg->setText(modelStr);
    dlg->exec();
    delete dlg;
}
void OllamaOnlineConfigureWidget::showModelInfo(const QString &modelName)
{
    // qDebug() << " showModelInfo " << modelName;
    mManager->showModelInfo(modelName);
}

void OllamaOnlineConfigureWidget::loadSettings()
{
    mName->setText(mManager->ollamaOnlineSettings()->displayName());
    mServerUrl->setText(mManager->ollamaOnlineSettings()->serverUrl().toString());
    mApiKey->setPassword(mManager->apiKey());
}

void OllamaOnlineConfigureWidget::saveSettings()
{
    mManager->ollamaOnlineSettings()->setDisplayName(mName->text());
    mManager->ollamaOnlineSettings()->setServerUrl(QUrl(mServerUrl->text()));
    mManager->setApiKey(mApiKey->password());
}

#include "moc_ollamaonlineconfigurewidget.cpp"
