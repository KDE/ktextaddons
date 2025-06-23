/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineclient.h"
using namespace Qt::Literals::StringLiterals;

#include "begamotenginedialog.h"
#include "bergamotengineplugin.h"
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
    return u"bergamot"_s;
}

QString BergamotEngineClient::translatedName() const
{
    return i18n("Bergamot");
}

TextTranslator::TranslatorEnginePlugin *BergamotEngineClient::createTranslator()
{
    auto enginePlugin = new BergamotEnginePlugin();
    connect(this, &BergamotEngineClient::configureChanged, enginePlugin, &BergamotEnginePlugin::slotConfigureChanged);
    return enginePlugin;
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

bool BergamotEngineClient::showConfigureDialog(QWidget *parentWidget)
{
    bool settingsChanged = false;
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
        settingsChanged = true;
    }
    delete dlg;
    return settingsChanged;
}

void BergamotEngineClient::updateInstalledLanguage()
{
    mLanguageInstalled = BergamotEngineUtils::languageLocallyStored();
    updateFromLanguageList();
    updateToLanguageList();
}

void BergamotEngineClient::updateFromLanguageList()
{
    mFromLanguages.clear();
    for (const auto &lang : std::as_const(mLanguageInstalled)) {
        const TextTranslator::TranslatorUtil::Language langUtil = TextTranslator::TranslatorUtil::stringToLanguage(lang.from);
        mFromLanguages.insert(langUtil, TextTranslator::TranslatorUtil::translatedLanguage(langUtil));
        // qDebug() << " SSSSSSSSSSSSSSSSSS " << langUtil << " mFromLanguages " << mFromLanguages;
    }
}

void BergamotEngineClient::updateToLanguageList()
{
    mToLanguages.clear();
    for (const auto &lang : std::as_const(mLanguageInstalled)) {
        // qDebug() << " lang.to " << lang.to << " mLanguageCode " << mLanguageCode;
        if (lang.to == mLanguageCode || mLanguageCode.isEmpty()) {
            const TextTranslator::TranslatorUtil::Language langUtil = TextTranslator::TranslatorUtil::stringToLanguage(lang.to);
            // qDebug() << " lang.to " << lang.to;
            mToLanguages.insert(langUtil, TextTranslator::TranslatorUtil::translatedLanguage(langUtil));
        }
    }
}

bool BergamotEngineClient::hasInvertSupport() const
{
    return false;
}

void BergamotEngineClient::generateToListFromCurrentToLanguage(const QString &languageCode)
{
    mLanguageCode = languageCode;
    updateToLanguageList();
}

TextTranslator::TranslatorEngineClient::EngineType BergamotEngineClient::engineType() const
{
    return TextTranslator::TranslatorEngineClient::Locale;
}

bool BergamotEngineClient::isSupported(TextTranslator::TranslatorUtil::Language lang) const
{
    Q_UNUSED(lang);
    return true;
}

void BergamotEngineClient::updateListLanguages()
{
    updateInstalledLanguage();
}

#include "moc_bergamotengineclient.cpp"
