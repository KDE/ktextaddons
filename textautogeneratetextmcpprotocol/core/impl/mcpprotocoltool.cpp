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

bool McpProtocolTool::operator==(const McpProtocolTool &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTool &t)
{
    d.space() << "meta " << t.meta();
    d.space() << "annotations " << t.annotations();
    d.space() << "description " << t.description();
    d.space() << "execution " << t.execution();
    d.space() << "icons " << t.icons();
    d.space() << "inputSchema " << McpProtocolTool::InputSchema::toJson(t.inputSchema());
    d.space() << "description " << t.description();
    d.space() << "name " << t.name();
    if (t.outputSchema().has_value()) {
        d.space() << "outputSchema " << McpProtocolTool::OutputSchema::toJson(*t.outputSchema());
    }
    d.space() << "title " << t.title();
    return d;
}

QByteArray McpProtocolTool::type()
{
    return "object"_ba;
}

McpProtocolTool McpProtocolTool::fromJson(const QJsonObject &obj)
{
    McpProtocolTool tool;
    if (!obj.contains("inputSchema"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: inputSchema";
        return {};
    }
    if (!obj.contains("name"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: name";
        return {};
    }
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        tool.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue annotationsValue = obj.value("annotations"_L1); annotationsValue.isObject()) {
        tool.setAnnotations(McpProtocolToolAnnotations::fromJson(annotationsValue.toObject()));
    }
    if (obj.contains("description"_L1)) {
        tool.setDescription(obj.value("description"_L1).toString());
    }
    if (const QJsonValue executionValue = obj.value("execution"_L1); executionValue.isObject()) {
        tool.setExecution(McpProtocolToolExecution::fromJson(executionValue.toObject()));
    }
    if (const QJsonValue iconsValue = obj.value("icons"_L1); iconsValue.isArray()) {
        const QJsonArray arr = iconsValue.toArray();
        QList<McpProtocolIcon> list_icons;
        list_icons.reserve(arr.count());
        for (const auto &v : arr) {
            list_icons.append(McpProtocolIcon::fromJson(v.toObject()));
        }
        tool.setIcons(list_icons);
    }
    if (const QJsonValue inputSchemaValue = obj.value("inputSchema"_L1); inputSchemaValue.isObject()) {
        tool.setInputSchema(InputSchema::fromJson(inputSchemaValue.toObject()));
    }
    tool.setName(obj.value("name"_L1).toString());
    if (const QJsonValue outputSchemaValue = obj.value("outputSchema"_L1); outputSchemaValue.isObject()) {
        tool.setOutputSchema(OutputSchema::fromJson(outputSchemaValue.toObject()));
    }
    if (obj.contains("title"_L1)) {
        tool.setTitle(obj.value("title"_L1).toString());
    }
    return tool;
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
    if (const QJsonValue propertiesValue = obj.value("properties"_L1); propertiesValue.isObject()) {
        const QJsonObject mapObj_properties = propertiesValue.toObject();
        QMap<QString, QJsonObject> map_properties;
        for (auto it = mapObj_properties.constBegin(); it != mapObj_properties.constEnd(); ++it) {
            map_properties.insert(it.key(), it.value().toObject());
        }
        result.mProperties = map_properties;
    }
    if (const QJsonValue requiredValue = obj.value("required"_L1); requiredValue.isArray()) {
        const QJsonArray arr = requiredValue.toArray();
        QStringList list_required;
        list_required.reserve(arr.count());
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
    if (const auto &dollarschema = input.dollarschema(); dollarschema.has_value()) {
        obj.insert("$schema"_L1, *dollarschema);
    }
    if (const auto &properties = input.properties(); properties.has_value()) {
        QJsonObject map_properties;
        for (auto it = properties->constBegin(); it != properties->constEnd(); ++it) {
            map_properties.insert(it.key(), QJsonValue(it.value()));
        }
        obj.insert("properties"_L1, map_properties);
    }
    if (const auto &required = input.required(); required.has_value()) {
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
    if (const QJsonValue propertiesValue2 = obj.value("properties"_L1); propertiesValue2.isObject()) {
        const QJsonObject mapObj_properties = propertiesValue2.toObject();
        QMap<QString, QJsonObject> map_properties;
        for (auto it = mapObj_properties.constBegin(); it != mapObj_properties.constEnd(); ++it) {
            map_properties.insert(it.key(), it.value().toObject());
        }
        result.mProperties = map_properties;
    }
    if (const QJsonValue requiredValue2 = obj.value("required"_L1); requiredValue2.isArray()) {
        const QJsonArray arr = requiredValue2.toArray();
        QStringList list_required;
        list_required.reserve(arr.count());
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
    if (const auto &dollarschema = input.dollarschema(); dollarschema.has_value()) {
        obj.insert("$schema"_L1, *dollarschema);
    }
    if (const auto &properties = input.properties(); properties.has_value()) {
        QJsonObject map_properties;
        for (auto it = properties->constBegin(); it != properties->constEnd(); ++it) {
            map_properties.insert(it.key(), QJsonValue(it.value()));
        }
        obj.insert("properties"_L1, map_properties);
    }
    if (const auto &required = input.required(); required.has_value()) {
        QJsonArray arr_required;
        for (const auto &v : *required) {
            arr_required.append(v);
        }
        obj.insert("required"_L1, arr_required);
    }
    return obj;
}
