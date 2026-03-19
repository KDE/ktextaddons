/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolStringSchema
{
public:
    enum class Format : uint8_t {
        Date,
        Dateminustime,
        Email,
        Uri,
        Unknown,
    };

    /*!
     */
    McpProtocolStringSchema();
    /*!
     */
    ~McpProtocolStringSchema();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolStringSchema &other) const;

    /*!
     */
    static McpProtocolStringSchema fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolStringSchema &image);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

    /*!
     */
    [[nodiscard]] std::optional<bool> defaultValue() const;
    /*!
     */
    void setDefaultValue(std::optional<bool> newDefaultValue);

    /*!
     */
    [[nodiscard]] std::optional<int> minLength() const;
    /*!
     */
    void setMinLength(std::optional<int> newMinLength);

    /*!
     */
    [[nodiscard]] std::optional<int> maxLength() const;
    /*!
     */
    void setMaxLength(std::optional<int> newMaxLength);

    /*!
     */
    [[nodiscard]] std::optional<Format> format() const;
    /*!
     */
    void setFormat(std::optional<Format> newFormat);

    /*!
     */
    [[nodiscard]] static QString convertModeToString(McpProtocolStringSchema::Format mode);
    /*!
     */
    [[nodiscard]] static McpProtocolStringSchema::Format convertModeFromString(const QString &str);

private:
    std::optional<Format> mFormat;
    std::optional<int> mMaxLength;
    std::optional<int> mMinLength;
    std::optional<bool> mDefaultValue;
    std::optional<QString> mDescription;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolStringSchema, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolStringSchema &t);
