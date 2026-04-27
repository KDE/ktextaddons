/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;

class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTextResourceContents
{
public:
    /*!
     */
    McpProtocolTextResourceContents();
    /*!
     */
    ~McpProtocolTextResourceContents();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTextResourceContents &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTextResourceContents fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTextResourceContents &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<QString> mimeType() const;
    /*!
     */
    void setMimeType(std::optional<QString> newMimeType);

    /*!
     */
    [[nodiscard]] QString text() const;
    /*!
     */
    void setText(const QString &newText);

    /*!
     */
    [[nodiscard]] QString uri() const;
    /*!
     */
    void setUri(const QString &newUri);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mMimeType;
    QString mText;
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolTextResourceContents, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTextResourceContents &t);
