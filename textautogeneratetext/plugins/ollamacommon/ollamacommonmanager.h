/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <TextAutoGenerateText/TextAutoGenerateManager>
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    explicit OllamaCommonManager(QObject *parent = nullptr);
    ~OllamaCommonManager() override;

    [[nodiscard]] bool hasVisionSupport(const QString &modelName) const;
    [[nodiscard]] bool hasToolsSupport(const QString &modelName) const;
    [[nodiscard]] bool hasOcrSupport(const QString &modelName) const;
    [[nodiscard]] bool hasAudioSupport(const QString &modelName) const;
    [[nodiscard]] bool hasThinkSupport(const QString &modelName) const;

    [[nodiscard]] virtual QUrl instanceUrl() = 0;
    void showModelInfo(const QString &modelName);
    void getVersion();
    [[nodiscard]] virtual bool hasCategorySupport(const QString &modelName, TextAutoGenerateText::TextAutoGenerateManager::Category cat) const;
};
