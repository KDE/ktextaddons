/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolaudiocontent.h"
#include "mcpprotocolembeddedresource.h"
#include "mcpprotocolimagecontent.h"
#include "mcpprotocolresourcelink.h"
#include "mcpprotocoltextcontent.h"
#include "mcpprotocolutils.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolPromptMessage
{
    Q_GADGET
public:
    /*!
     */
    McpProtocolPromptMessage();
    /*!
     */
    ~McpProtocolPromptMessage();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolPromptMessage &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolPromptMessage fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolPromptMessage &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::ContentBlock content() const;
    /*!
     */
    void setContent(const McpProtocolUtils::ContentBlock &newContent);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::Role role() const;
    /*!
     */
    void setRole(McpProtocolUtils::Role newRole);

private:
    McpProtocolUtils::ContentBlock mContent;
    McpProtocolUtils::Role mRole = McpProtocolUtils::Role::Unknown;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolPromptMessage, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPromptMessage &t);
