/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolservertool.h"
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolServerTool::McpProtocolServerTool() = default;

McpProtocolServerTool::~McpProtocolServerTool() = default;

McpProtocolTool
McpProtocolServerTool::createTool(const QString &name, const QString &description, const QMap<QString, QJsonObject> &properties, const QStringList &required)
{
    McpProtocolTool::InputSchema schema;
    schema.mProperties = properties;
    if (!required.isEmpty()) {
        schema.mRequired = required;
    }
    McpProtocolTool tool;
    tool.setName(name);
    tool.setDescription(description);
    tool.setInputSchema(schema);
    return tool;
}

McpProtocolTool McpProtocolServerTool::createTool(const QString &name,
                                                  const QString &title,
                                                  const QString &description,
                                                  ToolKind kind,
                                                  const QMap<QString, QJsonObject> &properties,
                                                  const QStringList &required)
{
    McpProtocolTool tool = createTool(name, description, properties, required);
    tool.setTitle(title);
    tool.setAnnotations(annotations(kind));
    return tool;
}

McpProtocolToolAnnotations McpProtocolServerTool::annotations(ToolKind kind)
{
    McpProtocolToolAnnotations annotations;
    annotations.setOpenWorldHint(false);
    switch (kind) {
    case ToolKind::ReadOnly:
        annotations.setReadOnlyHint(true);
        break;
    case ToolKind::Modify:
        annotations.setReadOnlyHint(false);
        annotations.setDestructiveHint(false);
        break;
    case ToolKind::Destructive:
        annotations.setReadOnlyHint(false);
        annotations.setDestructiveHint(true);
        break;
    }
    return annotations;
}

QJsonObject McpProtocolServerTool::schemaProperty(const QString &type, const QString &description)
{
    return QJsonObject{{"type"_L1, type}, {"description"_L1, description}};
}

QJsonObject McpProtocolServerTool::schemaEnumProperty(const QStringList &values, const QString &description)
{
    QJsonObject property{{"type"_L1, u"string"_s}, {"enum"_L1, QJsonArray::fromStringList(values)}};
    if (!description.isEmpty()) {
        property.insert("description"_L1, description);
    }
    return property;
}

QJsonObject McpProtocolServerTool::schemaArrayProperty(const QJsonObject &items, const QString &description)
{
    QJsonObject property{{"type"_L1, u"array"_s}, {"items"_L1, items}};
    if (!description.isEmpty()) {
        property.insert("description"_L1, description);
    }
    return property;
}
