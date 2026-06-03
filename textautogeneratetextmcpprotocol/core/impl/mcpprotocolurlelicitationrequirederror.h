/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolURLElicitationRequiredError
{
public:
    /*!
     */
    McpProtocolURLElicitationRequiredError();
    /*!
     */
    ~McpProtocolURLElicitationRequiredError();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolURLElicitationRequiredError &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolURLElicitationRequiredError fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolURLElicitationRequiredError &image);

private:
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolURLElicitationRequiredError, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolURLElicitationRequiredError &t);
