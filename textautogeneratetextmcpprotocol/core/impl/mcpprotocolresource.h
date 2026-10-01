/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QList>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolAnnotations>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolIcon>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <optional>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolResource
{
public:
    /*!
     */
    McpProtocolResource();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolResource &other) const;
    /*!
     */
    [[nodiscard]] static McpProtocolResource fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolResource &resource);

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
    [[nodiscard]] std::optional<qint64> size() const;
    /*!
     */
    void setSize(std::optional<qint64> newSize);

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
    std::optional<qint64> mSize;
    std::optional<QString> mTitle;
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolResource, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolResource &t);
