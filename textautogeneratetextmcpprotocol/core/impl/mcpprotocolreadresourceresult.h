/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolReadResourceResult
{
public:
    /*!
     */
    McpProtocolReadResourceResult();
    /*!
     */
    ~McpProtocolReadResourceResult();

    /*!
     */
    // [[nodiscard]] bool operator==(const McpProtocolReadResourceResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolReadResourceResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolReadResourceResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EmbeddedResourceResource> contents() const;
    /*!
     */
    void setContents(const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EmbeddedResourceResource> &newContents);

private:
    std::optional<McpProtocolMeta> mMeta;
    QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EmbeddedResourceResource> mContents;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceResult &t);
