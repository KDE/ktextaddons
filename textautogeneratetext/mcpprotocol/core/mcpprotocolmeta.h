/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
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
    ~McpProtocolMeta();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolMeta &other) const;

    /*!
     */
    static McpProtocolMeta fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolMeta &image);

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
