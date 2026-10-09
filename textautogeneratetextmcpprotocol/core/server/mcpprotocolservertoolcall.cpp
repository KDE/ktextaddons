/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolservertoolcall.h"
#include <QJsonObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextContent>

using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolServerToolCall::McpProtocolServerToolCall(const QJsonValue &requestId,
                                                     const QString &name,
                                                     const QMap<QString, QJsonValue> &arguments,
                                                     QObject *parent)
    : QObject{parent}
    , mRequestId(requestId)
    , mName(name)
    , mArguments(arguments)
{
}

McpProtocolServerToolCall::~McpProtocolServerToolCall() = default;

QJsonValue McpProtocolServerToolCall::requestId() const
{
    return mRequestId;
}

QString McpProtocolServerToolCall::name() const
{
    return mName;
}

QMap<QString, QJsonValue> McpProtocolServerToolCall::arguments() const
{
    return mArguments;
}

bool McpProtocolServerToolCall::isFinished() const
{
    return mFinished;
}

void McpProtocolServerToolCall::finish(const McpProtocolCallToolResult &result)
{
    if (mFinished) {
        return;
    }
    mFinished = true;
    Q_EMIT resultReady(McpProtocolCallToolResult::toJson(result));
}

void McpProtocolServerToolCall::finishWithText(const QString &text, bool isError)
{
    McpProtocolTextContent content;
    content.setText(text);
    McpProtocolCallToolResult result;
    result.setContent({content});
    if (isError) {
        result.setIsError(true);
    }
    finish(result);
}

void McpProtocolServerToolCall::finishWithError(int code, const QString &message)
{
    if (mFinished) {
        return;
    }
    mFinished = true;
    Q_EMIT errorReady(code, message);
}

void McpProtocolServerToolCall::cancel()
{
    if (mFinished) {
        return;
    }
    mFinished = true;
    Q_EMIT cancelled();
}

#include "moc_mcpprotocolservertoolcall.cpp"
