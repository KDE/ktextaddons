/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QStringList>
#include <TextTranslator/TranslatorEngineClient>
namespace QKeychain
{
class Job;
}
class LibreTranslateEngineClient : public TextTranslator::TranslatorEngineClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.Translator.libretranslate")
    Q_INTERFACES(TextTranslator::TranslatorEngineClient)
public:
    explicit LibreTranslateEngineClient(QObject *parent = nullptr);
    ~LibreTranslateEngineClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;
    [[nodiscard]] TextTranslator::TranslatorEnginePlugin *createTranslator() override;
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedFromLanguages() override;
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedToLanguages() override;

    [[nodiscard]] bool hasConfigurationDialog() const override;
    [[nodiscard]] bool showConfigureDialog(QWidget *parentWidget) override;
    [[nodiscard]] TextTranslator::TranslatorEngineClient::EngineType engineType() const override;

    void generateToListFromCurrentToLanguage(const QString &languageCode) override;

protected:
    [[nodiscard]] bool isSupported(TextTranslator::TranslatorUtil::Language lang) const override;

private:
    void slotPasswordWritten(QKeychain::Job *baseJob);
    void slotLanguagesLoaded(const QString &serverUrl, const QMap<QString, QStringList> &languages);
    void resetLanguages();
    void loadLanguages();
    void updateToLanguageList();
    [[nodiscard]] static QString serverUrl();
    // Source language code -> target language codes, as returned by the server
    QMap<QString, QStringList> mLanguageTargets;
    QMap<TextTranslator::TranslatorUtil::Language, QString> mToLanguages;
    QString mLanguageCode;
    bool mLanguagesRequested = false;
};
