/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolProgressNotificationParams
{
public:
    /*!
     */
    McpProtocolProgressNotificationParams();
    /*!
     */
    ~McpProtocolProgressNotificationParams();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolProgressNotificationParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolProgressNotificationParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolProgressNotificationParams &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<QString> message() const;
    /*!
     */
    void setMessage(std::optional<QString> newMessage);

    /*!
     */
    [[nodiscard]] double progress() const;
    /*!
     */
    void setProgress(double newProgress);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::ProgressToken progressToken() const;
    /*!
     */
    void setProgressToken(const McpProtocolUtils::ProgressToken &newProgressToken);

    /*!
     */
    [[nodiscard]] std::optional<double> total() const;
    /*!
     */
    void setTotal(std::optional<double> newTotal);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mMessage;
    double mProgress = 0.0;
    McpProtocolUtils::ProgressToken mProgressToken;
    std::optional<double> mTotal;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolProgressNotificationParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolProgressNotificationParams &t);
