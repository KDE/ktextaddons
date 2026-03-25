/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "mcpprotocolmeta.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolRoot
{
public:
    /*!
     */
    McpProtocolRoot();
    /*!
     */
    ~McpProtocolRoot();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolRoot &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolRoot fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolRoot &image);

    /*!
     */
    [[nodiscard]] std::optional<QString> name() const;
    /*!
     */
    void setName(std::optional<QString> newName);

    /*!
     */
    [[nodiscard]] QString uri() const;
    /*!
     */
    void setUri(const QString &newUri);

    std::optional<McpProtocolMeta> meta() const;
    void setMeta(std::optional<McpProtocolMeta> newMeta);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mName;
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolRoot, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolRoot &t);
