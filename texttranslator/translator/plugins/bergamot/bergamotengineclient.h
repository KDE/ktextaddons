/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

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

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;
    [[nodiscard]] TextTranslator::TranslatorEnginePlugin *createTranslator() override;
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedFromLanguages() override;
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedToLanguages() override;

    [[nodiscard]] bool hasConfigurationDialog() const override;

    [[nodiscard]] bool showConfigureDialog(QWidget *parentWidget) override;

    [[nodiscard]] bool hasInvertSupport() const override;

    void generateToListFromCurrentToLanguage(const QString &languageCode) override;

    [[nodiscard]] TextTranslator::TranslatorEngineClient::EngineType engineType() const override;

    void updateListLanguages() override;

protected:
    [[nodiscard]] bool isSupported(TextTranslator::TranslatorUtil::Language lang) const override;

private:
    void updateInstalledLanguage();
    void updateFromLanguageList();
    void updateToLanguageList();
    QMap<TextTranslator::TranslatorUtil::Language, QString> mToLanguages;
    QVector<BergamotEngineUtils::LanguageInstalled> mLanguageInstalled;
    QString mLanguageCode;
};
