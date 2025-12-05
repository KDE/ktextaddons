/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelavailableinfo.h"
#include "textautogenerateollama_private_export.h"
class QJsonObject;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelsAvalableInfos
{
public:
    OllamaModelsAvalableInfos();
    ~OllamaModelsAvalableInfos();

    void parseModelsInfo(const QJsonObject &obj);

    [[nodiscard]] QList<OllamaModelAvailableInfo> infos() const;
    void setInfos(const QList<OllamaModelAvailableInfo> &newInfos);

private:
    QList<OllamaModelAvailableInfo> mInfos;
};
Q_DECLARE_TYPEINFO(OllamaModelsAvalableInfos, Q_RELOCATABLE_TYPE);
