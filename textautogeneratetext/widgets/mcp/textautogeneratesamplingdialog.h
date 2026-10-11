/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

#include "textautogeneratetext_private_export.h"

class QLabel;
class QPlainTextEdit;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolCreateMessageRequest;
}

namespace TextAutoGenerateText
{
/*!
 * Asks user to confirm that sampling request of a MCP server can be sent to LLM.
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSamplingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSamplingDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateSamplingDialog() override;

    void setServerName(const QString &serverName);
    void setRequest(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &request);

    /*!
     * Text shown to user: system prompt and messages of \a request
     */
    [[nodiscard]] static QString requestText(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &request);

private:
    QLabel *const mLabel;
    QPlainTextEdit *const mMessages;
};
}
