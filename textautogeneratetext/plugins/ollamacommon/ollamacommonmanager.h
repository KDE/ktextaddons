/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    explicit OllamaCommonManager(QObject *parent = nullptr);
    ~OllamaCommonManager() override;

    [[nodiscard]] virtual bool hasVisionSupport(const QString &modelName) const;
    [[nodiscard]] virtual bool hasToolsSupport(const QString &modelName) const;
    [[nodiscard]] virtual bool hasOcrSupport(const QString &modelName) const;
    [[nodiscard]] virtual bool hasAudioSupport(const QString &modelName) const;
    [[nodiscard]] virtual bool hasThinkSupport(const QString &modelName) const;

    [[nodiscard]] virtual QUrl instanceUrl() = 0;
    void showModelInfo(const QString &modelName);
    void getVersion();
};
