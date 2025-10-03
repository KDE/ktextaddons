/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "modelsmanager/ollamamodelavailableinfo.h"
#include "modelsmanager/ollamamodelinstalledinfo.h"
#include "textautogenerateollama_export.h"
#include <QDebug>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class OllamaReply;
class OllamaSettings;
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    struct TEXTAUTOGENERATEOLLAMA_EXPORT CreateModelInfo {
        QString modelName;
        QString fromModelName;
        QString systemPrompt;
        [[nodiscard]] bool isValid() const;
    };

    explicit OllamaManager(OllamaSettings *settings, QObject *parent = nullptr);
    ~OllamaManager() override;

    void loadModels() override;
    void getVersion();
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
    [[nodiscard]] OllamaReply *downloadModel(const QString &modelName);
    void deleteModel(const QString &modelName);

    void showModelInfo(const QString &modelName);

    void createModel(const CreateModelInfo &info);

    [[nodiscard]] QList<OllamaModelInstalledInfo> installedInfos() const;
    void setInstalledInfos(const QList<OllamaModelInstalledInfo> &newInstalledInfos);

    [[nodiscard]] bool isAlreadyInstalled(const QString &modelName) const;

    [[nodiscard]] OllamaSettings *ollamaSettings() const;

    [[nodiscard]] QList<OllamaModelAvailableInfo> availableInfos() const;
    void setAvailableInfos(const QList<OllamaModelAvailableInfo> &newAvailableInfos);

    [[nodiscard]] bool hasVisionSupport(const QString &modelName) const;
    [[nodiscard]] bool hasToolsSupport(const QString &modelName) const;
Q_SIGNALS:
    void downloadInProgress(const QString &modelName, const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info);

private:
    [[nodiscard]] TEXTAUTOGENERATEOLLAMA_NO_EXPORT bool hasCategorySupport(const QString &modelName,
                                                                           TextAutoGenerateText::TextAutoGenerateManager::Category cat) const;
    QList<OllamaModelInstalledInfo> mInstalledInfos;
    QList<OllamaModelAvailableInfo> mAvailableInfos;
    OllamaSettings *const mOllamaSettings;
};
Q_DECLARE_TYPEINFO(OllamaManager::CreateModelInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATEOLLAMA_EXPORT QDebug operator<<(QDebug d, const OllamaManager::CreateModelInfo &t);
