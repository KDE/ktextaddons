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
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolAudioContent
{
public:
    /*!
     */
    McpProtocolAudioContent();
    /*!
     */
    ~McpProtocolAudioContent();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolAudioContent &other) const;

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolAnnotations> annotations() const;
    /*!
     */
    void setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations);

    /*!
     */
    [[nodiscard]] static McpProtocolAudioContent fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolAudioContent &image);

    /*!
     */
    [[nodiscard]] QString data() const;
    /*!
     */
    void setData(const QString &newData);

    /*!
     */
    [[nodiscard]] QString mimeType() const;
    /*!
     */
    void setMimeType(const QString &newMimeType);

    /*!
     */
    [[nodiscard]] bool isValid() const;

    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    void setMeta(std::optional<McpProtocolMeta> newMeta);

private:
    std::optional<McpProtocolAnnotations> mAnnotations;
    std::optional<McpProtocolMeta> mMeta;
    QString mData;
    QString mMimeType;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolAudioContent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolAudioContent &t);
