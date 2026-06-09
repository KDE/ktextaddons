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
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTitledMultiSelectEnumSchema
{
public:
    struct Items {
        struct AnyOfItem {
            QString mConstValue;
            QString mTitle;
            [[nodiscard]] bool operator==(const McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem &other) const;

            [[nodiscard]] static McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem fromJson(const QJsonObject &obj);
            /*!
             */
            [[nodiscard]] static QJsonObject toJson(const McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem &image);

            [[nodiscard]] QString constValue() const;
            void setConstValue(const QString &newConstValue);
            [[nodiscard]] QString title() const;
            void setTitle(const QString &newTitle);
        };

        QList<AnyOfItem> mAnyOf;

        /*!
         */
        [[nodiscard]] static McpProtocolTitledMultiSelectEnumSchema::Items fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolTitledMultiSelectEnumSchema::Items &image);
        /*!
         */
        [[nodiscard]] bool operator==(const McpProtocolTitledMultiSelectEnumSchema::Items &other) const;

    public:
        QList<AnyOfItem> anyOf() const;
        void setAnyOf(const QList<AnyOfItem> &newAnyOf);
    };
    /*!
     */
    McpProtocolTitledMultiSelectEnumSchema();
    /*!
     */
    ~McpProtocolTitledMultiSelectEnumSchema();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTitledMultiSelectEnumSchema &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTitledMultiSelectEnumSchema fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTitledMultiSelectEnumSchema &image);

    /*!
     */
    [[nodiscard]] std::optional<QStringList> defaultValue() const;
    /*!
     */
    void setDefault(std::optional<QStringList> newDefault);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] Items items() const;
    /*!
     */
    void setItems(const Items &newItems);

    /*!
     */
    [[nodiscard]] std::optional<int> maxItems() const;
    /*!
     */
    void setMaxItems(std::optional<int> newMaxItems);

    /*!
     */
    [[nodiscard]] std::optional<int> minItems() const;
    /*!
     */
    void setMinItems(std::optional<int> newMinItems);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

private:
    std::optional<QStringList> mDefault;
    std::optional<QString> mDescription;
    Items mItems;
    std::optional<int> mMaxItems;
    std::optional<int> mMinItems;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug
operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema::Items &t);
