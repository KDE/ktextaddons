/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>

#include <QStringList>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolUntitledSingleSelectEnumSchema
{
public:
    /*!
     */
    McpProtocolUntitledSingleSelectEnumSchema();
    /*!
     */
    ~McpProtocolUntitledSingleSelectEnumSchema();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolUntitledSingleSelectEnumSchema &other) const;

    /*!
     */
    static McpProtocolUntitledSingleSelectEnumSchema fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolUntitledSingleSelectEnumSchema &image);

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
    [[nodiscard]] std::optional<QString> defaultValue() const;
    /*!
     */
    void setDefaultValue(std::optional<QString> newDefaultValue);

    /*!
     */
    [[nodiscard]] QStringList enums() const;
    /*!
     */
    void setEnums(const QStringList &newEnums);

private:
    QStringList mEnums;
    std::optional<QString> mDefaultValue;
    std::optional<QString> mDescription;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolUntitledSingleSelectEnumSchema, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUntitledSingleSelectEnumSchema &t);
