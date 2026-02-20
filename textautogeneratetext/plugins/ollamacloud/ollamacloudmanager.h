/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamacommonmanager.h"
#include "ollamacommonmodelavailableinfo.h"
#include "textautogenerateollamacloud_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class QDebug;
class OllamaCloudSettings;
class TEXTAUTOGENERATEOLLAMACLOUD_EXPORT OllamaCloudManager : public OllamaCommonManager
{
    Q_OBJECT
public:
    explicit OllamaCloudManager(OllamaCloudSettings *settings, QObject *parent = nullptr);
    ~OllamaCloudManager() override;

    void loadModels() override;

    void getVersion();
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;

    [[nodiscard]] OllamaCloudSettings *ollamaCloudSettings() const;

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &newApiKey);

    [[nodiscard]] QList<OllamaCommonModelAvailableInfo> availableInfos() const;
    void setAvailableInfos(const QList<OllamaCommonModelAvailableInfo> &newAvailableInfos);

    [[nodiscard]] QUrl instanceUrl() override;

Q_SIGNALS:
    void errorOccurred(QNetworkReply::NetworkError e);

private:
    [[nodiscard]] TEXTAUTOGENERATEOLLAMACLOUD_NO_EXPORT QUrl ollamaCloudUrl() const;
    OllamaCloudSettings *const mOllamaCloudSettings;
    QString mApiKey;
    QList<OllamaCommonModelAvailableInfo> mAvailableInfos;
};
