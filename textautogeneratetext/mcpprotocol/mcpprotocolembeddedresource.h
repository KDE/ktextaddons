/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolblobresourcecontents.h"
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocoltextresourcecontents.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolEmbeddedResource
{
public:
    /*!
     */
    McpProtocolEmbeddedResource();
    /*!
     */
    ~McpProtocolEmbeddedResource();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolEmbeddedResource &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolEmbeddedResource fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolEmbeddedResource &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolAnnotations> annotations() const;
    /*!
     */
    void setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::EmbeddedResourceResource resource() const;
    /*!
     */
    void setResource(const McpProtocolUtils::EmbeddedResourceResource &newResource);

private:
    std::optional<McpProtocolAnnotations> mAnnotations;
    McpProtocolUtils::EmbeddedResourceResource mResource;
    std::optional<McpProtocolMeta> mMeta;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolEmbeddedResource, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolEmbeddedResource &t);
