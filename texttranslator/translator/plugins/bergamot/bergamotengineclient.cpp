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

QMap<TextTranslator::TranslatorUtil::Language, QString> BergamotEngineClient::supportedLanguages()
{
    if (mLanguages.isEmpty()) {
        mLanguages = fillLanguages();
    }
    return mLanguages;
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
        Q_EMIT configureChanged();
    }
    delete dlg;
}

bool BergamotEngineClient::hasInverteSupport() const
{
    return false;
}

bool BergamotEngineClient::isSupported(TextTranslator::TranslatorUtil::Language lang) const
{
    // TODO
    return true;
}

#include "moc_bergamotengineclient.cpp"
