/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocolpromptmessage.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolGetPromptResult
{
public:
    /*!
     */
    McpProtocolGetPromptResult();
    /*!
     */
    ~McpProtocolGetPromptResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolGetPromptResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolGetPromptResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolGetPromptResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] QList<McpProtocolPromptMessage> messages() const;
    /*!
     */
    void setMessages(const QList<McpProtocolPromptMessage> &newMessages);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mDescription;
    QList<McpProtocolPromptMessage> mMessages;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolGetPromptResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetPromptResult &t);
