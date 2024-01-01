/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "texttranslator_export.h"
#include <QObject>
#include <TextTranslator/TranslatorUtil>
#include <memory>
namespace TextTranslator
{
class TranslatorEngineLoaderPrivate;
class TranslatorEngineClient;
class TEXTTRANSLATOR_EXPORT TranslatorEngineLoader : public QObject
{
    Q_OBJECT
public:
    static TranslatorEngineLoader *self();

    explicit TranslatorEngineLoader(QObject *parent = nullptr);
    ~TranslatorEngineLoader() override;

    [[nodiscard]] TextTranslator::TranslatorEngineClient *createTranslatorClient(const QString &clientName);

    // engine name, i18n
    [[nodiscard]] QMap<QString, QString> translatorEngineInfos() const;

    [[nodiscard]] QString currentPluginName(const QString &key) const;

    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedFromLanguages(const QString &clientName) const;
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> supportedToLanguages(const QString &clientName) const;

    [[nodiscard]] bool hasConfigurationDialog(const QString &clientName) const;

    [[nodiscard]] QString fallbackFirstEngine() const;

    [[nodiscard]] bool showConfigureDialog(const QString &clientName, QWidget *parentWidget);

Q_SIGNALS:
    void loadingTranslatorFailed();

private:
    TEXTTRANSLATOR_NO_EXPORT void loadPlugins();
    TEXTTRANSLATOR_NO_EXPORT void loadPlugin(const QString &pluginPath);
    std::unique_ptr<TranslatorEngineLoaderPrivate> const d;
};
}
