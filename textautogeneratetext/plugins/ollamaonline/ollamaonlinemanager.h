/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamacommonmanager.h"
#include "ollamacommonmodelavailableinfo.h"
#include "textautogenerateollamaonline_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class QDebug;
class OllamaOnlineSettings;
class TEXTAUTOGENERATEOLLAMAONLINE_EXPORT OllamaOnlineManager : public OllamaCommonManager
{
    Q_OBJECT
public:
    explicit OllamaOnlineManager(OllamaOnlineSettings *settings, QObject *parent = nullptr);
    ~OllamaOnlineManager() override;

    void loadModels() override;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;

    [[nodiscard]] OllamaOnlineSettings *ollamaOnlineSettings() const;

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &newApiKey);

    [[nodiscard]] QList<OllamaCommonModelAvailableInfo> availableInfos() const;
    void setAvailableInfos(const QList<OllamaCommonModelAvailableInfo> &newAvailableInfos);
    [[nodiscard]] QUrl instanceUrl() override;

Q_SIGNALS:
    void errorOccurred(QNetworkReply::NetworkError e);

private:
    [[nodiscard]] TEXTAUTOGENERATEOLLAMAONLINE_NO_EXPORT bool hasCategorySupport(const QString &modelName,
                                                                                 TextAutoGenerateText::TextAutoGenerateManager::Category cat) const override;
    OllamaOnlineSettings *const mOllamaOnlineSettings;
    QString mApiKey;
    QList<OllamaCommonModelAvailableInfo> mAvailableInfos;
};
