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
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolPaginatedRequestParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolPaginatedRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolPaginatedRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolPaginatedRequestParams::Meta &image);
    };

    /*!
     */
    McpProtocolPaginatedRequestParams();
    /*!
     */
    ~McpProtocolPaginatedRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolPaginatedRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolPaginatedRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolPaginatedRequestParams &image);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    /*!
     */
    [[nodiscard]] QString cursor() const;
    /*!
     */
    void setCursor(const QString &newCursor);

private:
    std::optional<Meta> mMeta;
    QString mCursor;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolPaginatedRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPaginatedRequestParams &t);
