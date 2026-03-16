/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolTextContent
{
public:
    /*!
     */
    McpProtocolTextContent();
    /*!
     */
    ~McpProtocolTextContent();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTextContent &other) const;

    [[nodiscard]] QString text() const;
    void setText(const QString &newText);

private:
    // TODO annotations
    // TODO additionalProperties
    QString mText;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolTextContent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTextContent &t);
