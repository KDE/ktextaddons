/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineclient.h"
#include "begamotenginedialog.h"
#include "bergamotengineplugin.h"
#include "bergamotengineutils.h"
#include "translator/misc/translatorutil.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QPointer>

BergamotEngineClient::BergamotEngineClient(QObject *parent)
    : TextTranslator::TranslatorEngineClient{parent}
{
    updateInstalledLanguage();
}

BergamotEngineClient::~BergamotEngineClient() = default;

QString BergamotEngineClient::name() const
{
    return QStringLiteral("bergamot");
}

QString BergamotEngineClient::translatedName() const
{
    return i18n("Bergamot");
}

TextTranslator::TranslatorEnginePlugin *BergamotEngineClient::createTranslator()
{
    return new BergamotEnginePlugin();
}

QMap<TextTranslator::TranslatorUtil::Language, QString> BergamotEngineClient::supportedFromLanguages()
{
    return mFromLanguages;
}

QMap<TextTranslator::TranslatorUtil::Language, QString> BergamotEngineClient::supportedToLanguages()
{
    return mToLanguages;
}

bool BergamotEngineClient::hasConfigurationDialog() const
{
    return true;
}

void BergamotEngineClient::showConfigureDialog(QWidget *parentWidget)
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), BergamotEngineUtils::groupName());
    QPointer<BegamotEngineDialog> dlg = new BegamotEngineDialog(parentWidget);
    BergamotEngineUtils::SettingsInfo info;
    info.loadSettingsInfo();
    dlg->setSettingsInfo(info);
    if (dlg->exec()) {
        info = dlg->settingsInfo();
        info.saveSettingsInfo();
        updateInstalledLanguage();
        Q_EMIT configureChanged();
    }
    delete dlg;
}

void BergamotEngineClient::updateInstalledLanguage()
{
    mLanguageInstalled = BergamotEngineUtils::languageLocallyStored(QDir(BergamotEngineUtils::storageLanguagePath()));
    updateFromLanguageList();
    updateToLanguageList();
}

void BergamotEngineClient::updateFromLanguageList()
{
    mFromLanguages.clear();
    for (const auto &lang : std::as_const(mLanguageInstalled)) {
        const TextTranslator::TranslatorUtil::Language langUtil = TextTranslator::TranslatorUtil::stringToLanguage(lang.from);
        mFromLanguages.insert(langUtil, TextTranslator::TranslatorUtil::translatedLanguage(langUtil));
    }
}

void BergamotEngineClient::updateToLanguageList()
{
    mToLanguages.clear();
    for (const auto &lang : std::as_const(mLanguageInstalled)) {
        const TextTranslator::TranslatorUtil::Language langUtil = TextTranslator::TranslatorUtil::stringToLanguage(lang.to);
        qDebug() << " lang.to " << lang.to;
        mToLanguages.insert(langUtil, TextTranslator::TranslatorUtil::translatedLanguage(langUtil));
    }
}

bool BergamotEngineClient::hasInvertSupport() const
{
    return false;
}

void BergamotEngineClient::generateToListFromCurrentToLanguage()
{
    // TODO
}

bool BergamotEngineClient::isSupported(TextTranslator::TranslatorUtil::Language lang) const
{
    return true;
}

#include "moc_bergamotengineclient.cpp"
