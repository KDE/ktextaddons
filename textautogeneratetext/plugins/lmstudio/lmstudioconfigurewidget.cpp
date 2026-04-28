/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lmstudioconfigurewidget.h"
#include "widgets/common/textautogeneratenotworkingmessagewidget.h"
#include "widgets/common/textautogenerateshowmodelinfodialog.h"

#include "lmstudiomanager.h"

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
#include <kpasswordlineedit.h>
#include <qurl.h>

using namespace Qt::Literals::StringLiterals;
LMStudioConfigureWidget::LMStudioConfigureWidget(LMStudioManager *manager, QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mUrl(new QLineEdit(this))
    , mApiKey(new KPasswordLineEdit(this))
    , mMessageWidget(new TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget(this))
    , mManager(manager)
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

    mUrl->setObjectName(u"mUrl"_s);
    KLineEditEventHandler::catchReturnKey(mUrl);
    formLayout->addRow(i18n("Url:"), mUrl);

    mApiKey->setObjectName(u"mUrl"_s);
    KLineEditEventHandler::catchReturnKey(mApiKey);
    formLayout->addRow(i18n("Api token:"), mApiKey);

    mainLayout->addStretch(1);

    connect(mManager, &LMStudioManager::modelsLoadDone, this, [this](const LMStudioManager::ModelsInfo &modelinfo) {
        // qDebug() << " LMStudioConfigureWidget::fillModels() " << modelinfo;
        if (modelinfo.hasError) {
            mMessageWidget->setMessageInfo(modelinfo.errorOccured);
            mMessageWidget->animatedShow();
            Q_EMIT lmStudioProcessOk(false);
        } else {
            // mModelComboBoxWidget->setModels(modelinfo.models);
            Q_EMIT lmStudioProcessOk(true);
        }
    });
    connect(mName, &QLineEdit::textChanged, this, [this](const QString &str) {
        Q_EMIT enableOkButton(!str.trimmed().isEmpty());
    });
    loadSettings();
    connect(mManager, &LMStudioManager::refreshInstalledModels, this, &LMStudioConfigureWidget::fillModels);
    connect(mManager, &LMStudioManager::showModelInfoDone, this, &LMStudioConfigureWidget::displayModelInfo);
    fillModels();
}

LMStudioConfigureWidget::~LMStudioConfigureWidget() = default;

void LMStudioConfigureWidget::displayModelInfo(const QString &modelStr)
{
    TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog dlg(this);
    dlg.setText(modelStr);
    dlg.exec();
}

void LMStudioConfigureWidget::showModelInfo(const QString &modelName)
{
    // qDebug() << " showModelInfo " << modelName;
    // mManager->showModelInfo(modelName);
}

void LMStudioConfigureWidget::loadSettings()
{
    mName->setText(mManager->lmStudioSettings()->displayName());
    mUrl->setText(mManager->lmStudioSettings()->serverUrl().url());
    mApiKey->setPassword(mManager->apiKey());
}

void LMStudioConfigureWidget::saveSettings()
{
    mManager->lmStudioSettings()->setDisplayName(mName->text());
    mManager->lmStudioSettings()->setServerUrl(QUrl(mUrl->text()));
    mManager->setApiKey(mApiKey->password());
}

void LMStudioConfigureWidget::restoreToDefaults()
{
    mManager->lmStudioSettings()->setServerUrl(mManager->lmStudioSettings()->defaultServerUrl());
}

void LMStudioConfigureWidget::fillModels()
{
    mMessageWidget->animatedHide();
    mManager->loadModels();
}

#include "moc_lmstudioconfigurewidget.cpp"
