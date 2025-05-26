/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollama_export.h"
#include <QDebug>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
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
    [[nodiscard]] OllamaReply *downloadModel(const QString &modelName);
    void deleteModel(const QString &modelName);

    void showModelInfo(const QString &modelName);
    [[nodiscard]] QStringList listModels() const;

Q_SIGNALS:
    void modelsLoadDone(const ModelsInfo &models);
    void finished(const QString &replyText);
    void downloadInProgress(const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info);

private:
    QMetaObject::Connection mOllamaCheckConnect;
    QStringList mListModels;
};
Q_DECLARE_TYPEINFO(OllamaManager::ModelsInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const OllamaManager::ModelsInfo &t);
