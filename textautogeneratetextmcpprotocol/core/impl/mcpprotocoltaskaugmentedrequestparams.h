/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTaskMetadata>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTaskAugmentedRequestParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolTaskAugmentedRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolTaskAugmentedRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolTaskAugmentedRequestParams::Meta &image);
    };

    /*!
     */
    McpProtocolTaskAugmentedRequestParams();
    /*!
     */
    ~McpProtocolTaskAugmentedRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTaskAugmentedRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTaskAugmentedRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTaskAugmentedRequestParams &image);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolTaskMetadata> tasks() const;
    /*!
     */
    void setTasks(std::optional<McpProtocolTaskMetadata> newTasks);

private:
    std::optional<Meta> mMeta;
    std::optional<McpProtocolTaskMetadata> mTasks;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskAugmentedRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskAugmentedRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskAugmentedRequestParams::Meta &t);
