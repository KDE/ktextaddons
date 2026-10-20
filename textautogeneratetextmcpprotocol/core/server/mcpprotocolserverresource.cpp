/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverresource.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextResourceContents>
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolServerResource::McpProtocolServerResource() = default;

McpProtocolServerResource::~McpProtocolServerResource() = default;

McpProtocolResource McpProtocolServerResource::createResource(const QString &uri, const QString &name, const QString &description, const QString &mimeType)
{
    McpProtocolResource resource;
    resource.setUri(uri);
    resource.setName(name);
    if (!description.isEmpty()) {
        resource.setDescription(description);
    }
    if (!mimeType.isEmpty()) {
        resource.setMimeType(mimeType);
    }
    return resource;
}

McpProtocolReadResourceResult McpProtocolServerResource::textResult(const QString &text) const
{
    const McpProtocolResource resource = definition();
    McpProtocolTextResourceContents contents;
    contents.setUri(resource.uri());
    contents.setMimeType(resource.mimeType());
    contents.setText(text);
    McpProtocolReadResourceResult result;
    result.setContents({contents});
    return result;
}
