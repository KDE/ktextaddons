/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolResourceUpdatedNotificationParams
{
public:
    /*!
     */
    McpProtocolResourceUpdatedNotificationParams();
    /*!
     */
    ~McpProtocolResourceUpdatedNotificationParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolResourceUpdatedNotificationParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolResourceUpdatedNotificationParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolResourceUpdatedNotificationParams &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] QString uri() const;
    void setUri(const QString &newUri);

private:
    std::optional<McpProtocolMeta> mMeta;
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceUpdatedNotificationParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceUpdatedNotificationParams &t);
