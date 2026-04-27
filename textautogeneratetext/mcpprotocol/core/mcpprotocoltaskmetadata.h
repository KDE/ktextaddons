/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolTaskMetadata
{
public:
    /*!
     */
    McpProtocolTaskMetadata();
    /*!
     */
    ~McpProtocolTaskMetadata();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTaskMetadata &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTaskMetadata fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTaskMetadata &image);

    /*!
     */
    [[nodiscard]] std::optional<int> ttl() const;
    /*!
     */
    void setTtl(std::optional<int> newTtl);

private:
    std::optional<int> mTtl;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolTaskMetadata, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTaskMetadata &t);
