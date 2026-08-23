/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>

#include <QStringList>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTitledSingleSelectEnumSchema
{
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT OneOfItem {
        QString mConstValue;
        QString mTitle;

        [[nodiscard]] bool operator==(const McpProtocolTitledSingleSelectEnumSchema::OneOfItem &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolTitledSingleSelectEnumSchema::OneOfItem fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolTitledSingleSelectEnumSchema::OneOfItem &image);

        [[nodiscard]] QString constValue() const;
        void setConstValue(const QString &newConstValue);
        [[nodiscard]] QString title() const;
        void setTitle(const QString &newTitle);
    };
    /*!
     */
    McpProtocolTitledSingleSelectEnumSchema();
    /*!
     */
    ~McpProtocolTitledSingleSelectEnumSchema();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTitledSingleSelectEnumSchema &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTitledSingleSelectEnumSchema fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTitledSingleSelectEnumSchema &image);

    /*!
     */
    [[nodiscard]] std::optional<QString> defaultValue() const;
    /*!
     */
    void setDefault(std::optional<QString> newDefault);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] QList<OneOfItem> oneOf() const;
    /*!
     */
    void setOneOf(const QList<OneOfItem> &newOneOf);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

private:
    QList<OneOfItem> mOneOf;
    std::optional<QString> mDefault;
    std::optional<QString> mDescription;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledSingleSelectEnumSchema, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledSingleSelectEnumSchema &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledSingleSelectEnumSchema::OneOfItem &t);
