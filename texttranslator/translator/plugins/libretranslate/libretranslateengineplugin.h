/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextTranslator/TranslatorEnginePlugin>
namespace QKeychain
{
class Job;
}
class LibreTranslateEnginePlugin : public TextTranslator::TranslatorEnginePlugin
{
    Q_OBJECT
public:
    explicit LibreTranslateEnginePlugin(QObject *parent = nullptr);
    ~LibreTranslateEnginePlugin() override;

    void translate() override;

    void slotConfigureChanged();

private:
    void loadSettings();
    void parseTranslation(QNetworkReply *reply);
    void slotApiKeyRead(QKeychain::Job *baseJob);
    void translateText();
    QString mServerUrl;
    QString mResult;
    QString mApiKey;
    bool mRequiredApiKey = false;
};
