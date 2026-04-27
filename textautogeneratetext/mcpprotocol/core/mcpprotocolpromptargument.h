/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolPromptArgument
{
public:
    /*!
     */
    McpProtocolPromptArgument();
    /*!
     */
    ~McpProtocolPromptArgument();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolPromptArgument &other) const;

    /*!
     */
    static McpProtocolPromptArgument fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolPromptArgument &image);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] std::optional<bool> required() const;
    /*!
     */
    void setRequired(std::optional<bool> newRequired);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

private:
    std::optional<QString> mDescription;
    QString mName;
    std::optional<bool> mRequired;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptArgument, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptArgument &t);
