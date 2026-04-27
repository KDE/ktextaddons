/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolBooleanSchema
{
public:
    /*!
     */
    McpProtocolBooleanSchema();
    /*!
     */
    ~McpProtocolBooleanSchema();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolBooleanSchema &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolBooleanSchema fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolBooleanSchema &image);

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

private:
    std::optional<bool> mDefaultValue;
    std::optional<QString> mDescription;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolBooleanSchema, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolBooleanSchema &t);
