/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoljsonrpcresultresponse.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolJSONRPCResultResponse::McpProtocolJSONRPCResultResponse() = default;

bool McpProtocolJSONRPCResultResponse::operator==(const McpProtocolJSONRPCResultResponse &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCResultResponse &t)
{
    d.space() << "result:" << t.result();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolJSONRPCResultResponse McpProtocolJSONRPCResultResponse::fromJson(const QJsonObject &obj)
{
    McpProtocolJSONRPCResultResponse response;
    if (obj.value("jsonrpc"_L1).toString() != u"2.0"_s) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.contains("id"_L1)) {
        response.setId(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    if (obj.contains("result"_L1)) {
        response.setResult(McpProtocolResult::fromJson(obj["result"_L1].toObject()));
    }
    return response;
}

QJsonObject McpProtocolJSONRPCResultResponse::toJson(const McpProtocolJSONRPCResultResponse &response)
{
    QJsonObject obj;
    obj["result"_L1] = McpProtocolResult::toJson(response.result());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["id"_L1] = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdToJson(response.id());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolJSONRPCResultResponse::id() const
{
    return mId;
}

void McpProtocolJSONRPCResultResponse::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolResult McpProtocolJSONRPCResultResponse::result() const
{
    return mResult;
}

void McpProtocolJSONRPCResultResponse::setResult(McpProtocolResult newResult)
{
    mResult = std::move(newResult);
}
