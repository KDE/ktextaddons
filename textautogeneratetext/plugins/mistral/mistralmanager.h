/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratemistral_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class MistralReply;
class TEXTAUTOGENERATEMISTRAL_EXPORT MistralManager : public QObject
{
    Q_OBJECT
public:
    struct ModelsInfo {
        QStringList models;
        QString errorOccured;
        bool hasError = false;
        bool isReady = false;
    };
    explicit MistralManager(QObject *parent = nullptr);
    ~MistralManager() override;
    void loadModels();

    [[nodiscard]] MistralReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);

    [[nodiscard]] QByteArray apiKey() const;
    void setApiKey(const QByteArray &newApiKey);

Q_SIGNALS:
    void modelsLoadDone(const ModelsInfo &models);
    void finished(const QString &replyText);

private:
    QByteArray mApiKey;
};
