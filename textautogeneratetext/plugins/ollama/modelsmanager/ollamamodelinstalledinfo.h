/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QDebug>
#include <QJsonObject>
#include <QString>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInstalledInfo
{
public:
    OllamaModelInstalledInfo();
    ~OllamaModelInstalledInfo();
    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QString model() const;
    void setModel(const QString &newModel);

    [[nodiscard]] QString quantizationLevel() const;
    void setQuantizationLevel(const QString &newQuantizationLevel);

    [[nodiscard]] QString family() const;
    void setFamily(const QString &newFamily);

    void parseInfo(const QJsonObject &obj);
    [[nodiscard]] QString parameterSize() const;
    void setParameterSize(const QString &newParameterSize);

    [[nodiscard]] QString modifyAt() const;
    void setModifyAt(const QString &newModifyAt);

    [[nodiscard]] QString modifyAtInLocal() const;

    [[nodiscard]] bool operator==(const OllamaModelInstalledInfo &other) const;

    [[nodiscard]] QString generateModelName() const;

private:
    QString mName;
    QString mModel;
    QString mQuantizationLevel;
    QString mFamily;
    QString mParameterSize;
    QString mModifyAt;
    QString mGeneratedModelName;
};
Q_DECLARE_TYPEINFO(OllamaModelInstalledInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const OllamaModelInstalledInfo &t);
