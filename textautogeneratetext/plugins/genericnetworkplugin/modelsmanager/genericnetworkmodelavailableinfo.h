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
    enum Capability {
        None = 0,
        Vision = 1,
        Audio = 4,
        Ocr = 8,
    };
    Q_FLAGS(Capability Capabilities)
    Q_DECLARE_FLAGS(Capabilities, Capability)

    GenericNetworkModelAvailableInfo();
    ~GenericNetworkModelAvailableInfo();
    void parseInfo(const QJsonObject &obj);
    [[nodiscard]] QString description() const;
    void setDescription(const QString &newDescription);

    [[nodiscard]] bool operator==(const GenericNetworkModelAvailableInfo &other) const;

    [[nodiscard]] QString modelName() const;
    void setModelName(const QString &newName);

    [[nodiscard]] bool toolsSupported() const;
    void setToolsSupported(bool newToolsSupported);

    [[nodiscard]] QString modelSize() const;
    void setModelSize(const QString &newModelSize);

    [[nodiscard]] QString identifier() const;
    void setIdentifier(const QString &newIdentifier);

    [[nodiscard]] QString ownedBy() const;
    void setOwnedBy(const QString &newOwnedBy);

    [[nodiscard]] Capabilities capabilities() const;
    void setCapabilities(const Capabilities &newCapabilities);

private:
    TEXTAUTOGENERATEGENERICNETWORK_NO_EXPORT void parseCapabilities(const QJsonObject &obj);
    Capabilities mCapabilities = Capability::None;
    QString mDescription;
    QString mModelName;
    QString mModelSize;
    QString mIdentifier;
    QString mOwnedBy;
    bool mToolsSupported = false;
    // TODO add tags
};
Q_DECLARE_TYPEINFO(GenericNetworkModelAvailableInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATEGENERICNETWORK_EXPORT QDebug operator<<(QDebug d, const GenericNetworkModelAvailableInfo &t);
