/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"

#include <QByteArray>
#include <QJsonObject>
#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolIcon>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolExecution>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTool
{
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT InputSchema {
        std::optional<QString> mDollarschema;
        std::optional<QMap<QString, QJsonObject>> mProperties;
        std::optional<QStringList> mRequired;
        [[nodiscard]] const std::optional<QString> &dollarschema() const;
        [[nodiscard]] const std::optional<QMap<QString, QJsonObject>> &properties() const;
        [[nodiscard]] const std::optional<QStringList> &required() const;
        [[nodiscard]] bool operator==(const InputSchema &other) const;
        [[nodiscard]] static McpProtocolTool::InputSchema fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const McpProtocolTool::InputSchema &input);
    };

    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT OutputSchema {
        std::optional<QString> mDollarschema;
        std::optional<QMap<QString, QJsonObject>> mProperties;
        std::optional<QStringList> mRequired;
        [[nodiscard]] const std::optional<QString> &dollarschema() const;
        [[nodiscard]] const std::optional<QMap<QString, QJsonObject>> &properties() const;
        [[nodiscard]] const std::optional<QStringList> &required() const;
        [[nodiscard]] bool operator==(const OutputSchema &other) const;
        [[nodiscard]] static McpProtocolTool::OutputSchema fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const McpProtocolTool::OutputSchema &input);
    };

    /*!
     */
    McpProtocolTool();

    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTool &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTool fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTool &tool);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolToolAnnotations> annotations() const;
    /*!
     */
    void setAnnotations(std::optional<McpProtocolToolAnnotations> newAnnotations);

    /*!
     */
    [[nodiscard]] std::optional<QString> description() const;
    /*!
     */
    void setDescription(std::optional<QString> newDescription);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolToolExecution> execution() const;
    /*!
     */
    void setExecution(std::optional<McpProtocolToolExecution> newExecution);

    /*!
     */
    [[nodiscard]] std::optional<QList<McpProtocolIcon>> icons() const;
    /*!
     */
    void setIcons(std::optional<QList<McpProtocolIcon>> newIcons);

    /*!
     */
    [[nodiscard]] InputSchema inputSchema() const;
    /*!
     */
    void setInputSchema(InputSchema newInputSchema);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] std::optional<OutputSchema> outputSchema() const;
    /*!
     */
    void setOutputSchema(std::optional<OutputSchema> newOutputSchema);

    /*!
     */
    [[nodiscard]] std::optional<QString> title() const;
    /*!
     */
    void setTitle(std::optional<QString> newTitle);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<McpProtocolToolAnnotations> mAnnotations;
    std::optional<QString> mDescription;
    std::optional<McpProtocolToolExecution> mExecution;
    std::optional<QList<McpProtocolIcon>> mIcons;
    InputSchema mInputSchema;
    QString mName;
    std::optional<OutputSchema> mOutputSchema;
    std::optional<QString> mTitle;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolTool, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTool &t);
