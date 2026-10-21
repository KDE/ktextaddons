/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QMap>
#include <QStringList>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPrompt>
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolServerPrompt
 * \brief The McpProtocolServerPrompt class is a prompt exported by McpProtocolServerProtocolManager
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerPrompt
 *
 * Reimplement definition() (name, description, arguments…) and get(), and complete() to propose argument values.
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServerPrompt
{
public:
    /*!
     * \brief McpProtocolServerPrompt
     */
    McpProtocolServerPrompt();
    /*!
     * \brief ~McpProtocolServerPrompt
     */
    virtual ~McpProtocolServerPrompt();

    /*!
     * \brief definition
     * \return prompt as sent in prompts/list
     */
    [[nodiscard]] virtual TextAutoGenerateTextMcpProtocolCore::McpProtocolPrompt definition() const = 0;
    /*!
     * \brief get
     * Return messages of prompt for \a arguments. Required arguments are checked by manager before.
     */
    [[nodiscard]] virtual TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptResult get(const QMap<QString, QString> &arguments) const = 0;
    /*!
     * \brief complete
     * Return completion values for argument \a argumentName which starts with \a value (completion/complete).
     * \a arguments contains values of arguments already resolved by client. By default no value is returned.
     */
    [[nodiscard]] virtual QStringList complete(const QString &argumentName, const QString &value, const QMap<QString, QString> &arguments) const;

    /*!
     * \brief createPrompt
     * Return a prompt definition with \a name, \a description and \a arguments.
     */
    [[nodiscard]] static McpProtocolPrompt
    createPrompt(const QString &name, const QString &description, const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptArgument> &arguments = {});
    /*!
     * \brief createArgument
     * Return a prompt argument with \a name and \a description.
     */
    [[nodiscard]] static McpProtocolPromptArgument createArgument(const QString &name, const QString &description, bool required = false);
    /*!
     * \brief createUserTextResult
     * Return a result with one user message containing \a text.
     */
    [[nodiscard]] static McpProtocolGetPromptResult createUserTextResult(const QString &text, const QString &description = {});

private:
    Q_DISABLE_COPY_MOVE(McpProtocolServerPrompt)
};
}
