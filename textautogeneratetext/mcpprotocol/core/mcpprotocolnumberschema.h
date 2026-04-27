/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolNumberSchema
{
public:
    enum class Type : uint8_t {
        Integer,
        Number,
        Unknown,
    };

    /*!
     */
    McpProtocolNumberSchema();
    /*!
     */
    ~McpProtocolNumberSchema();

    /*!
     */
    [[nodiscard]] static McpProtocolNumberSchema fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolNumberSchema &image);

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolNumberSchema &other) const;

    /*!
     */
    [[nodiscard]] std::optional<int> defaultValue() const;
    /*!
     */
    void setDefaultValue(std::optional<int> newDefaultValue);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] std::optional<int> maximum() const;
    /*!
     */
    void setMaximum(std::optional<int> newMaximum);

    /*!
     */
    [[nodiscard]] std::optional<int> minimum() const;
    /*!
     */
    void setMinimum(std::optional<int> newMinimum);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

    /*!
     */
    [[nodiscard]] Type type() const;
    /*!
     */
    void setType(Type newType);

    /*!
     */
    [[nodiscard]] static QString convertNumberSchemaTypeToString(McpProtocolNumberSchema::Type level);
    /*!
     */
    [[nodiscard]] static McpProtocolNumberSchema::Type convertNumberSchemaTypeFromString(const QString &str);

private:
    std::optional<int> mDefaultValue;
    std::optional<QString> mDescription;
    std::optional<int> mMaximum;
    std::optional<int> mMinimum;
    std::optional<QString> mTitle;
    Type mType = Type::Unknown;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema &t);
