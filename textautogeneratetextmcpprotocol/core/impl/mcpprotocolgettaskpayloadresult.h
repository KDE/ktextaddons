/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonObject>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>

class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolGetTaskPayloadResult
{
public:
    /*!
     */
    McpProtocolGetTaskPayloadResult();
    /*!
     */
    ~McpProtocolGetTaskPayloadResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolGetTaskPayloadResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolGetTaskPayloadResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolGetTaskPayloadResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] QJsonObject additionalProperties() const;
    /*!
     */
    void setAdditionalProperties(const QJsonObject &newAdditionalProperties);

private:
    std::optional<McpProtocolMeta> mMeta;
    QJsonObject mAdditionalProperties;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskPayloadResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskPayloadResult &t);
