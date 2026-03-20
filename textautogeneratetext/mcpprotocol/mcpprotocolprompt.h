/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolicon.h"
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolpromptargument.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolPrompt
{
public:
    /*!
     */
    McpProtocolPrompt();
    /*!
     */
    ~McpProtocolPrompt();

    [[nodiscard]] bool operator==(const McpProtocolPrompt &other) const;
    [[nodiscard]] static McpProtocolPrompt fromJson(const QJsonObject &obj);
    [[nodiscard]] static QJsonObject toJson(const McpProtocolPrompt &boolean);
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    [[nodiscard]] std::optional<QList<McpProtocolPromptArgument>> arguments() const;
    void setArguments(std::optional<QList<McpProtocolPromptArgument>> newArguments);

    [[nodiscard]] std::optional<QString> description() const;
    void setDescription(std::optional<QString> newDescription);

    [[nodiscard]] std::optional<QList<McpProtocolIcon>> icons() const;
    void setIcons(std::optional<QList<McpProtocolIcon>> newIcons);

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] std::optional<QString> title() const;
    void setTitle(std::optional<QString> newTitle);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QList<McpProtocolPromptArgument>> mArguments;
    std::optional<QString> mDescription;
    std::optional<QList<McpProtocolIcon>> mIcons;
    QString mName;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolPrompt, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPrompt &t);
