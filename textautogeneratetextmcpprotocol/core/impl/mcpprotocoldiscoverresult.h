/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <QStringList>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerCapabilities>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolDiscoverResult
{
public:
    /*!
     */
    McpProtocolDiscoverResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolDiscoverResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolDiscoverResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolDiscoverResult &result);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] QStringList supportedVersions() const;
    /*!
     */
    void setSupportedVersions(const QStringList &newSupportedVersions);

    /*!
     */
    [[nodiscard]] McpProtocolServerCapabilities capabilities() const;
    /*!
     */
    void setCapabilities(McpProtocolServerCapabilities newCapabilities);

    /*!
     */
    [[nodiscard]] std::optional<QString> instructions() const;
    /*!
     */
    void setInstructions(std::optional<QString> newInstructions);

    /*!
     */
    [[nodiscard]] qint64 ttlMs() const;
    /*!
     */
    void setTtlMs(qint64 newTtlMs);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::CacheScope cacheScope() const;
    /*!
     */
    void setCacheScope(McpProtocolUtils::CacheScope newCacheScope);

private:
    std::optional<McpProtocolMeta> mMeta;
    QStringList mSupportedVersions;
    McpProtocolServerCapabilities mCapabilities;
    std::optional<QString> mInstructions;
    qint64 mTtlMs = 0;
    McpProtocolUtils::CacheScope mCacheScope = McpProtocolUtils::CacheScope::Unknown;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolDiscoverResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolDiscoverResult &t);
