/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "lmstudiosettings.h"
#include "modelsmanager/lmstudiomodelinstalledinfo.h"
#include "textautogeneratelmstudio_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateManager>
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextRequest>
class QDebug;
class LMStudioSettings;
class LMStudioStartProcessJob;
class TEXTAUTOGENERATELMSTUDIO_EXPORT LMStudioManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    explicit LMStudioManager(LMStudioSettings *settings, QObject *parent = nullptr);
    ~LMStudioManager() override;

    void loadModels() override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getResponses(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;

    [[nodiscard]] LMStudioSettings *lmStudioSettings() const;

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &newApiKey);

    [[nodiscard]] QList<LMStudioModelInstalledInfo> installedInfos() const;
    void setInstalledInfos(const QList<LMStudioModelInstalledInfo> &newInstalledInfos);

    [[nodiscard]] bool hasVisionSupport(const QString &modelName) const;
    [[nodiscard]] bool hasToolsSupport(const QString &modelName) const;
    [[nodiscard]] bool hasOcrSupport(const QString &modelName) const;
    [[nodiscard]] bool hasAudioSupport(const QString &modelName) const;
    [[nodiscard]] bool hasThinkSupport(const QString &modelName) const;

    void startLMStudio();

    [[nodiscard]] QByteArray lsmStudioOutputData() const;
    [[nodiscard]] bool isLMStudioStarted() const;
Q_SIGNALS:
    void errorOccurred(QNetworkReply::NetworkError e);
    void lmsStarted();
    void lmsFailed(const QString &errorStr);

private:
    [[nodiscard]] TEXTAUTOGENERATELMSTUDIO_NO_EXPORT bool hasCategorySupport(const QString &modelName,
                                                                             TextAutoGenerateText::TextAutoGenerateManager::Category cat) const;
    QList<LMStudioModelInstalledInfo> mInstalledInfos;
    QString mApiKey;
    LMStudioSettings *const mLMStudioSettings;
    LMStudioStartProcessJob *mLMStudioStartProcessJob = nullptr;
};
QDebug operator<<(QDebug d, const LMStudioManager &t);
