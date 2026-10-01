/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonValue>
#include <QMap>
#include <QString>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolMeta
{
public:
    /*!
     */
    McpProtocolMeta();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolMeta &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolMeta fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolMeta &protocolMeta);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonValue>> meta() const;
    /*!
     */
    void setMeta(std::optional<QMap<QString, QJsonValue>> newMeta);

private:
    std::optional<QMap<QString, QJsonValue>> mMeta;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta &t);
