/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolclientcapabilities.h"
#include "mcpprotocolimplementation.h"
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolInitializeRequestParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolInitializeRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolInitializeRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolInitializeRequestParams::Meta &image);
    };

    /*!
     */
    McpProtocolInitializeRequestParams();
    /*!
     */
    ~McpProtocolInitializeRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolInitializeRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolInitializeRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolInitializeRequestParams &image);

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
    void setClientInfo(const McpProtocolImplementation &newClientInfo);

    /*!
     */
    [[nodiscard]] McpProtocolClientCapabilities capabilities() const;
    /*!
     */
    void setCapabilities(const McpProtocolClientCapabilities &newCapabilities);

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
