/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolToolAnnotations
{
public:
    /*!
     */
    McpProtocolToolAnnotations();

    /*!
     */
    [[nodiscard]] std::optional<bool> destructiveHint() const;
    /*!
     */
    void setDestructiveHint(std::optional<bool> newDestructiveHint);

    /*!
     */
    [[nodiscard]] std::optional<bool> idempotentHint() const;
    /*!
     */
    void setIdempotentHint(std::optional<bool> newIdempotentHint);

    /*!
     */
    [[nodiscard]] std::optional<bool> openWorldHint() const;
    /*!
     */
    void setOpenWorldHint(std::optional<bool> newOpenWorldHint);

    /*!
     */
    [[nodiscard]] std::optional<bool> readOnlyHint() const;
    /*!
     */
    void setReadOnlyHint(std::optional<bool> newReadOnlyHint);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolToolAnnotations &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolToolAnnotations fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolToolAnnotations &toolAnnotations);

private:
    std::optional<bool> mDestructiveHint;
    std::optional<bool> mIdempotentHint;
    std::optional<bool> mOpenWorldHint;
    std::optional<bool> mReadOnlyHint;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations &t);
