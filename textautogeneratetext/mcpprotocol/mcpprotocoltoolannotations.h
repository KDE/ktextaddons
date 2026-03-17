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
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolToolAnnotations
{
public:
    /*!
     */
    McpProtocolToolAnnotations();
    /*!
     */
    ~McpProtocolToolAnnotations();

    /*!
     */
    [[nodiscard]] bool destructiveHint() const;
    /*!
     */
    void setDestructiveHint(bool newDestructiveHint);

    /*!
     */
    [[nodiscard]] bool idempotentHint() const;
    /*!
     */
    void setIdempotentHint(bool newIdempotentHint);

    /*!
     */
    [[nodiscard]] bool openWorldHint() const;
    /*!
     */
    void setOpenWorldHint(bool newOpenWorldHint);

    /*!
     */
    [[nodiscard]] bool readOnlyHint() const;
    /*!
     */
    void setReadOnlyHint(bool newReadOnlyHint);

    /*!
     */
    [[nodiscard]] QString title() const;
    /*!
     */
    void setTitle(const QString &newTitle);

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolToolAnnotations &other) const;

    static McpProtocolToolAnnotations fromJson(const QJsonObject &obj);
    static QJsonObject toJson(const McpProtocolToolAnnotations &text);

private:
    bool mDestructiveHint = true;
    bool mIdempotentHint = false;
    bool mOpenWorldHint = true;
    bool mReadOnlyHint = false;
    QString mTitle;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolToolAnnotations, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolAnnotations &t);
