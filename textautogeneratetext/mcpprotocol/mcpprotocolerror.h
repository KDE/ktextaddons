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
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolError
{
    Q_GADGET
public:
    /*!
     */
    McpProtocolError();
    /*!
     */
    ~McpProtocolError();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolError &other) const;

    /*!
     */
    static McpProtocolError fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolError &image);
    /*!
     */
    [[nodiscard]] int code() const;
    /*!
     */
    void setCode(int newCode);

    /*!
     */
    [[nodiscard]] std::optional<QString> data() const;
    /*!
     */
    void setData(std::optional<QString> newData);

    /*!
     */
    [[nodiscard]] QString message() const;
    /*!
     */
    void setMessage(const QString &newMessage);

private:
    int mCode = 0;
    std::optional<QString> mData;
    QString mMessage;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolError, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolError &t);
