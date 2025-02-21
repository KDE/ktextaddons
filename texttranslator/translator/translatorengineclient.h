/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include "texttranslator_export.h"
#include <QMap>
#include <TextTranslator/TranslatorUtil>
namespace TextTranslator
{
class TranslatorEnginePlugin;
class TEXTTRANSLATOR_EXPORT TranslatorEngineClient : public QObject
{
    Q_OBJECT
public:
    enum EngineType {
        Local,
        Network,
    };
    explicit TranslatorEngineClient(QObject *parent = nullptr);
    ~TranslatorEngineClient() override;

    /**
     * @returns the name of the implementing class.
     */
    virtual QString name() const = 0;

    virtual QString translatedName() const = 0;

    virtual TranslatorEnginePlugin *createTranslator() = 0;

    [[nodiscard]] virtual QMap<TranslatorUtil::Language, QString> supportedFromLanguages() = 0;
    [[nodiscard]] virtual QMap<TranslatorUtil::Language, QString> supportedToLanguages() = 0;
    virtual void updateListLanguages();

    [[nodiscard]] virtual bool hasConfigurationDialog() const;

    virtual bool showConfigureDialog(QWidget *parentWidget);
    virtual void generateToListFromCurrentToLanguage(const QString &languageCode);

    [[nodiscard]] virtual bool hasInvertSupport() const;

    [[nodiscard]] virtual TextTranslator::TranslatorEngineClient::EngineType engineType() const = 0;

    [[nodiscard]] static QString convertEngineType(TextTranslator::TranslatorEngineClient::EngineType type);

Q_SIGNALS:
    void configureChanged();

protected:
    [[nodiscard]] QMap<TextTranslator::TranslatorUtil::Language, QString> fillLanguages();
    [[nodiscard]] virtual bool isSupported(TextTranslator::TranslatorUtil::Language lang) const = 0;
    QMap<TranslatorUtil::Language, QString> mFromLanguages;
};
}
Q_DECLARE_INTERFACE(TextTranslator::TranslatorEngineClient, "org.kde.translator.Client")
