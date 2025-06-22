/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategenericnetwork_export.h"
#include <QDebug>
#include <QJsonObject>
#include <QString>

class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkModelAvailableInfo
{
public:
    GenericNetworkModelAvailableInfo();
    ~GenericNetworkModelAvailableInfo();
    void parseInfo(const QString &name, const QJsonObject &obj);
    [[nodiscard]] QString description() const;
    void setDescription(const QString &newDescription);

    [[nodiscard]] bool operator==(const GenericNetworkModelAvailableInfo &other) const;

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    bool toolsSupported() const;
    void setToolsSupported(bool newToolsSupported);

private:
    QString mDescription;
    QString mName;
    bool mToolsSupported = false;
};
Q_DECLARE_TYPEINFO(GenericNetworkModelAvailableInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const GenericNetworkModelAvailableInfo &t);
