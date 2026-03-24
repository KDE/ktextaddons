/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolpromptreference.h"
#include "mcpprotocolresourcetemplatereference.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolCompleteRequestParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolCompleteRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolCompleteRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolCompleteRequestParams::Meta &image);
    };

    struct Argument {
        QString mName;
        QString mValue;
        /*!
         */
        [[nodiscard]] static McpProtocolCompleteRequestParams::Argument fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolCompleteRequestParams::Argument &image);
        [[nodiscard]] bool operator==(const McpProtocolCompleteRequestParams::Argument &other) const;
    };

    struct Context {
        std::optional<QMap<QString, QString>> mArguments;
        /*!
         */
        [[nodiscard]] static McpProtocolCompleteRequestParams::Context fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolCompleteRequestParams::Context &image);
        [[nodiscard]] bool operator==(const McpProtocolCompleteRequestParams::Context &other) const;
    };
    /*!
     */
    McpProtocolCompleteRequestParams();
    /*!
     */
    ~McpProtocolCompleteRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCompleteRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCompleteRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCompleteRequestParams &image);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

private:
    Argument mArgument;
    std::optional<Context> mContext;
    McpProtocolUtils::CompleteRequestParamsRef mRef;
    std::optional<Meta> mMeta;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolCompleteRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCompleteRequestParams &t);
