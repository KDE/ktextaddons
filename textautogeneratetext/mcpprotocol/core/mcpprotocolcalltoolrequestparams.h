/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocoltaskmetadata.h"
#include "mcpprotocolutils.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCallToolRequestParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolCallToolRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolCallToolRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolCallToolRequestParams::Meta &image);
    };

    /*!
     */
    McpProtocolCallToolRequestParams();
    /*!
     */
    ~McpProtocolCallToolRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCallToolRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCallToolRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCallToolRequestParams &image);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonValue>> arguments() const;
    /*!
     */
    void setArguments(std::optional<QMap<QString, QJsonValue>> newArguments);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolTaskMetadata> task() const;
    /*!
     */
    void setTask(std::optional<McpProtocolTaskMetadata> newTask);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

private:
    std::optional<Meta> mMeta;
    std::optional<QMap<QString, QJsonValue>> mArguments;
    QString mName;
    std::optional<McpProtocolTaskMetadata> mTask;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequestParams::Meta &t);
