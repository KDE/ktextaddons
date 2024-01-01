/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextTranslator/TranslatorEnginePlugin>

class BingEnginePlugin : public TextTranslator::TranslatorEnginePlugin
{
    Q_OBJECT
public:
    explicit BingEnginePlugin(QObject *parent = nullptr);
    ~BingEnginePlugin() override;

    void translate() override;

    [[nodiscard]] QString languageCode(const QString &langStr) override;

private:
    void parseCredentials(QNetworkReply *reply);
    void translateText();
    void parseTranslation(QNetworkReply *reply);
    static QByteArray sBingKey;
    static QByteArray sBingToken;
    static QString sBingIg;
    static QString sBingIid;
};
