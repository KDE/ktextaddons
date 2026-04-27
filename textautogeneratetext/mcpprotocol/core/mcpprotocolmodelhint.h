/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolModelHint
{
    Q_GADGET
public:
    /*!
     */
    McpProtocolModelHint();
    /*!
     */
    ~McpProtocolModelHint();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolModelHint &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolModelHint fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolModelHint &image);
    /*!
     */
    [[nodiscard]] std::optional<QString> name() const;
    /*!
     */
    void setName(std::optional<QString> newName);

private:
    std::optional<QString> mName;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolModelHint, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolModelHint &t);
