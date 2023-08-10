/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineplugin.h"
#include "bergamotmarianinterface.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>

BergamotEnginePlugin::BergamotEnginePlugin(QObject *parent)
    : TextTranslator::TranslatorEnginePlugin(parent)
    , mBergamotInterface(new BergamotMarianInterface(this))
{
    loadSettings();

    connect(mBergamotInterface, &BergamotMarianInterface::errorText, this, [this](const QString &message) {
        Q_EMIT translateFailed(message);
    });
    connect(mBergamotInterface, &BergamotMarianInterface::translationReady, this, [&](Translation translation) {
        appendResult(translation.translation());
        Q_EMIT translateDone();
    });
    connect(this, &BergamotEnginePlugin::languagesChanged, this, &BergamotEnginePlugin::slotLanguagesChanged);
}

BergamotEnginePlugin::~BergamotEnginePlugin() = default;

void BergamotEnginePlugin::translate()
{
    clear();
    mBergamotInterface->translate(inputText());
}

void BergamotEnginePlugin::loadSettings()
{
    mInstalledLanguages = BergamotEngineUtils::languageLocallyStored();
    mSettingInfo.loadSettingsInfo();
    updateBergamotModel();
}

void BergamotEnginePlugin::updateBergamotModel()
{
    QString absolutePath;
    for (const auto &installed : std::as_const(mInstalledLanguages)) {
        if (installed.from == from() && installed.to == to()) {
            absolutePath = installed.absoluteLanguageModelPath;
            break;
        }
    }
    if (QDir().exists(absolutePath)) {
        mBergamotInterface->setModel(absolutePath, mSettingInfo);
    }
}

void BergamotEnginePlugin::slotConfigureChanged()
{
    loadSettings();
}

void BergamotEnginePlugin::slotLanguagesChanged()
{
    updateBergamotModel();
}
