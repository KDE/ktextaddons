/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolClientCapabilities
{
    Q_GADGET
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT Elicitation {
        [[nodiscard]] bool operator==(const McpProtocolClientCapabilities::Elicitation &other) const;
        [[nodiscard]] static Elicitation fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const Elicitation &image);
        std::optional<QMap<QString, QJsonValue>> mForm;
        std::optional<QMap<QString, QJsonValue>> mUrl;

        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> form() const;
        void setForm(std::optional<QMap<QString, QJsonValue>> newForm);
        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> url() const;
        void setUrl(std::optional<QMap<QString, QJsonValue>> newUrl);
    };

    struct TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT Roots {
        [[nodiscard]] bool operator==(const McpProtocolClientCapabilities::Roots &other) const;
        [[nodiscard]] static Roots fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const Roots &image);
        std::optional<bool> mListChanged;

        [[nodiscard]] std::optional<bool> listChanged() const;
        void setListChanged(std::optional<bool> newListChanged);
    };

    struct TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT Sampling {
        [[nodiscard]] bool operator==(const McpProtocolClientCapabilities::Sampling &other) const;
        [[nodiscard]] static Sampling fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const Sampling &image);

        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> context() const;
        void setContext(std::optional<QMap<QString, QJsonValue>> newContext);
        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> tools() const;
        void setTools(std::optional<QMap<QString, QJsonValue>> newTools);

        std::optional<QMap<QString, QJsonValue>> mContext;
        std::optional<QMap<QString, QJsonValue>> mTools;
    };
    struct TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT Tasks {
        struct TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT Requests {
            struct Elicitation {
                std::optional<QMap<QString, QJsonValue>> mCreate;

                [[nodiscard]] bool operator==(const Elicitation &other) const;
                [[nodiscard]] static Elicitation fromJson(const QJsonObject &obj);
                [[nodiscard]] static QJsonObject toJson(const Elicitation &image);

                [[nodiscard]] std::optional<QMap<QString, QJsonValue>> create() const;
                void setCreate(std::optional<QMap<QString, QJsonValue>> newCreate);
            };
            struct Sampling {
                std::optional<QMap<QString, QJsonValue>> mCreateMessage;

                [[nodiscard]] bool operator==(const Sampling &other) const;
                [[nodiscard]] static Sampling fromJson(const QJsonObject &obj);
                [[nodiscard]] static QJsonObject toJson(const Sampling &image);

                [[nodiscard]] std::optional<QMap<QString, QJsonValue>> createMessage() const;
                void setCreateMessage(std::optional<QMap<QString, QJsonValue>> newCreateMessage);
            };
            [[nodiscard]] bool operator==(const Requests &other) const;
            [[nodiscard]] static Requests fromJson(const QJsonObject &obj);
            [[nodiscard]] static QJsonObject toJson(const Requests &image);

            std::optional<Elicitation> mElicitation;
            std::optional<Sampling> mSampling;

            [[nodiscard]] std::optional<Sampling> sampling() const;
            void setSampling(std::optional<Sampling> newSampling);
            [[nodiscard]] std::optional<Elicitation> elicitation() const;
            void setElicitation(std::optional<Elicitation> newElicitation);
        };

        [[nodiscard]] bool operator==(const Tasks &other) const;
        [[nodiscard]] static Tasks fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const Tasks &image);

        std::optional<QMap<QString, QJsonValue>> mCancel;
        std::optional<QMap<QString, QJsonValue>> mList;
        std::optional<Requests> mRequests;

        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> list() const;
        void setList(std::optional<QMap<QString, QJsonValue>> newList);
        [[nodiscard]] std::optional<QMap<QString, QJsonValue>> cancel() const;
        void setCancel(std::optional<QMap<QString, QJsonValue>> newCancel);
        [[nodiscard]] std::optional<Requests> requests() const;
        void setRequests(std::optional<Requests> newRequests);
    };

    /*!
     */
    McpProtocolClientCapabilities();
    /*!
     */
    ~McpProtocolClientCapabilities();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolClientCapabilities &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolClientCapabilities fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolClientCapabilities &image);

    /*!
     */
    [[nodiscard]] std::optional<Elicitation> elicitation() const;
    /*!
     */
    void setElicitation(std::optional<Elicitation> newElicitation);

    /*!
     */
    [[nodiscard]] std::optional<Roots> roots() const;
    /*!
     */
    void setRoots(std::optional<Roots> newRoots);

    /*!
     */
    [[nodiscard]] std::optional<Sampling> sampling() const;
    /*!
     */
    void setSampling(std::optional<Sampling> newSampling);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonObject>> experimental() const;
    /*!
     */
    void setExperimental(std::optional<QMap<QString, QJsonObject>> newExperimental);

    /*!
     */
    [[nodiscard]] std::optional<Tasks> tasks() const;
    /*!
     */
    void setTasks(std::optional<Tasks> newTasks);

private:
    std::optional<Elicitation> mElicitation;
    std::optional<Roots> mRoots;
    std::optional<Sampling> mSampling;
    std::optional<QMap<QString, QJsonObject>> mExperimental;
    std::optional<Tasks> mTasks;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolClientCapabilities, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Elicitation &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Roots &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Sampling &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Tasks &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Tasks::Requests &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Tasks::Requests::Sampling &t);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities::Tasks::Requests::Elicitation &t);
