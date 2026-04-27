/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "mcpprotocolmeta.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;

class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTextContent
{
public:
    /*!
     */
    McpProtocolTextContent();
    /*!
     */
    ~McpProtocolTextContent();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTextContent &other) const;

    /*!
     */
    [[nodiscard]] QString text() const;
    /*!
     */
    void setText(const QString &newText);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolAnnotations> annotations() const;
    /*!
     */
    void setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations);

    /*!
     */
    [[nodiscard]] static McpProtocolTextContent fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTextContent &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

private:
    std::optional<McpProtocolAnnotations> mAnnotations;
    std::optional<McpProtocolMeta> mMeta;
    QString mText;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolTextContent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTextContent &t);
