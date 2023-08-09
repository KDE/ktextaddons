/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

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

    Q_REQUIRED_RESULT TextTranslator::TranslatorEngineClient *createTranslatorClient(const QString &clientName);

    // engine name, i18n
    Q_REQUIRED_RESULT QMap<QString, QString> translatorEngineInfos() const;

    Q_REQUIRED_RESULT QMap<TextTranslator::TranslatorUtil::Language, QString> supportedFromLanguages(const QString &clientName) const;
    Q_REQUIRED_RESULT QMap<TextTranslator::TranslatorUtil::Language, QString> supportedToLanguages(const QString &clientName) const;

    Q_REQUIRED_RESULT bool hasConfigurationDialog(const QString &clientName) const;

    Q_REQUIRED_RESULT QString fallbackFirstEngine() const;

    Q_REQUIRED_RESULT bool showConfigureDialog(const QString &clientName, QWidget *parentWidget);

Q_SIGNALS:
    void loadingTranslatorFailed();

private:
    TEXTTRANSLATOR_NO_EXPORT void loadPlugins();
    TEXTTRANSLATOR_NO_EXPORT void loadPlugin(const QString &pluginPath);
    std::unique_ptr<TranslatorEngineLoaderPrivate> const d;
};
}
