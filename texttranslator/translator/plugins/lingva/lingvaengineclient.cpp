/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lingvaengineclient.h"
#include "lingvaenginedialog.h"
#include "lingvaengineplugin.h"
#include "lingvaengineutil.h"
#include "translator/misc/translatorutil.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QPointer>

LingvaEngineClient::LingvaEngineClient(QObject *parent)
    : TextTranslator::TranslatorEngineClient{parent}
{
}

LingvaEngineClient::~LingvaEngineClient() = default;

QString LingvaEngineClient::name() const
{
    return QStringLiteral("lingva");
}

QString LingvaEngineClient::translatedName() const
{
    return i18n("Lingva");
}

TextTranslator::TranslatorEnginePlugin *LingvaEngineClient::createTranslator()
{
    auto enginePlugin = new LingvaEnginePlugin();
    connect(this, &LingvaEngineClient::configureChanged, enginePlugin, &LingvaEnginePlugin::slotConfigureChanged);
    return enginePlugin;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> LingvaEngineClient::supportedFromLanguages()
{
    if (mFromLanguages.isEmpty()) {
        mFromLanguages = fillLanguages();
    }
    return mFromLanguages;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> LingvaEngineClient::supportedToLanguages()
{
    return supportedFromLanguages();
}

bool LingvaEngineClient::hasConfigurationDialog() const
{
    return true;
}

bool LingvaEngineClient::showConfigureDialog(QWidget *parentWidget)
{
    bool settingsChanged = false;
    QPointer<LingvaEngineDialog> dlg = new LingvaEngineDialog(parentWidget);
    KConfigGroup myGroup(KSharedConfig::openConfig(), LingvaEngineUtil::groupName());
    QString lingvaUrl = myGroup.readEntry(LingvaEngineUtil::serverUrlKey(), LingvaEngineUtil::defaultServerUrl());
    if (lingvaUrl.isEmpty()) {
        lingvaUrl = LingvaEngineUtil::defaultServerUrl();
    }
    dlg->setServerUrl(lingvaUrl);
    if (dlg->exec()) {
        const QString serverUrl = dlg->serverUrl();
        myGroup.writeEntry(LingvaEngineUtil::serverUrlKey(), serverUrl);
        myGroup.sync();
        Q_EMIT configureChanged();
        settingsChanged = true;
    }
    delete dlg;
    return settingsChanged;
}

TextTranslator::TranslatorEngineClient::EngineType LingvaEngineClient::engineType() const
{
    return TextTranslator::TranslatorEngineClient::Network;
}

bool LingvaEngineClient::isSupported(TextTranslator::TranslatorUtil::Language lang) const
{
    switch (lang) {
    case TextTranslator::TranslatorUtil::ka:
    case TextTranslator::TranslatorUtil::tl:
        return false;
    default:
        break;
    }
    return true;
}

#include "moc_lingvaengineclient.cpp"
