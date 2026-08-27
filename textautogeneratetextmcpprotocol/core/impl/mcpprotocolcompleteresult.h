/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonObject>
#include <QString>
#include <QStringList>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>

class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCompleteResult
{
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Completion {
        QStringList mValues;
        std::optional<bool> mHasMore;
        std::optional<int> mTotal;

        [[nodiscard]] bool operator==(const McpProtocolCompleteResult::Completion &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolCompleteResult::Completion fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolCompleteResult::Completion &image);

        [[nodiscard]] QStringList values() const;
        void setValues(const QStringList &newValues);
        [[nodiscard]] std::optional<bool> hasMore() const;
        void setHasMore(std::optional<bool> newHasMore);
        [[nodiscard]] std::optional<int> total() const;
        void setTotal(std::optional<int> newTotal);
    };

    /*!
     */
    McpProtocolCompleteResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCompleteResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCompleteResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCompleteResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] Completion completion() const;
    /*!
     */
    void setCompletion(const Completion &newCompletion);

private:
    std::optional<McpProtocolMeta> mMeta;
    Completion mCompletion;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteResult &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteResult::Completion &t);
