/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QObject>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInfosManager : public QObject
{
    Q_OBJECT
public:
    explicit OllamaModelInfosManager(QObject *parent = nullptr);
    ~OllamaModelInfosManager() override;
    [[nodiscard]] bool loadAvailableModels();

    [[nodiscard]] QList<OllamaModelInfo> modelInfos() const;
    void setModelInfos(const QList<OllamaModelInfo> &newModelInfos);

private:
    QList<OllamaModelInfo> mModelInfos;
};
