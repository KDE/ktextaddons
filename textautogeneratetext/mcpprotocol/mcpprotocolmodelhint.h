/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolModelHint
{
    Q_GADGET
public:
    /*!
     */
    McpProtocolModelHint();
    /*!
     */
    ~McpProtocolModelHint();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolModelHint &other) const;

    /*!
     */
    static McpProtocolModelHint fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolModelHint &image);
    std::optional<QString> name() const;
    void setName(std::optional<QString> newName);

private:
    std::optional<QString> mName;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolModelHint, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolModelHint &t);
