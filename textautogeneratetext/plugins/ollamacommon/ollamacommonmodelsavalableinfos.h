/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamacommonmodelavailableinfo.h"
#include "textautogenerateollamacommon_export.h"
class QJsonObject;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelsAvalableInfos
{
public:
    OllamaCommonModelsAvalableInfos();
    ~OllamaCommonModelsAvalableInfos();

    void parseModelsInfo(const QJsonObject &obj);

    [[nodiscard]] QList<OllamaCommonModelAvailableInfo> infos() const;
    void setInfos(const QList<OllamaCommonModelAvailableInfo> &newInfos);

private:
    QList<OllamaCommonModelAvailableInfo> mInfos;
};
Q_DECLARE_TYPEINFO(OllamaCommonModelsAvalableInfos, Q_RELOCATABLE_TYPE);
