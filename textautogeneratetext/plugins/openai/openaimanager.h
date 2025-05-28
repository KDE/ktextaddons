/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateopenai_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class OpenAIReply;
class TEXTAUTOGENERATEOPENAI_EXPORT OpenAIManager : public QObject
{
    Q_OBJECT
public:
    struct ModelsInfo {
        QStringList models;
        QString errorOccured;
        bool hasError = false;
        bool isReady = false;
    };
    explicit OpenAIManager(QObject *parent = nullptr);
    ~OpenAIManager() override;
    void loadModels();

    [[nodiscard]] OpenAIReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &newApiKey);

Q_SIGNALS:
    void modelsLoadDone(const ModelsInfo &models);
    void finished(const QString &replyText);

private:
    QString mApiKey;
};
