/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRequestMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolGetPromptRequestParams
{
public:
    using Meta = McpProtocolRequestMeta;

    /*!
     */
    McpProtocolGetPromptRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolGetPromptRequestParams &other) const;

    /*!
     */
    [[nodiscard]] bool isValid() const;

    /*!
     */
    [[nodiscard]] static McpProtocolGetPromptRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolGetPromptRequestParams &params);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QString>> arguments() const;
    /*!
     */
    void setArguments(std::optional<QMap<QString, QString>> newArguments);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

private:
    std::optional<Meta> mMeta;
    std::optional<QMap<QString, QString>> mArguments;
    QString mName;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequestParams &t);
