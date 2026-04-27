/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolBaseMetadata
{
public:
    /*!
     */
    McpProtocolBaseMetadata();
    /*!
     */
    ~McpProtocolBaseMetadata();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolBaseMetadata &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolBaseMetadata fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolBaseMetadata &image);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

private:
    QString mName;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolBaseMetadata, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolBaseMetadata &t);
