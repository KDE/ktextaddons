/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolReadResourceResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResource>
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolServerResource
 * \brief The McpProtocolServerResource class is a resource exported by McpProtocolServerProtocolManager
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerResource
 *
 * Reimplement definition() (uri, name, mime type…) and read().
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServerResource
{
public:
    /*!
     * \brief McpProtocolServerResource
     */
    McpProtocolServerResource();
    /*!
     * \brief ~McpProtocolServerResource
     */
    virtual ~McpProtocolServerResource();

    /*!
     * \brief definition
     * \return resource as sent in resources/list
     */
    [[nodiscard]] virtual TextAutoGenerateTextMcpProtocolCore::McpProtocolResource definition() const = 0;
    /*!
     * \brief read
     * Return contents of resource. Empty contents is an error (resource can't be read).
     */
    [[nodiscard]] virtual TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceResult read() const = 0;

    /*!
     * \brief createResource
     * Return a resource definition with \a uri, \a name, \a description and \a mimeType.
     */
    [[nodiscard]] static McpProtocolResource
    createResource(const QString &uri, const QString &name, const QString &description = {}, const QString &mimeType = {});

protected:
    /*!
     * \brief textResult
     * Return a result with \a text, uri and mime type of definition().
     */
    [[nodiscard]] McpProtocolReadResourceResult textResult(const QString &text) const;

private:
    Q_DISABLE_COPY_MOVE(McpProtocolServerResource)
};
}
