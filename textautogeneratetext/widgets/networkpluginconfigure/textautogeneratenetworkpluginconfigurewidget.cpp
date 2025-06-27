/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenetworkpluginconfigurewidget.h"

#include <KAuthorized>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KPasswordLineEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateNetworkPluginConfigureWidget::TextAutoGenerateNetworkPluginConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mApiKey(new KPasswordLineEdit(this))
    , mInstanceName(new QLineEdit(this))
    , mMaxToken(new QSpinBox(this))
    , mTemperature(new QDoubleSpinBox(this))
    , mWebSite(new QLabel(this))
    , mDescription(new QLabel(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
    mApiKey->setObjectName(u"mApiKey"_s);
    mInstanceName->setObjectName(u"mInstanceName"_s);
    mInstanceName->setClearButtonEnabled(true);
    mMaxToken->setMaximum(9999);
    mMaxToken->setObjectName(u"mMaxToken"_s);
    mTemperature->setObjectName(u"mTemperature"_s);
    mTemperature->setMaximum(10.0);
    mTemperature->setSingleStep(0.1);

    mApiKey->setObjectName(u"mPasswordLineEdit"_s);
    mApiKey->setRevealPasswordMode(KAuthorized::authorize(u"lineedit_reveal_password"_s) ? KPassword::RevealMode::OnlyNew : KPassword::RevealMode::Never);

    mainLayout->addRow(i18n("Name:"), mInstanceName);
    mainLayout->addRow(i18n("Api Key:"), mApiKey);
    mainLayout->addRow(i18n("Max Tokens:"), mMaxToken);
    mainLayout->addRow(i18n("Temperature:"), mTemperature);

    KLineEditEventHandler::catchReturnKey(mApiKey->lineEdit());
    KLineEditEventHandler::catchReturnKey(mInstanceName);
    mWebSite->setOpenExternalLinks(true);
    mWebSite->setObjectName(u"mWebSite"_s);
    mWebSite->setTextFormat(Qt::RichText);
    mainLayout->addWidget(mWebSite);

    mDescription->setObjectName(u"mDescription"_s);
    mDescription->setTextFormat(Qt::PlainText);
    mDescription->setWordWrap(true);
    mainLayout->addWidget(mDescription);
}

TextAutoGenerateNetworkPluginConfigureWidget::~TextAutoGenerateNetworkPluginConfigureWidget() = default;

void TextAutoGenerateNetworkPluginConfigureWidget::setApiKey(const QString &key)
{
    mApiKey->setPassword(key);
}

QString TextAutoGenerateNetworkPluginConfigureWidget::apiKey() const
{
    return mApiKey->password();
}

void TextAutoGenerateNetworkPluginConfigureWidget::setInstanceName(const QString &name)
{
    mInstanceName->setText(name);
}

QString TextAutoGenerateNetworkPluginConfigureWidget::instanceName() const
{
    return mInstanceName->text();
}

void TextAutoGenerateNetworkPluginConfigureWidget::setTemperature(double temp)
{
    mTemperature->setValue(temp);
}

double TextAutoGenerateNetworkPluginConfigureWidget::temperature() const
{
    return mTemperature->value();
}

void TextAutoGenerateNetworkPluginConfigureWidget::setMaxTokens(int tokens)
{
    mMaxToken->setValue(tokens);
}

int TextAutoGenerateNetworkPluginConfigureWidget::maxTokens() const
{
    return mMaxToken->value();
}

void TextAutoGenerateNetworkPluginConfigureWidget::setDescription(const QString &description)
{
    if (description.isEmpty()) {
        mDescription->hide();
    } else {
        mDescription->setText(description);
    }
}

void TextAutoGenerateNetworkPluginConfigureWidget::setWebSiteUrl(const QString &url)
{
    if (url.isEmpty()) {
        mWebSite->setText({});
    } else {
        mWebSite->setText(u"<a href=\"%1\">%1</a>"_s.arg(url));
    }
}

#include "moc_textautogeneratenetworkpluginconfigurewidget.cpp"
