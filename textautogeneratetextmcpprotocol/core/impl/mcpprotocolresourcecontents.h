/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolResourceContents
{
public:
    /*!
     */
    McpProtocolResourceContents();
    /*!
     */
    ~McpProtocolResourceContents();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolResourceContents &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolResourceContents fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolResourceContents &image);

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
    [[nodiscard]] QString uri() const;
    /*!
     */
    void setUri(const QString &newUri);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mMimeType;
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceContents, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceContents &t);
