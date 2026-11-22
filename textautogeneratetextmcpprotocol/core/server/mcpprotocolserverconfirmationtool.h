/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerTool>
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolServerConfirmationTool
 * \brief The McpProtocolServerConfirmationTool class is a server tool which asks user confirmation before running
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerConfirmationTool
 *
 * A notification asks user to accept or reject the call, unless tool is read-only (readOnlyHint annotation)
 * or askModify() returns false. Only one notification is shown at a time: other calls wait their turn.
 * A call not answered before timeout, rejected or whose notification is closed is refused.
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServerConfirmationTool : public TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool
{
public:
    /*!
     * \brief McpProtocolServerConfirmationTool
     */
    McpProtocolServerConfirmationTool();
    /*!
     * \brief ~McpProtocolServerConfirmationTool
     */
    ~McpProtocolServerConfirmationTool() override;

    /*!
     * \brief call
     * Ask confirmation if needed, then run doCall() with \a call.
     */
    void call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call) final;

protected:
    /*!
     * \brief askModify
     * \return true when user must confirm calls of a tool which is not read-only
     */
    [[nodiscard]] virtual bool askModify() const = 0;

private:
    /*!
     * \brief doCall
     * Run tool with \a call, once confirmed.
     */
    virtual void doCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call) = 0;
    void askConfirmation(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);
};
}
