/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamaonline_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class QDebug;
class OllamaOnlineSettings;
class TEXTAUTOGENERATEOLLAMAONLINE_EXPORT OllamaOnlineManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    explicit OllamaOnlineManager(OllamaOnlineSettings *settings, QObject *parent = nullptr);
    ~OllamaOnlineManager() override;

    void loadModels() override;

    void getVersion();
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;

    void showModelInfo(const QString &modelName);

    [[nodiscard]] OllamaOnlineSettings *ollamaOnlineSettings() const;

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &newApiKey);

Q_SIGNALS:
    void downloadInProgress(const QString &modelName, const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info);
    void downloadError(const QString &modelName, const QString &errorStr);
    void errorOccurred(QNetworkReply::NetworkError e);

private:
    OllamaOnlineSettings *const mOllamaOnlineSettings;
    QString mApiKey;
};
