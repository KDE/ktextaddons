/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientCapabilities>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImplementation>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolInitializeRequestParams
{
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolInitializeRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolInitializeRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolInitializeRequestParams::Meta &meta);
    };

    /*!
     */
    McpProtocolInitializeRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolInitializeRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolInitializeRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolInitializeRequestParams &params);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    /*!
     */
    [[nodiscard]] QString protocolVersion() const;
    /*!
     */
    void setProtocolVersion(const QString &newProtocolVersion);

    /*!
     */
    [[nodiscard]] McpProtocolImplementation clientInfo() const;
    /*!
     */
    void setClientInfo(McpProtocolImplementation newClientInfo);

    /*!
     */
    [[nodiscard]] McpProtocolClientCapabilities capabilities() const;
    /*!
     */
    void setCapabilities(McpProtocolClientCapabilities newCapabilities);

private:
    std::optional<Meta> mMeta;
    McpProtocolClientCapabilities mCapabilities;
    McpProtocolImplementation mClientInfo;
    QString mProtocolVersion;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams::Meta &t);
