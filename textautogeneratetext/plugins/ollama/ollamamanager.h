/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollama_export.h"
#include <QDebug>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class OllamaReply;
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaManager : public QObject
{
    Q_OBJECT
public:
    struct ModelsInfo {
        QStringList models;
        QString errorOccured;
        bool hasError = false;
        bool isReady = false;
    };

    explicit OllamaManager(QObject *parent = nullptr);
    ~OllamaManager() override;

    void loadModels();
    void getVersion();
    [[nodiscard]] OllamaReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);
    [[nodiscard]] OllamaReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);
    void downloadModel(const QString &modelName);
    void deleteModel(const QString &modelName);

    void showModelInfo(const QString &modelName);
Q_SIGNALS:
    void modelsLoadDone(const ModelsInfo &models);
    void finished(const QString &replyText);

private:
    QMetaObject::Connection mOllamaCheckConnect;
};
Q_DECLARE_TYPEINFO(OllamaManager::ModelsInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const OllamaManager::ModelsInfo &t);
