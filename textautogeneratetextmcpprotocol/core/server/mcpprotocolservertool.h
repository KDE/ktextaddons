/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTool>
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServerToolCall;
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool
 * \brief The McpProtocolServerTool class is a tool exported by McpProtocolServerProtocolManager
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerTool
 *
 * Reimplement definition() (name, description, input schema, annotations…) and call().
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServerTool
{
public:
    /*!
     * \brief McpProtocolServerTool
     */
    McpProtocolServerTool();
    /*!
     * \brief ~McpProtocolServerTool
     */
    virtual ~McpProtocolServerTool();

    /*!
     * \brief definition
     * \return tool as sent in tools/list
     */
    [[nodiscard]] virtual TextAutoGenerateTextMcpProtocolCore::McpProtocolTool definition() const = 0;

    /*!
     * \brief call
     * Execute tool. Answer can be asynchronous: keep \a call and use McpProtocolServerToolCall::finish() later.
     * \a call is owned by manager, it's deleted when finished or cancelled (see McpProtocolServerToolCall::cancelled()).
     * \param call
     */
    virtual void call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call) = 0;

    [[nodiscard]] static McpProtocolTool
    createTool(const QString &name, const QString &description, const QMap<QString, QJsonObject> &properties = {}, const QStringList &required = {});

    [[nodiscard]] static QJsonObject schemaProperty(const QString &type, const QString &description);

private:
    Q_DISABLE_COPY_MOVE(McpProtocolServerTool)
};
}
