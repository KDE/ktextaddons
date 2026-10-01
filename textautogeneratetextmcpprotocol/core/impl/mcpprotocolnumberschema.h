/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <cstdint>
#include <optional>
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
    [[nodiscard]] static McpProtocolNumberSchema fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolNumberSchema &schema);

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolNumberSchema &other) const;

    /*!
     */
    [[nodiscard]] std::optional<double> defaultValue() const;
    /*!
     */
    void setDefaultValue(std::optional<double> newDefaultValue);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] std::optional<double> maximum() const;
    /*!
     */
    void setMaximum(std::optional<double> newMaximum);

    /*!
     */
    [[nodiscard]] std::optional<double> minimum() const;
    /*!
     */
    void setMinimum(std::optional<double> newMinimum);

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
    [[nodiscard]] static QString convertNumberSchemaTypeToString(McpProtocolNumberSchema::Type type);
    /*!
     */
    [[nodiscard]] static McpProtocolNumberSchema::Type convertNumberSchemaTypeFromString(const QString &str);

private:
    std::optional<double> mDefaultValue;
    std::optional<QString> mDescription;
    std::optional<double> mMaximum;
    std::optional<double> mMinimum;
    std::optional<QString> mTitle;
    Type mType = Type::Unknown;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema &t);
