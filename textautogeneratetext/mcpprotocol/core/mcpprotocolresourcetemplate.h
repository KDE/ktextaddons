/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolResourceTemplate
{
public:
    /*!
     */
    McpProtocolResourceTemplate();
    /*!
     */
    ~McpProtocolResourceTemplate();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolResourceTemplate &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolResourceTemplate fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolResourceTemplate &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolAnnotations> annotations() const;
    /*!
     */
    void setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations);

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
    [[nodiscard]] std::optional<QString> mimeType() const;
    /*!
     */
    void setMimeType(std::optional<QString> newMimeType);

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
    [[nodiscard]] QString uriTemplate() const;
    /*!
     */
    void setUriTemplate(const QString &newUriTemplate);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<McpProtocolAnnotations> mAnnotations;
    std::optional<QString> mDescription;
    std::optional<QList<McpProtocolIcon>> mIcons;
    std::optional<QString> mMimeType;
    QString mName;
    std::optional<QString> mTitle;
    QString mUriTemplate;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolResourceTemplate, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResourceTemplate &t);
