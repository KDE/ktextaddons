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
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolToolResultContent
{
public:
    /*!
     */
    McpProtocolToolResultContent();
    /*!
     */
    ~McpProtocolToolResultContent();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    // [[nodiscard]] bool operator==(const McpProtocolToolResultContent &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolToolResultContent fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolToolResultContent &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] QList<McpProtocolUtils::ContentBlock> content() const;
    /*!
     */
    void setContent(const QList<McpProtocolUtils::ContentBlock> &newContent);

    /*!
     */
    [[nodiscard]] std::optional<bool> isError() const;
    /*!
     */
    void setIsError(std::optional<bool> newIsError);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonValue>> structuredContent() const;
    /*!
     */
    void setStructuredContent(std::optional<QMap<QString, QJsonValue>> newStructuredContent);

    /*!
     */
    [[nodiscard]] QString toolUseId() const;
    /*!
     */
    void setToolUseId(const QString &newToolUseId);

private:
    std::optional<McpProtocolMeta> mMeta;

    QList<McpProtocolUtils::ContentBlock> mContent;
    std::optional<bool> mIsError;
    std::optional<QMap<QString, QJsonValue>> mStructuredContent;
    QString mToolUseId;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolToolResultContent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolResultContent &t);
