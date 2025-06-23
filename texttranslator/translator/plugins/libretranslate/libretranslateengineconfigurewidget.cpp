/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineconfigurewidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QCheckBox>
#include <QCompleter>
#include <QFormLayout>
#include <QLineEdit>

LibreTranslateEngineConfigureWidget::LibreTranslateEngineConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mServerUrl(new QLineEdit(this))
    , mApiKey(new QLineEdit(this))
    , mRequiredApiKey(new QCheckBox(i18nc("@option:check", "Server required Api Key"), this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(u"mainLayout"_s);

    mServerUrl->setObjectName(u"mServerUrl"_s);
    mServerUrl->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Server Url:"), mServerUrl);

    mRequiredApiKey->setObjectName(u"mRequiredApiKey"_s);
    mainLayout->addWidget(mRequiredApiKey);

    mApiKey->setObjectName(u"mApiKey"_s);
    mApiKey->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Api Key:"), mApiKey);
    connect(mRequiredApiKey, &QCheckBox::clicked, this, &LibreTranslateEngineConfigureWidget::updateApiKeyState);

    const QStringList listServer{
        u"https://libretranslate.com"_s,
        u"https://libretranslate.de"_s,
        u"https://translate.argosopentech.com"_s,
        u"https://translate.api.skitzen.com"_s,
        u"https://translate.fortytwo-it.com"_s,
        u"https://translate.terraprint.co"_s,
        u"https://lt.vern.cc"_s,
    };

    KLineEditEventHandler::catchReturnKey(mApiKey);
    KLineEditEventHandler::catchReturnKey(mServerUrl);

    auto completer = new QCompleter(listServer, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    mServerUrl->setCompleter(completer);
}

LibreTranslateEngineConfigureWidget::~LibreTranslateEngineConfigureWidget() = default;

void LibreTranslateEngineConfigureWidget::updateApiKeyState(bool state)
{
    mApiKey->setEnabled(state);
}

QString LibreTranslateEngineConfigureWidget::serverUrl() const
{
    return mServerUrl->text();
}

void LibreTranslateEngineConfigureWidget::setServerUrl(const QString &serverUrl)
{
    mServerUrl->setText(serverUrl);
}

QString LibreTranslateEngineConfigureWidget::apiKey() const
{
    return mApiKey->text();
}

void LibreTranslateEngineConfigureWidget::setApiKey(const QString &key)
{
    mApiKey->setText(key);
}

bool LibreTranslateEngineConfigureWidget::serverRequiredApiKey() const
{
    return mRequiredApiKey->isChecked();
}

void LibreTranslateEngineConfigureWidget::setServerRequiredApiKey(bool state)
{
    mRequiredApiKey->setChecked(state);
    updateApiKeyState(state);
}

#include "moc_libretranslateengineconfigurewidget.cpp"
