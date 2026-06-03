/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltool.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTool::McpProtocolTool() = default;

McpProtocolTool::~McpProtocolTool() = default;

bool McpProtocolTool::operator==(const McpProtocolTool &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTool &t)
{
    return d;
}

QByteArray McpProtocolTool::type()
{
    return "object"_ba;
}

McpProtocolTool McpProtocolTool::fromJson(const QJsonObject &obj)
{
    McpProtocolTool text;
    return text;
}

QJsonObject McpProtocolTool::toJson(const McpProtocolTool &tool)
{
    QJsonObject obj;
    obj.insert("inputSchema"_L1, InputSchema::toJson(tool.inputSchema()));
    obj.insert("name"_L1, tool.name());
    if (tool.meta().has_value()) {
        obj.insert("_meta"_L1, McpProtocolMeta::toJson(*tool.meta()));
    }
    if (tool.annotations().has_value()) {
        obj.insert("annotations"_L1, McpProtocolToolAnnotations::toJson(*tool.annotations()));
    }
    if (tool.description().has_value()) {
        obj.insert("description"_L1, *tool.description());
    }
    if (tool.execution().has_value()) {
        obj.insert("execution"_L1, McpProtocolToolExecution::toJson(*tool.execution()));
    }
    if (tool.icons().has_value()) {
        QJsonArray arr_icons;
        const auto icons = *tool.icons();
        for (const auto &v : icons) {
            arr_icons.append(McpProtocolIcon::toJson(v));
        }
        obj.insert("icons"_L1, arr_icons);
    }
    if (tool.outputSchema().has_value()) {
        obj.insert("outputSchema"_L1, McpProtocolTool::OutputSchema::toJson(*tool.outputSchema()));
    }
    if (tool.title().has_value()) {
        obj.insert("title"_L1, *tool.title());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolTool::meta() const
{
    return mMeta;
}

void McpProtocolTool::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolToolAnnotations> McpProtocolTool::annotations() const
{
    return mAnnotations;
}

void McpProtocolTool::setAnnotations(std::optional<McpProtocolToolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

std::optional<QString> McpProtocolTool::description() const
{
    return mDescription;
}

void McpProtocolTool::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<McpProtocolToolExecution> McpProtocolTool::execution() const
{
    return mExecution;
}

void McpProtocolTool::setExecution(std::optional<McpProtocolToolExecution> newExecution)
{
    mExecution = std::move(newExecution);
}

std::optional<QList<McpProtocolIcon>> McpProtocolTool::icons() const
{
    return mIcons;
}

void McpProtocolTool::setIcons(std::optional<QList<McpProtocolIcon>> newIcons)
{
    mIcons = std::move(newIcons);
}

McpProtocolTool::InputSchema McpProtocolTool::inputSchema() const
{
    return mInputSchema;
}

void McpProtocolTool::setInputSchema(const InputSchema &newInputSchema)
{
    mInputSchema = newInputSchema;
}

QString McpProtocolTool::name() const
{
    return mName;
}

void McpProtocolTool::setName(const QString &newName)
{
    mName = newName;
}

std::optional<McpProtocolTool::OutputSchema> McpProtocolTool::outputSchema() const
{
    return mOutputSchema;
}

void McpProtocolTool::setOutputSchema(std::optional<OutputSchema> newOutputSchema)
{
    mOutputSchema = std::move(newOutputSchema);
}

std::optional<QString> McpProtocolTool::title() const
{
    return mTitle;
}

void McpProtocolTool::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

const std::optional<QString> &McpProtocolTool::InputSchema::dollarschema() const
{
    return mDollarschema;
}

const std::optional<QMap<QString, QJsonObject>> &McpProtocolTool::InputSchema::properties() const
{
    return mProperties;
}

const std::optional<QStringList> &McpProtocolTool::InputSchema::required() const
{
    return mRequired;
}

bool McpProtocolTool::InputSchema::operator==(const InputSchema &other) const = default;

McpProtocolTool::InputSchema McpProtocolTool::InputSchema::fromJson(const QJsonObject &obj)
{
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolTool::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "InputSchema: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }
    McpProtocolTool::InputSchema result;
    if (obj.contains("$schema"_L1)) {
        result.mDollarschema = obj.value("$schema"_L1).toString();
    }
    if (obj.contains("properties"_L1) && obj["properties"_L1].isObject()) {
        const QJsonObject mapObj_properties = obj["properties"_L1].toObject();
        QMap<QString, QJsonObject> map_properties;
        for (auto it = mapObj_properties.constBegin(); it != mapObj_properties.constEnd(); ++it) {
            map_properties.insert(it.key(), it.value().toObject());
        }
        result.mProperties = map_properties;
    }
    if (obj.contains("required"_L1) && obj["required"_L1].isArray()) {
        const QJsonArray arr = obj["required"_L1].toArray();
        QStringList list_required;
        for (const auto &v : arr) {
            list_required.append(v.toString());
        }
        result.mRequired = list_required;
    }
    return result;
}

QJsonObject McpProtocolTool::InputSchema::toJson(const InputSchema &input)
{
    QJsonObject obj;
    obj.insert("type"_L1, QString::fromLatin1(McpProtocolTool::type()));
    const auto &dollarschema = input.dollarschema();
    if (dollarschema.has_value()) {
        obj.insert("$schema"_L1, *dollarschema);
    }
    const auto &properties = input.properties();
    if (properties.has_value()) {
        QJsonObject map_properties;
        for (auto it = properties->constBegin(); it != properties->constEnd(); ++it) {
            map_properties.insert(it.key(), QJsonValue(it.value()));
        }
        obj.insert("properties"_L1, map_properties);
    }
    const auto &required = input.required();
    if (required.has_value()) {
        QJsonArray arr_required;
        for (const auto &v : *required) {
            arr_required.append(v);
        }
        obj.insert("required"_L1, arr_required);
    }
    return obj;
}

const std::optional<QString> &McpProtocolTool::OutputSchema::dollarschema() const
{
    return mDollarschema;
}

const std::optional<QMap<QString, QJsonObject>> &McpProtocolTool::OutputSchema::properties() const
{
    return mProperties;
}

const std::optional<QStringList> &McpProtocolTool::OutputSchema::required() const
{
    return mRequired;
}

bool McpProtocolTool::OutputSchema::operator==(const OutputSchema &other) const = default;

McpProtocolTool::OutputSchema McpProtocolTool::OutputSchema::fromJson(const QJsonObject &obj)
{
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolTool::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "InputSchema: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }
    McpProtocolTool::OutputSchema result;
    if (obj.contains("$schema"_L1)) {
        result.mDollarschema = obj.value("$schema"_L1).toString();
    }
    if (obj.contains("properties"_L1) && obj["properties"_L1].isObject()) {
        const QJsonObject mapObj_properties = obj["properties"_L1].toObject();
        QMap<QString, QJsonObject> map_properties;
        for (auto it = mapObj_properties.constBegin(); it != mapObj_properties.constEnd(); ++it) {
            map_properties.insert(it.key(), it.value().toObject());
        }
        result.mProperties = map_properties;
    }
    if (obj.contains("required"_L1) && obj["required"_L1].isArray()) {
        const QJsonArray arr = obj["required"_L1].toArray();
        QStringList list_required;
        for (const auto &v : arr) {
            list_required.append(v.toString());
        }
        result.mRequired = list_required;
    }
    return result;
}

QJsonObject McpProtocolTool::OutputSchema::toJson(const OutputSchema &input)
{
    QJsonObject obj;
    obj.insert("type"_L1, QString::fromLatin1(McpProtocolTool::type()));
    const auto &dollarschema = input.dollarschema();
    if (dollarschema.has_value()) {
        obj.insert("$schema"_L1, *dollarschema);
    }
    const auto &properties = input.properties();
    if (properties.has_value()) {
        QJsonObject map_properties;
        for (auto it = properties->constBegin(); it != properties->constEnd(); ++it) {
            map_properties.insert(it.key(), QJsonValue(it.value()));
        }
        obj.insert("properties"_L1, map_properties);
    }
    const auto &required = input.required();
    if (required.has_value()) {
        QJsonArray arr_required;
        for (const auto &v : *required) {
            arr_required.append(v);
        }
        obj.insert("required"_L1, arr_required);
    }
    return obj;
}
