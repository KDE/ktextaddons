/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <QStringList>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolError>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolUnsupportedProtocolVersionError
{
public:
    /*!
     */
    McpProtocolUnsupportedProtocolVersionError();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolUnsupportedProtocolVersionError &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolUnsupportedProtocolVersionError fromJson(const QJsonObject &obj);
    /*!
     * JSON-RPC error code used by this error
     */
    static constexpr int errorCode = -32022;
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolUnsupportedProtocolVersionError &unsupportedProtocolVersionError);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolUtils::RequestId> id() const;
    /*!
     */
    void setId(std::optional<McpProtocolUtils::RequestId> newId);

    /*!
     */
    [[nodiscard]] McpProtocolError error() const;
    /*!
     */
    void setError(const McpProtocolError &newError);

    /*!
     * Protocol versions supported by server ("error.data.supported").
     */
    [[nodiscard]] QStringList supported() const;

    /*!
     * Protocol version requested by client ("error.data.requested").
     */
    [[nodiscard]] QString requested() const;

private:
    std::optional<McpProtocolUtils::RequestId> mId;
    McpProtocolError mError;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolUnsupportedProtocolVersionError, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolUnsupportedProtocolVersionError &t);
