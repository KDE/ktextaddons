/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelavailableinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QObject>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableInfosManager : public QObject
{
    Q_OBJECT
public:
    explicit OllamaModelAvailableInfosManager(QObject *parent = nullptr);
    ~OllamaModelAvailableInfosManager() override;
    [[nodiscard]] bool loadAvailableModels();

    [[nodiscard]] QList<OllamaModelAvailableInfo> modelInfos() const;
    void setModelInfos(const QList<OllamaModelAvailableInfo> &newModelInfos);

    [[nodiscard]] OllamaModelAvailableInfo modelInfo(const QString &modelName) const;

private:
    QList<OllamaModelAvailableInfo> mModelInfos;
};
