/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonValue>
#include <QMap>
#include <QObject>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolCallToolResult;
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall
 * \brief The McpProtocolServerToolCall class is a tools/call request not answered yet
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall
 *
 * Created by McpProtocolServerProtocolManager. Answer only once, with finish(), finishWithText() or finishWithError().
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServerToolCall : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief McpProtocolServerToolCall
     * \param requestId
     * \param name
     * \param arguments
     * \param parent
     */
    explicit McpProtocolServerToolCall(const QJsonValue &requestId, const QString &name, const QMap<QString, QJsonValue> &arguments, QObject *parent = nullptr);
    /*!
     * \brief ~McpProtocolServerToolCall
     */
    ~McpProtocolServerToolCall() override;

    /*!
     * \brief requestId
     * \return
     */
    [[nodiscard]] QJsonValue requestId() const;
    /*!
     * \brief name
     * \return tool name
     */
    [[nodiscard]] QString name() const;
    /*!
     * \brief arguments
     * \return
     */
    [[nodiscard]] QMap<QString, QJsonValue> arguments() const;

    /*!
     * \brief isFinished
     * \return true when answered or cancelled
     */
    [[nodiscard]] bool isFinished() const;

    /*!
     * \brief finish
     * Send tool \a result. Ignored when call is already finished or cancelled.
     */
    void finish(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult &result);
    /*!
     * \brief finishWithText
     * Send a result with only \a text. \a isError means a tool error (the model can see it), not a protocol error.
     */
    void finishWithText(const QString &text, bool isError = false);
    /*!
     * \brief finishWithError
     * Send a JSON-RPC error (protocol error: invalid params…).
     */
    void finishWithError(int code, const QString &message);

    /*!
     * \brief cancel
     * Called by manager when client cancels request or server stops.
     */
    void cancel();

Q_SIGNALS:
    /*!
     * \brief cancelled
     * Client cancelled request (or server stopped): stop work (kill job…), answer will be ignored.
     */
    void cancelled();
    /*!
     * \brief resultReady
     * \param result
     */
    void resultReady(const QJsonObject &result);
    /*!
     * \brief errorReady
     * \param code
     * \param message
     */
    void errorReady(int code, const QString &message);

private:
    const QJsonValue mRequestId;
    const QString mName;
    const QMap<QString, QJsonValue> mArguments;
    bool mFinished = false;
};
}
