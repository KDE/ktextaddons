/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServerCapabilities
{
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Prompts {
        std::optional<bool> mListChanged;

        Prompts &listChanged(std::optional<bool> v);

        const std::optional<bool> &listChanged() const;
    };

    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Resources {
        std::optional<bool> mListChanged;
        std::optional<bool> mSubscribe;

        Resources &listChanged(std::optional<bool> v)
        {
            mListChanged = v;
            return *this;
        }
        Resources &subscribe(std::optional<bool> v)
        {
            mSubscribe = v;
            return *this;
        }

        const std::optional<bool> &listChanged() const
        {
            return mListChanged;
        }
        const std::optional<bool> &subscribe() const
        {
            return mSubscribe;
        }
    };
    /*!
     */
    McpProtocolServerCapabilities();
    /*!
     */
    ~McpProtocolServerCapabilities();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolServerCapabilities &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolServerCapabilities fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolServerCapabilities &image);
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Prompts &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Resources &t);
