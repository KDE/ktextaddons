/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolutils.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QList>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolAnnotations
{
public:
    /*!
     */
    McpProtocolAnnotations();
    /*!
     */
    ~McpProtocolAnnotations();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolAnnotations &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolAnnotations fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolAnnotations &annot);

    /*!
     */
    [[nodiscard]] std::optional<double> priority() const;
    /*!
     */
    void setPriority(std::optional<double> newPriority);

    /*!
     */
    [[nodiscard]] std::optional<QString> lastModified() const;
    /*!
     */
    void setLastModified(std::optional<QString> newLastModified);

    /*!
     */
    [[nodiscard]] std::optional<QList<McpProtocolUtils::Role>> audience() const;
    /*!
     */
    void setAudience(std::optional<QList<McpProtocolUtils::Role>> newAudience);

private:
    std::optional<QString> mLastModified;
    std::optional<double> mPriority;
    std::optional<QList<McpProtocolUtils::Role>> mAudience;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolAnnotations, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolAnnotations &t);
