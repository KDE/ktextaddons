/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolAnnotations
{
public:
    /*!
     */
    McpProtocolAnnotations();
    /*!
     */
    ~McpProtocolAnnotations();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolAnnotations &other) const;

    /*!
     */
    static McpProtocolAnnotations fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolAnnotations &annot);

    std::optional<double> priority() const;
    void setPriority(std::optional<double> newPriority);

    std::optional<QString> lastModified() const;
    void setLastModified(std::optional<QString> newLastModified);

private:
    std::optional<QString> mLastModified;
    std::optional<double> mPriority;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolAnnotations, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolAnnotations &t);
