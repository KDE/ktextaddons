/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolresourcetemplate.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolListResourceTemplatesResult
{
public:
    /*!
     */
    McpProtocolListResourceTemplatesResult();
    /*!
     */
    ~McpProtocolListResourceTemplatesResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolListResourceTemplatesResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolListResourceTemplatesResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolListResourceTemplatesResult &image);

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

    /*!
     */
    [[nodiscard]] QList<McpProtocolResourceTemplate> resourceTemplates() const;
    /*!
     */
    void setResourceTemplates(const QList<McpProtocolResourceTemplate> &newResourceTemplates);

private:
    std::optional<McpProtocolMeta> mMeta;
    QList<McpProtocolResourceTemplate> mResourceTemplates;
    std::optional<QString> mNextCursor;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolListResourceTemplatesResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListResourceTemplatesResult &t);
