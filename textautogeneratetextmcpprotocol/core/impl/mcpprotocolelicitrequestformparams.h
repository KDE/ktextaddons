/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolBooleanSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolNumberSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolStringSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTaskMetadata>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUntitledSingleSelectEnumSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
// TODO #include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTitledSingleSelectEnumSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolLegacyTitledEnumSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTitledMultiSelectEnumSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUntitledMultiSelectEnumSchema>

class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolElicitRequestFormParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolElicitRequestFormParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolElicitRequestFormParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolElicitRequestFormParams::Meta &image);
    };
    struct RequestedSchema {
        std::optional<QString> mDollarschema;
        // TODO QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> mProperties;
        std::optional<QStringList> mRequired;

        [[nodiscard]] std::optional<QString> dollarschema() const;
        void setDollarschema(std::optional<QString> newDollarschema);
        [[nodiscard]] std::optional<QStringList> required() const;
        void setRequired(std::optional<QStringList> newRequired);
#if 0 // TODO
        [[nodiscard]] QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> properties() const;
        void setProperties(const QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> &newProperties);
#endif
        /*!
         */
        [[nodiscard]] static McpProtocolElicitRequestFormParams::RequestedSchema fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolElicitRequestFormParams::RequestedSchema &image);
    };
    /*!
     */
    McpProtocolElicitRequestFormParams();
    /*!
     */
    ~McpProtocolElicitRequestFormParams();

    /*!
     */
    [[nodiscard]] static McpProtocolElicitRequestFormParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolElicitRequestFormParams &image);

    /*!
     */
    [[nodiscard]] QString message() const;
    /*!
     */
    void setMessage(const QString &newMessage);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolTaskMetadata> task() const;
    /*!
     */
    void setTask(std::optional<McpProtocolTaskMetadata> newTask);

private:
    std::optional<Meta> mMeta;
    QString mMessage;
    // RequestedSchema mRequestedSchema;
    std::optional<McpProtocolTaskMetadata> mTask;
};
}

Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestFormParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestFormParams &t);
