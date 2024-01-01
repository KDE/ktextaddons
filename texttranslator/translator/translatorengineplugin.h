/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "texttranslator_export.h"
#include <QNetworkReply>
#include <QObject>
#include <QString>
#include <TextTranslator/TranslatorUtil>
#include <memory>

namespace TextTranslator
{
class TranslatorEnginePluginPrivate;
class TEXTTRANSLATOR_EXPORT TranslatorEnginePlugin : public QObject
{
    Q_OBJECT
public:
    explicit TranslatorEnginePlugin(QObject *parent = nullptr);
    ~TranslatorEnginePlugin() override;

    virtual void translate() = 0;

    [[nodiscard]] QString resultTranslate() const;
    void setInputText(const QString &text);
    void setFrom(const QString &language);
    void setTo(const QString &language);
    void setResult(const QString &result);
    void setJsonDebug(const QString &debug);

    [[nodiscard]] QString inputText() const;
    [[nodiscard]] QString from() const;
    [[nodiscard]] QString to() const;
    [[nodiscard]] QString result() const;
    [[nodiscard]] QString jsonDebug() const;

    void clear();

Q_SIGNALS:
    void translateDone();
    void translateFailed(const QString &errorMessage);
    void languagesChanged();

protected:
    void appendResult(const QString &result);
    void slotError(QNetworkReply::NetworkError error);
    [[nodiscard]] bool verifyFromAndToLanguage();
    [[nodiscard]] bool hasDebug() const;

    [[nodiscard]] virtual QString languageCode(const QString &langStr);

private:
    std::unique_ptr<TranslatorEnginePluginPrivate> const d;
};
}
