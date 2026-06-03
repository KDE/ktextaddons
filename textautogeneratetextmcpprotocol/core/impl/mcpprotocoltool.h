/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"

#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolIcon>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolExecution>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTool
{
public:
    struct InputSchema {
        std::optional<QString> mDollarschema;
        std::optional<QMap<QString, QJsonObject>> mProperties;
        std::optional<QStringList> mRequired;
        const std::optional<QString> &dollarschema() const
        {
            return mDollarschema;
        }
        const std::optional<QMap<QString, QJsonObject>> &properties() const
        {
            return mProperties;
        }
        const std::optional<QStringList> &required() const
        {
            return mRequired;
        }
        [[nodiscard]] bool operator==(const InputSchema &other) const;
    };

    struct OutputSchema {
        std::optional<QString> mDollarschema;
        std::optional<QMap<QString, QJsonObject>> mProperties;
        std::optional<QStringList> mRequired;
        const std::optional<QString> &dollarschema() const
        {
            return mDollarschema;
        }
        const std::optional<QMap<QString, QJsonObject>> &properties() const
        {
            return mProperties;
        }
        const std::optional<QStringList> &required() const
        {
            return mRequired;
        }
        [[nodiscard]] bool operator==(const OutputSchema &other) const;
    };

    /*!
     */
    McpProtocolTool();
    /*!
     */
    ~McpProtocolTool();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTool &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTool fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTool &image);

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
    void setInputSchema(const InputSchema &newInputSchema);

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
