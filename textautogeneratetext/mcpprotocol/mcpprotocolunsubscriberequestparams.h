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
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolUnsubscribeRequestParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolUnsubscribeRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolUnsubscribeRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolUnsubscribeRequestParams::Meta &image);
    };

    /*!
     */
    McpProtocolUnsubscribeRequestParams();
    /*!
     */
    ~McpProtocolUnsubscribeRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolUnsubscribeRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolUnsubscribeRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolUnsubscribeRequestParams &image);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    [[nodiscard]] QString uri() const;
    void setUri(const QString &newUri);

private:
    std::optional<Meta> mMeta;
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolUnsubscribeRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUnsubscribeRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUnsubscribeRequestParams::Meta &t);
