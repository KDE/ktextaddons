/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>
#include <QString>
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServerCapabilities
{
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Prompts {
        std::optional<bool> mListChanged;

        Prompts &listChanged(std::optional<bool> v);

        const std::optional<bool> &listChanged() const;

        [[nodiscard]] bool operator==(const McpProtocolServerCapabilities::Prompts &other) const;
        [[nodiscard]] static McpProtocolServerCapabilities::Prompts fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const McpProtocolServerCapabilities::Prompts &image);
    };

    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Resources {
        std::optional<bool> mListChanged;
        std::optional<bool> mSubscribe;

        Resources &listChanged(std::optional<bool> v);
        Resources &subscribe(std::optional<bool> v);

        const std::optional<bool> &listChanged() const;
        const std::optional<bool> &subscribe() const;

        [[nodiscard]] bool operator==(const McpProtocolServerCapabilities::Resources &other) const;
        [[nodiscard]] static McpProtocolServerCapabilities::Resources fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const McpProtocolServerCapabilities::Resources &image);
    };
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Tools {
        std::optional<bool> mListChanged;

        Tools &listChanged(std::optional<bool> v);

        const std::optional<bool> &listChanged() const;

        [[nodiscard]] bool operator==(const McpProtocolServerCapabilities::Tools &other) const;
        [[nodiscard]] static McpProtocolServerCapabilities::Tools fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const McpProtocolServerCapabilities::Tools &image);
    };
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Tasks {
        struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Requests {
            struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Tools {
                std::optional<QMap<QString, QJsonValue>> mCall;

                [[nodiscard]] bool operator==(const Tools &other) const;
                [[nodiscard]] static Tools fromJson(const QJsonObject &obj);
                [[nodiscard]] static QJsonObject toJson(const Tools &image);

                [[nodiscard]] std::optional<QMap<QString, QJsonValue>> call() const;
                void setCall(std::optional<QMap<QString, QJsonValue>> newCall);
            };
            std::optional<Tools> mTools;

            [[nodiscard]] bool operator==(const Requests &other) const;
            [[nodiscard]] static Requests fromJson(const QJsonObject &obj);
            [[nodiscard]] static QJsonObject toJson(const Requests &image);

            [[nodiscard]] std::optional<Tools> tools() const;
            void setTools(std::optional<Tools> newTools);
        };

        std::optional<QMap<QString, QJsonValue>> mCancel;
        std::optional<QMap<QString, QJsonValue>> mList;
        std::optional<Requests> mRequests;

        [[nodiscard]] bool operator==(const Tasks &other) const;
        [[nodiscard]] static Tasks fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const Tasks &image);

        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> cancel() const;
        void setCancel(std::optional<QMap<QString, QJsonValue>> newCancel);
        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> list() const;
        void setList(std::optional<QMap<QString, QJsonValue>> newList);
        [[nodiscard]] std::optional<Requests> requests() const;
        void setRequests(std::optional<Requests> newRequests);
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

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonValue>> completions() const;
    /*!
     */
    void setCompletions(std::optional<QMap<QString, QJsonValue>> newCompletions);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonObject>> experimental() const;
    /*!
     */
    void setExperimental(std::optional<QMap<QString, QJsonObject>> newExperimental);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonValue>> logging() const;
    /*!
     */
    void setLogging(std::optional<QMap<QString, QJsonValue>> newLogging);

    /*!
     */
    [[nodiscard]] std::optional<Prompts> prompts() const;
    /*!
     */
    void setPrompts(std::optional<Prompts> newPrompts);

    /*!
     */
    [[nodiscard]] std::optional<Resources> resources() const;
    /*!
     */
    void setResources(std::optional<Resources> newResources);

    /*!
     */
    [[nodiscard]] std::optional<Tasks> tasks() const;
    /*!
     */
    void setTasks(std::optional<Tasks> newTasks);

    /*!
     */
    [[nodiscard]] std::optional<Tools> tools() const;
    /*!
     */
    void setTools(std::optional<Tools> newTools);

private:
    std::optional<QMap<QString, QJsonValue>> mCompletions;
    std::optional<QMap<QString, QJsonObject>> mExperimental;
    std::optional<QMap<QString, QJsonValue>> mLogging;
    std::optional<Prompts> mPrompts;
    std::optional<Resources> mResources;
    std::optional<Tasks> mTasks;
    std::optional<Tools> mTools;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Prompts &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Resources &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Tools &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Tasks &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Tasks::Requests &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug
operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Tasks::Requests::Tools &t);
