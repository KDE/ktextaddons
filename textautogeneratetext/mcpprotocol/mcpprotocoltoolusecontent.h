/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolToolUseContent
{
public:
    /*!
     */
    McpProtocolToolUseContent();
    /*!
     */
    ~McpProtocolToolUseContent();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolToolUseContent &other) const;

    /*!
     */
    [[nodiscard]] QJsonObject meta() const;
    /*!
     */
    void setMeta(const QJsonObject &newMeta);

    /*!
     */
    [[nodiscard]] static McpProtocolToolUseContent fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolToolUseContent &image);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] QString id() const;
    /*!
     */
    void setId(const QString &newId);

private:
    QJsonObject mMeta;
    QString mName;
    QString mId;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolToolUseContent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolUseContent &t);
