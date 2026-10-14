/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateplugincommon_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class QDebug;
class QJsonObject;
class TEXTAUTOGENERATEPLUGINCOMMON_EXPORT PluginCommonModelInstalledInfo
{
public:
    virtual ~PluginCommonModelInstalledInfo() = default;

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QString model() const;
    void setModel(const QString &newModel);

    [[nodiscard]] QString quantizationLevel() const;
    void setQuantizationLevel(const QString &newQuantizationLevel);

    [[nodiscard]] QString parameterSize() const;
    void setParameterSize(const QString &newParameterSize);

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager::Categories categories() const;
    void setCategories(TextAutoGenerateText::TextAutoGenerateManager::Categories newCategories);

    // Need to be override for each provider because the result JSON can be different
    virtual void parseInfo(const QJsonObject &obj) = 0;

protected:
    QString mName;
    QString mModel;
    QString mQuantizationLevel;
    QString mParameterSize;
    TextAutoGenerateText::TextAutoGenerateManager::Categories mCategories = TextAutoGenerateText::TextAutoGenerateManager::Category::Unknown;
};
TEXTAUTOGENERATEPLUGINCOMMON_EXPORT QDebug operator<<(QDebug d, const PluginCommonModelInstalledInfo &t);
