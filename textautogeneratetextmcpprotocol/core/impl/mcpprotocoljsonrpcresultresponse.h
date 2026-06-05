/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolJSONRPCResultResponse
{
public:
    /*!
     */
    McpProtocolJSONRPCResultResponse();
    /*!
     */
    ~McpProtocolJSONRPCResultResponse();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolJSONRPCResultResponse &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolJSONRPCResultResponse fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolJSONRPCResultResponse &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] McpProtocolResult result() const;
    /*!
     */
    void setResult(const McpProtocolResult &newResult);

private:
    McpProtocolResult mResult;
    McpProtocolUtils::RequestId mId;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCResultResponse, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCResultResponse &t);
