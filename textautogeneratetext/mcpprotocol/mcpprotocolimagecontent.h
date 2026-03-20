/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolImageContent
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
    [[nodiscard]] QJsonObject meta() const;
    /*!
     */
    void setMeta(const QJsonObject &newMeta);

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
    QString mMimeType;
    QString mData;
    QJsonObject mMeta;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolImageContent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolImageContent &t);
