/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "mcpprotocolicon.h"
#include "mcpprotocolmeta.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolResource
{
public:
    /*!
     */
    McpProtocolResource();
    /*!
     */
    ~McpProtocolResource();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolResource &other) const;
    /*!
     */
    [[nodiscard]] static McpProtocolResource fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolResource &boolean);

    /*!
     */
    [[nodiscard]] QString uri() const;
    /*!
     */
    void setUri(const QString &newUri);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

    /*!
     */
    [[nodiscard]] std::optional<int> size() const;
    /*!
     */
    void setSize(std::optional<int> newSize);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] std::optional<QString> mimeType() const;
    /*!
     */
    void setMimeType(std::optional<QString> newMimeType);

    /*!
     */
    [[nodiscard]] std::optional<QList<McpProtocolIcon>> icons() const;
    /*!
     */
    void setIcons(std::optional<QList<McpProtocolIcon>> newIcons);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolAnnotations> annotations() const;
    /*!
     */
    void setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<McpProtocolAnnotations> mAnnotations;
    std::optional<QString> mDescription;
    std::optional<QList<McpProtocolIcon>> mIcons;
    std::optional<QString> mMimeType;
    QString mName;
    std::optional<int> mSize;
    std::optional<QString> mTitle;
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolResource, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResource &t);
