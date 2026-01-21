/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamacommonmodelavailableinfo.h"
#include "textautogenerateollamacommon_export.h"
#include <QObject>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableInfosManager : public QObject
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableInfosManager(QObject *parent = nullptr);
    ~OllamaCommonModelAvailableInfosManager() override;
    [[nodiscard]] bool loadAvailableModels();

    [[nodiscard]] QList<OllamaCommonModelAvailableInfo> modelInfos() const;
    void setModelInfos(const QList<OllamaCommonModelAvailableInfo> &newModelInfos);

    [[nodiscard]] OllamaCommonModelAvailableInfo modelInfo(const QString &modelName) const;

private:
    QList<OllamaCommonModelAvailableInfo> mModelInfos;
};
