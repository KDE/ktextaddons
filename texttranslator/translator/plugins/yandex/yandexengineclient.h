/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextTranslator/TranslatorEngineClient>

class YandexEngineClient : public TextTranslator::TranslatorEngineClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.Translator.yandex")
    Q_INTERFACES(TextTranslator::TranslatorEngineClient)
public:
    explicit YandexEngineClient(QObject *parent = nullptr);
    ~YandexEngineClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;
    [[nodiscard]] TextTranslator::TranslatorEnginePlugin *createTranslator() override;
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedFromLanguages() override;
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedToLanguages() override;
    [[nodiscard]] TextTranslator::TranslatorEngineClient::EngineType engineType() const override;

protected:
    [[nodiscard]] bool isSupported(TextTranslator::TranslatorUtil::Language lang) const override;
};
