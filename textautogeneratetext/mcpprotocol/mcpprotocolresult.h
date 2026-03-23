/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolResult
{
public:
    /*!
     */
    McpProtocolResult();
    /*!
     */
    ~McpProtocolResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    QJsonObject additionalProperties() const;
    void setAdditionalProperties(const QJsonObject &newAdditionalProperties);

private:
    std::optional<McpProtocolMeta> mMeta;
    QJsonObject mAdditionalProperties;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResult &t);
