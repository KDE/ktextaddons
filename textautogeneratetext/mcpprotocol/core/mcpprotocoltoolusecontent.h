/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "mcpprotocolmeta.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
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

    /*!
     */
    [[nodiscard]] QMap<QString, QJsonValue> input() const;
    /*!
     */
    void setInput(const QMap<QString, QJsonValue> &newInput);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

private:
    std::optional<McpProtocolMeta> mMeta;
    QMap<QString, QJsonValue> mInput;

    QString mName;
    QString mId;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolToolUseContent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolUseContent &t);
