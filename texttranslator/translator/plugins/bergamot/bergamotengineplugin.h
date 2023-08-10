/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "bergamotengineutils.h"

#include <TextTranslator/TranslatorEnginePlugin>
#include <TextTranslator/TranslatorUtil>
class BergamotMarianInterface;
class BergamotEnginePlugin : public TextTranslator::TranslatorEnginePlugin
{
    Q_OBJECT
public:
    explicit BergamotEnginePlugin(QObject *parent = nullptr);
    ~BergamotEnginePlugin() override;

    void translate() override;

    void slotConfigureChanged();

private:
    void loadSettings();
    void slotLanguagesChanged();
    void updateBergamotModel();
    BergamotMarianInterface *const mBergamotInterface;
    QVector<BergamotEngineUtils::LanguageInstalled> mInstalledLanguages;
    BergamotEngineUtils::SettingsInfo mSettingInfo;
    QString mModelLanguageName;
};
