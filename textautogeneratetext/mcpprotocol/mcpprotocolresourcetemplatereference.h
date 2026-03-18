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
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolResourceTemplateReference
{
public:
    /*!
     */
    McpProtocolResourceTemplateReference();
    /*!
     */
    ~McpProtocolResourceTemplateReference();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolResourceTemplateReference &other) const;

    /*!
     */
    static McpProtocolResourceTemplateReference fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolResourceTemplateReference &image);

    QString uri() const;
    void setUri(const QString &newUri);

private:
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolResourceTemplateReference, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResourceTemplateReference &t);
