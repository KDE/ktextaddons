/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "bergamotengineutils.h"

#include <TextTranslator/TranslatorEngineClient>

class BergamotEngineClient : public TextTranslator::TranslatorEngineClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.Translator.bergamot")
    Q_INTERFACES(TextTranslator::TranslatorEngineClient)
public:
    explicit BergamotEngineClient(QObject *parent = nullptr);
    ~BergamotEngineClient() override;

    Q_REQUIRED_RESULT QString name() const override;
    Q_REQUIRED_RESULT QString translatedName() const override;
    Q_REQUIRED_RESULT TextTranslator::TranslatorEnginePlugin *createTranslator() override;
    Q_REQUIRED_RESULT QMap<TextTranslator::TranslatorUtil::Language, QString> supportedFromLanguages() override;
    Q_REQUIRED_RESULT QMap<TextTranslator::TranslatorUtil::Language, QString> supportedToLanguages() override;

    Q_REQUIRED_RESULT bool hasConfigurationDialog() const override;

    void showConfigureDialog(QWidget *parentWidget) override;

    Q_REQUIRED_RESULT bool hasInvertSupport() const override;

protected:
    Q_REQUIRED_RESULT bool isSupported(TextTranslator::TranslatorUtil::Language lang) const override;

private:
    void updateInstalledLanguage();
    void updateFromLanguageList();
    void updateToLanguageList();
    QMap<TextTranslator::TranslatorUtil::Language, QString> mToLanguages;
    QVector<BergamotEngineUtils::LanguageInstalled> mLanguageInstalled;
};
