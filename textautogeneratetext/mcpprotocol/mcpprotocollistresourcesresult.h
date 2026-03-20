/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolListResourcesResult
{
public:
    /*!
     */
    McpProtocolListResourcesResult();
    /*!
     */
    ~McpProtocolListResourcesResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolListResourcesResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolListResourcesResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolListResourcesResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<QString> nextCursor() const;
    /*!
     */
    void setNextCursor(std::optional<QString> newNextCursor);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mNextCursor;
    // TODO QList<Resource> _resources;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolListResourcesResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListResourcesResult &t);
