/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <optional>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTaskMetadata
{
public:
    /*!
     */
    McpProtocolTaskMetadata();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTaskMetadata &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTaskMetadata fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTaskMetadata &taskMetadata);

    /*!
     */
    [[nodiscard]] std::optional<qint64> ttl() const;
    /*!
     */
    void setTtl(std::optional<qint64> newTtl);

private:
    std::optional<qint64> mTtl;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskMetadata, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskMetadata &t);
