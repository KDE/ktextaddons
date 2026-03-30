/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourcetemplatereference.h"
#include "textautogeneratetextmcpprotocol_debug.h"
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolResourceTemplateReference::McpProtocolResourceTemplateReference() = default;

McpProtocolResourceTemplateReference::~McpProtocolResourceTemplateReference() = default;

QByteArray McpProtocolResourceTemplateReference::type()
{
    return QByteArrayLiteral("ref/resource");
}

bool McpProtocolResourceTemplateReference::operator==(const McpProtocolResourceTemplateReference &other) const = default;
QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResourceTemplateReference &t)
{
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolResourceTemplateReference McpProtocolResourceTemplateReference::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceTemplateReference text;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolResourceTemplateReference::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "McpProtocolResourceTemplateReference: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }

    text.setUri(obj.value("uri"_L1).toString());
    return text;
}

QJsonObject McpProtocolResourceTemplateReference::toJson(const McpProtocolResourceTemplateReference &text)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(McpProtocolResourceTemplateReference::type());
    obj["uri"_L1] = text.uri();
    return obj;
}

QString McpProtocolResourceTemplateReference::uri() const
{
    return mUri;
}

void McpProtocolResourceTemplateReference::setUri(const QString &newUri)
{
    mUri = newUri;
}
