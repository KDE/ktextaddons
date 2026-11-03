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
     * \enum TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind
     * \brief Effect of tool on its environment, used to set its annotations
     * \value ReadOnly Tool doesn't modify its environment
     * \value Modify Tool modifies its environment without destroying data (e.g. it creates an item)
     * \value Destructive Tool can delete or overwrite data
     */
    enum class ToolKind : uint8_t {
        ReadOnly,
        Modify,
        Destructive,
    };

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

    /*!
     * \brief createTool
     * \return tool with \a title and annotations matching \a kind (see annotations()).
     * Clients consider tools without annotations as destructive: use this method to always define them.
     * Annotations can be adjusted afterwards (e.g. idempotentHint, openWorldHint).
     */
    [[nodiscard]] static McpProtocolTool createTool(const QString &name,
                                                    const QString &title,
                                                    const QString &description,
                                                    ToolKind kind,
                                                    const QMap<QString, QJsonObject> &properties = {},
                                                    const QStringList &required = {});

    /*!
     * \brief annotations
     * \return annotations matching \a kind: readOnlyHint, destructiveHint (when tool is not read only) and openWorldHint (false)
     */
    [[nodiscard]] static McpProtocolToolAnnotations annotations(ToolKind kind);

    [[nodiscard]] static QJsonObject schemaProperty(const QString &type, const QString &description);

    /*!
     * \brief schemaEnumProperty
     * \return string property which accepts only \a values
     */
    [[nodiscard]] static QJsonObject schemaEnumProperty(const QStringList &values, const QString &description);

    /*!
     * \brief schemaArrayProperty
     * \return array property whose elements are described by \a items (see schemaProperty() and schemaEnumProperty())
     */
    [[nodiscard]] static QJsonObject schemaArrayProperty(const QJsonObject &items, const QString &description);

private:
    Q_DISABLE_COPY_MOVE(McpProtocolServerTool)
};
}
