/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolsetlevelrequestparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolSetLevelRequest
{
public:
    /*!
     */
    McpProtocolSetLevelRequest();
    /*!
     */
    ~McpProtocolSetLevelRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSetLevelRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSetLevelRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSetLevelRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] McpProtocolSetLevelRequestParams params() const;
    /*!
     */
    void setParams(const McpProtocolSetLevelRequestParams &newParams);

private:
    McpProtocolUtils::RequestId mId;
    McpProtocolSetLevelRequestParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolSetLevelRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolSetLevelRequest &t);
