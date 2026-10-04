/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "core/tools/textautogeneratetexttoolbasejob.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include "textautogeneratetext_export.h"
#include <QJsonObject>
#include <QPointer>

namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolCallToolResult;
class McpProtocolClientProtocolManager;
}

namespace TextAutoGenerateText
{
class TextAutoGenerateMcpToolsManager;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateMcpToolCallJob
 * \brief Calls a tool of a MCP server and returns its result as text.
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMcpToolCallJob : public TextAutoGenerateTextToolBaseJob
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMcpToolCallJob(TextAutoGenerateMcpToolsManager *toolsManager, QObject *parent = nullptr);
    ~TextAutoGenerateMcpToolCallJob() override;

    void start() override;

    /*!
     * Arguments with their json type
     */
    [[nodiscard]] QJsonObject arguments() const;
    void setArguments(const QJsonObject &newArguments);

    /*!
     * Convert result of tool call to text
     */
    [[nodiscard]] static QString resultToText(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult &result);

Q_SIGNALS:
    void finished(const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &info);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void emitFinished(const QString &content);
    TextAutoGenerateMcpToolsManager *const mToolsManager;
    QJsonObject mArguments;
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager> mClient;
    qint64 mRequestId = -1;
    bool mFinished = false;
};
}
