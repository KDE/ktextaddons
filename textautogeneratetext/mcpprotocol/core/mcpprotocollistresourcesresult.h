/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocolresource.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolListResourcesResult
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

    /*!
     */
    [[nodiscard]] QList<McpProtocolResource> resources() const;
    /*!
     */
    void setResources(const QList<McpProtocolResource> &newResources);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mNextCursor;
    QList<McpProtocolResource> mResources;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolListResourcesResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListResourcesResult &t);
