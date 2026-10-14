/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourcetemplatereference.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolResourceTemplateReference::McpProtocolResourceTemplateReference() = default;

QByteArray McpProtocolResourceTemplateReference::type()
{
    return "ref/resource"_ba;
}

bool McpProtocolResourceTemplateReference::operator==(const McpProtocolResourceTemplateReference &other) const = default;

bool McpProtocolResourceTemplateReference::isValid() const
{
    return !mUri.isEmpty();
}
QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceTemplateReference &t)
{
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolResourceTemplateReference McpProtocolResourceTemplateReference::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceTemplateReference text;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolResourceTemplateReference::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolResourceTemplateReference: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }

    if (const QJsonValue uriValue = obj.value("uri"_L1); uriValue.isString() && !uriValue.toString().isEmpty()) {
        text.setUri(uriValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolResourceTemplateReference: missing required field 'uri'";
        return {};
    }
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
