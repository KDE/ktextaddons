/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "modelsmanager/ollamamodelinstalledinfo.h"
#include "textautogenerateollama_export.h"
#include <QDebug>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class OllamaReply;
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    explicit OllamaManager(QObject *parent = nullptr);
    ~OllamaManager() override;

    void loadModels() override;
    void getVersion();
    [[nodiscard]] OllamaReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);
    [[nodiscard]] OllamaReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);
    [[nodiscard]] OllamaReply *downloadModel(const QString &modelName);
    void deleteModel(const QString &modelName);

    void showModelInfo(const QString &modelName);

    [[nodiscard]] QList<OllamaModelInstalledInfo> installedInfos() const;
    void setInstalledInfos(const QList<OllamaModelInstalledInfo> &newInstalledInfos);

    [[nodiscard]] bool isAlreadyInstalled(const QString &modelName) const;

Q_SIGNALS:
    void finished(const QString &replyText);
    void downloadInProgress(const QString &modelName, const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info);

private:
    QMetaObject::Connection mOllamaCheckConnect;
    QList<OllamaModelInstalledInfo> mInstalledInfos;
};
