/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratelmstudio_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class QDebug;
class QJsonObject;
class TEXTAUTOGENERATELMSTUDIO_EXPORT LMStudioModelInstalledInfo
{
public:
    LMStudioModelInstalledInfo();
    ~LMStudioModelInstalledInfo();

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QString publisher() const;
    void setPublisher(const QString &newPublisher);

    [[nodiscard]] QString model() const;
    void setModel(const QString &newModel);

    [[nodiscard]] QString quantizationLevel() const;
    void setQuantizationLevel(const QString &newQuantizationLevel);

    void parseInfo(const QJsonObject &obj);
    [[nodiscard]] QString parameterSize() const;
    void setParameterSize(const QString &newParameterSize);

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager::Categories categories() const;
    void setCategories(TextAutoGenerateText::TextAutoGenerateManager::Categories newCategories);

private:
    QString mName;
    QString mPublisher;
    QString mModel;
    QString mQuantizationLevel;
    QString mParameterSize;
    TextAutoGenerateText::TextAutoGenerateManager::Categories mCategories = TextAutoGenerateText::TextAutoGenerateManager::Category::Unknown;
};
Q_DECLARE_TYPEINFO(LMStudioModelInstalledInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const LMStudioModelInstalledInfo &t);
