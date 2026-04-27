/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "mcpprotocolicon.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QList>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolImplementation
{
public:
    /*!
     */
    McpProtocolImplementation();
    /*!
     */
    ~McpProtocolImplementation();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolImplementation &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolImplementation fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolImplementation &image);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] std::optional<QList<McpProtocolIcon>> icons() const;
    /*!
     */
    void setIcons(std::optional<QList<McpProtocolIcon>> newIcons);

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

    /*!
     */
    [[nodiscard]] QString version() const;
    /*!
     */
    void setVersion(const QString &newVersion);

    /*!
     */
    [[nodiscard]] std::optional<QString> websiteUrl() const;
    /*!
     */
    void setWebsiteUrl(std::optional<QString> newWebsiteUrl);

private:
    std::optional<QString> mDescription;
    std::optional<QList<McpProtocolIcon>> mIcons;
    QString mName;
    std::optional<QString> mTitle;
    QString mVersion;
    std::optional<QString> mWebsiteUrl;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolImplementation, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolImplementation &t);
