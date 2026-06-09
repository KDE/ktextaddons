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
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolUntitledMultiSelectEnumSchema
{
public:
    struct Items {
        QStringList mEnum;
        [[nodiscard]] bool operator==(const McpProtocolUntitledMultiSelectEnumSchema::Items &other) const;

        [[nodiscard]] QStringList enumValue() const;
        void setEnum(const QStringList &newEnum);

        /*!
         */
        [[nodiscard]] static McpProtocolUntitledMultiSelectEnumSchema::Items fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolUntitledMultiSelectEnumSchema::Items &image);
    };
    /*!
     */
    McpProtocolUntitledMultiSelectEnumSchema();
    /*!
     */
    ~McpProtocolUntitledMultiSelectEnumSchema();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolUntitledMultiSelectEnumSchema &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolUntitledMultiSelectEnumSchema fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolUntitledMultiSelectEnumSchema &image);

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
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolUntitledMultiSelectEnumSchema, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUntitledMultiSelectEnumSchema &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolUntitledMultiSelectEnumSchema::Items &t);
