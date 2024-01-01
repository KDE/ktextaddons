/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextTranslator/TranslatorEngineClient>

class LingvaEngineClient : public TextTranslator::TranslatorEngineClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.Translator.lingva")
    Q_INTERFACES(TextTranslator::TranslatorEngineClient)
public:
    explicit LingvaEngineClient(QObject *parent = nullptr);
    ~LingvaEngineClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;
    [[nodiscard]] TextTranslator::TranslatorEnginePlugin *createTranslator() override;
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedFromLanguages() override;
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedToLanguages() override;

    [[nodiscard]] bool hasConfigurationDialog() const override;
    [[nodiscard]] bool showConfigureDialog(QWidget *parentWidget) override;
    [[nodiscard]] TextTranslator::TranslatorEngineClient::EngineType engineType() const override;

protected:
    [[nodiscard]] bool isSupported(TextTranslator::TranslatorUtil::Language lang) const override;
};
