/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineplugin.h"
#include "bergamotmarianinterface.h"
#include "bergamottranslator_debug.h"
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDir>

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
    // The settings may have changed the way the model has to be loaded, so forget
    // about the model currently in use and load it again.
    mModelLanguageName.clear();
    updateBergamotModel();
}

void BergamotEnginePlugin::updateBergamotModel()
{
    if (from().isEmpty() || to().isEmpty()) {
        return;
    }
    QString absolutePath;
    for (const auto &installed : std::as_const(mInstalledLanguages)) {
        if (installed.from == from() && installed.to == to()) {
            absolutePath = installed.absoluteLanguageModelPath;
            break;
        }
    }
    if (!absolutePath.isEmpty() && !QDir().exists(absolutePath)) {
        qCWarning(TRANSLATOR_BERGAMOT_LOG) << "Language model directory is gone:" << absolutePath;
        absolutePath.clear();
    }
    if (absolutePath.isEmpty()) {
        // Unload the current model, otherwise we would keep translating with the
        // previously selected language pair.
        qCWarning(TRANSLATOR_BERGAMOT_LOG) << "No language model installed for" << from() << "->" << to();
        mModelLanguageName.clear();
        mBergamotInterface->setModel({}, mSettingInfo);
        return;
    }
    // Loading a model is expensive: from() and to() are set one after the other,
    // so skip the reload when we already use this very model.
    if (mModelLanguageName == absolutePath) {
        return;
    }
    mModelLanguageName = absolutePath;
    mBergamotInterface->setModel(absolutePath, mSettingInfo);
}

void BergamotEnginePlugin::slotConfigureChanged()
{
    loadSettings();
}

void BergamotEnginePlugin::slotLanguagesChanged()
{
    updateBergamotModel();
}

#include "moc_bergamotengineplugin.cpp"
