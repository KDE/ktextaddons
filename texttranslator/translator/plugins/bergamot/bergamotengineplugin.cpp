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
}

BergamotEnginePlugin::~BergamotEnginePlugin() = default;

void BergamotEnginePlugin::translate()
{
    clear();
    mBergamotInterface->translate(inputText());
}

void BergamotEnginePlugin::loadSettings()
{
    BergamotEngineUtils::SettingsInfo settingInfo;
    settingInfo.loadSettingsInfo();
    // TODO fixme
    const QString filePath{BergamotEngineUtils::storageLanguagePath() + QStringLiteral("/enfr.student.tiny11/")};
    // TODO from();  to();
    if (QDir().exists(filePath)) {
        mBergamotInterface->setModel(filePath, settingInfo);
    }
}

void BergamotEnginePlugin::slotConfigureChanged()
{
    loadSettings();
}
