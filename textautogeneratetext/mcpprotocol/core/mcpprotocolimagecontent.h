/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolmeta.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolImageContent
{
public:
    /*!
     */
    McpProtocolImageContent();
    /*!
     */
    ~McpProtocolImageContent();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] QString mimeType() const;
    /*!
     * \brief setMimeType
     * \param newMimeType
     */
    void setMimeType(const QString &newMimeType);

    /*!
     */
    [[nodiscard]] QString data() const;
    /*!
     */
    void setData(const QString &newData);

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolImageContent &other) const;

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

    /*!
     */
    [[nodiscard]] bool isValid() const;

    /*!
     */
    [[nodiscard]] static McpProtocolImageContent fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolImageContent &image);

private:
    std::optional<McpProtocolAnnotations> mAnnotations;
    std::optional<McpProtocolMeta> mMeta;
    QString mMimeType;
    QString mData;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolImageContent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolImageContent &t);
