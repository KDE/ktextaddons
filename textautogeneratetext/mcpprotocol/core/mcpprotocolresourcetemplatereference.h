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
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolResourceTemplateReference
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
    [[nodiscard]] static McpProtocolResourceTemplateReference fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolResourceTemplateReference &image);

    /*!
     */
    [[nodiscard]] QString uri() const;
    /*!
     */
    void setUri(const QString &newUri);

private:
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolResourceTemplateReference, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResourceTemplateReference &t);
