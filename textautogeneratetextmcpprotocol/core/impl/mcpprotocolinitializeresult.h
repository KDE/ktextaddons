/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImplementation>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolInitializeResult
{
public:
    /*!
     */
    McpProtocolInitializeResult();
    /*!
     */
    ~McpProtocolInitializeResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolInitializeResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolInitializeResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolInitializeResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<QString> instructions() const;
    /*!
     */
    void setInstructions(std::optional<QString> newInstructions);

    /*!
     */
    [[nodiscard]] QString protocolVersion() const;
    /*!
     */
    void setProtocolVersion(const QString &newProtocolVersion);

    /*!
     */
    [[nodiscard]] McpProtocolImplementation serverInfo() const;
    /*!
     */
    void setServerInfo(const McpProtocolImplementation &newServerInfo);

private:
    std::optional<McpProtocolMeta> mMeta;
    // TODO McpProtocolServerCapabilities mCapabilities;
    std::optional<QString> mInstructions;
    QString mProtocolVersion;
    McpProtocolImplementation mServerInfo;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeResult &t);
