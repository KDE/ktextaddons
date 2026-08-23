/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QMap>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolBooleanSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolLegacyTitledEnumSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolNumberSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolStringSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTaskMetadata>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTitledMultiSelectEnumSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTitledSingleSelectEnumSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUntitledMultiSelectEnumSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUntitledSingleSelectEnumSchema>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>

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
        QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> mProperties;
        std::optional<QStringList> mRequired;

        [[nodiscard]] std::optional<QString> dollarschema() const;
        void setDollarschema(std::optional<QString> newDollarschema);
        [[nodiscard]] std::optional<QStringList> required() const;
        void setRequired(std::optional<QStringList> newRequired);
        [[nodiscard]] QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> properties() const;
        void setProperties(const QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> &newProperties);
        [[nodiscard]] bool operator==(const McpProtocolElicitRequestFormParams::RequestedSchema &other) const;
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
    [[nodiscard]] bool operator==(const McpProtocolElicitRequestFormParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolElicitRequestFormParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolElicitRequestFormParams &image);

    /*!
     */
    [[nodiscard]] static QByteArray mode();

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    /*!
     */
    [[nodiscard]] QString message() const;
    /*!
     */
    void setMessage(const QString &newMessage);

    /*!
     */
    [[nodiscard]] RequestedSchema requestedSchema() const;
    /*!
     */
    void setRequestedSchema(const RequestedSchema &newRequestedSchema);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolTaskMetadata> task() const;
    /*!
     */
    void setTask(std::optional<McpProtocolTaskMetadata> newTask);

private:
    std::optional<Meta> mMeta;
    QString mMessage;
    RequestedSchema mRequestedSchema;
    std::optional<McpProtocolTaskMetadata> mTask;
};
}

Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestFormParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestFormParams &t);
