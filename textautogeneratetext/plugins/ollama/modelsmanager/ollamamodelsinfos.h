/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QJsonObject>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelsInfos
{
public:
    OllamaModelsInfos();
    ~OllamaModelsInfos();

    void parseModelsInfo(const QJsonObject &obj);

    [[nodiscard]] QList<OllamaModelInfo> infos() const;
    void setInfos(const QList<OllamaModelInfo> &newInfos);

private:
    QList<OllamaModelInfo> mInfos;
};
Q_DECLARE_TYPEINFO(OllamaModelsInfos, Q_RELOCATABLE_TYPE);
