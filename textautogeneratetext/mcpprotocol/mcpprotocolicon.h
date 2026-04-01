/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocol_export.h"
#include <QMetaType>
#include <QString>
#include <QStringList>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolIcon
{
public:
    /*!
     */
    McpProtocolIcon();
    /*!
     */
    ~McpProtocolIcon();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolIcon &other) const;

    /*!
     */
    [[nodiscard]] std::optional<QString> mimeType() const;
    /*!
     */
    void setMimeType(std::optional<QString> newMimeType);

    /*!
     */
    [[nodiscard]] std::optional<QStringList> sizes() const;
    /*!
     */
    void setSizes(std::optional<QStringList> newSizes);

    /*!
     */
    [[nodiscard]] std::optional<QString> theme() const;
    /*!
     */
    void setTheme(std::optional<QString> newTheme);

    /*!
     */
    [[nodiscard]] QString src() const;
    /*!
     */
    void setSrc(const QString &newSrc);

    /*!
     */
    [[nodiscard]] static McpProtocolIcon fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolIcon &image);

private:
    QString mSrc;
    std::optional<QString> mMimeType;
    std::optional<QStringList> mSizes; // e.g. "48x48", "96x96", "any"
    std::optional<QString> mTheme; // "light" or "dark"
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolIcon, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolIcon &t);
