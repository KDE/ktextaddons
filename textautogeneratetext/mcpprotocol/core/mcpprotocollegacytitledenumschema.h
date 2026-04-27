/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolLegacyTitledEnumSchema
{
public:
    /*!
     */
    McpProtocolLegacyTitledEnumSchema();
    /*!
     */
    ~McpProtocolLegacyTitledEnumSchema();

    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolLegacyTitledEnumSchema &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolLegacyTitledEnumSchema fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolLegacyTitledEnumSchema &image);

    /*!
     */
    [[nodiscard]] std::optional<QString> defaultValue() const;
    /*!
     */
    void setDefaultValue(std::optional<QString> newDefaultValue);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] QStringList enums() const;
    /*!
     */
    void setEnums(const QStringList &newEnums);

    /*!
     */
    [[nodiscard]] std::optional<QStringList> enumNames() const;
    /*!
     */
    void setEnumNames(std::optional<QStringList> newEnumNames);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

private:
    std::optional<QString> mDefaultValue;
    std::optional<QString> mDescription;
    QStringList mEnums;
    std::optional<QStringList> mEnumNames;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolLegacyTitledEnumSchema, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolLegacyTitledEnumSchema &t);
