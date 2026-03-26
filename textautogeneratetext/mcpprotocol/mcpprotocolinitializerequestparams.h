/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolInitializeRequestParams
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

    QString protocolVersion() const;
    void setProtocolVersion(const QString &newProtocolVersion);

private:
    std::optional<Meta> mMeta;
    // TODO ClientCapabilities mCapabilities;
    // TODO Implementation mClientInfo;
    QString mProtocolVersion;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolInitializeRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolInitializeRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolInitializeRequestParams::Meta &t);
