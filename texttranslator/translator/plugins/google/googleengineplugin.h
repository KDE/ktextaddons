/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextTranslator/TranslatorEnginePlugin>
#include <TextTranslator/TranslatorUtil>
class QNetworkReply;
class GoogleEnginePlugin : public TextTranslator::TranslatorEnginePlugin
{
public:
    explicit GoogleEnginePlugin(QObject *parent = nullptr);
    ~GoogleEnginePlugin() override;

    void translate() override;

    [[nodiscard]] QString languageCode(const QString &langStr) override;

private:
    void slotTranslateFinished(QNetworkReply *reply);
    QString mJsonData;
    QString mResult;
};
