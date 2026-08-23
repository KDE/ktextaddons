/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QMap>
#include <QObject>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolElicitResult
{
    Q_GADGET
public:
    enum class Action : uint8_t {
        Accept = 0,
        Cancel,
        Decline,
        Unknown,
    };
    Q_ENUM(Action)

    /*!
     */
    McpProtocolElicitResult();
    /*!
     */
    ~McpProtocolElicitResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolElicitResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolElicitResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolElicitResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] Action action() const;
    /*!
     */
    void setAction(Action newAction);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, McpProtocolUtils::ElicitResultContentValue>> content() const;
    /*!
     */
    void setContent(std::optional<QMap<QString, McpProtocolUtils::ElicitResultContentValue>> newContent);

    /*!
     */
    [[nodiscard]] static QString convertActionToString(McpProtocolElicitResult::Action action);

    /*!
     */
    [[nodiscard]] static McpProtocolElicitResult::Action convertActionFromString(const QString &str);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QMap<QString, McpProtocolUtils::ElicitResultContentValue>> mContent;
    Action mAction = Action::Unknown;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &t);
