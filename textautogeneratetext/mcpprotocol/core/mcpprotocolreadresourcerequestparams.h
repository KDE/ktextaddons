/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolReadResourceRequestParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolReadResourceRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolReadResourceRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolReadResourceRequestParams::Meta &image);
    };

    /*!
     */
    McpProtocolReadResourceRequestParams();
    /*!
     */
    ~McpProtocolReadResourceRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolReadResourceRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolReadResourceRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolReadResourceRequestParams &image);

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
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolReadResourceRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolReadResourceRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolReadResourceRequestParams::Meta &t);
