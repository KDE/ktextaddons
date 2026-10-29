/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoldiscoverresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolDiscoverResult::McpProtocolDiscoverResult() = default;

bool McpProtocolDiscoverResult::operator==(const McpProtocolDiscoverResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolDiscoverResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "supportedVersions:" << t.supportedVersions();
    d.space() << "capabilities:" << t.capabilities();
    d.space() << "instructions:" << t.instructions();
    d.space() << "ttlMs:" << t.ttlMs();
    d.space() << "cacheScope:" << McpProtocolUtils::convertCacheScopeToString(t.cacheScope());
    return d;
}

McpProtocolDiscoverResult McpProtocolDiscoverResult::fromJson(const QJsonObject &obj)
{
    McpProtocolDiscoverResult result;
    if (const QJsonValue supportedVersionsValue = obj.value("supportedVersions"_L1); supportedVersionsValue.isArray()) {
        QStringList supportedVersions;
        const QJsonArray supportedVersionsArray = supportedVersionsValue.toArray();
        for (const QJsonValue &version : supportedVersionsArray) {
            if (!version.isString()) {
                qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolDiscoverResult: invalid field 'supportedVersions'";
                return {};
            }
            supportedVersions.append(version.toString());
        }
        result.setSupportedVersions(supportedVersions);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolDiscoverResult: missing required field 'supportedVersions'";
        return {};
    }
    if (const QJsonValue capabilitiesValue = obj.value("capabilities"_L1); capabilitiesValue.isObject()) {
        result.setCapabilities(McpProtocolServerCapabilities::fromJson(capabilitiesValue.toObject()));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolDiscoverResult: missing required field 'capabilities'";
        return {};
    }
    if (const QJsonValue ttlMsValue = obj.value("ttlMs"_L1); ttlMsValue.isDouble() && ttlMsValue.toDouble() >= 0) {
        result.setTtlMs(ttlMsValue.toInteger());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolDiscoverResult: missing or invalid required field 'ttlMs'";
        return {};
    }
    if (const QJsonValue cacheScopeValue = obj.value("cacheScope"_L1); cacheScopeValue.isString()) {
        const McpProtocolUtils::CacheScope cacheScope = McpProtocolUtils::convertCacheScopeFromString(cacheScopeValue.toString());
        if (cacheScope == McpProtocolUtils::CacheScope::Unknown) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolDiscoverResult: invalid field 'cacheScope'" << cacheScopeValue.toString();
            return {};
        }
        result.setCacheScope(cacheScope);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolDiscoverResult: missing required field 'cacheScope'";
        return {};
    }
    if (const QJsonValue instructionsValue = obj.value("instructions"_L1); instructionsValue.isString()) {
        result.setInstructions(instructionsValue.toString());
    }
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    return result;
}

QJsonObject McpProtocolDiscoverResult::toJson(const McpProtocolDiscoverResult &result)
{
    QJsonObject obj;
    obj["supportedVersions"_L1] = QJsonArray::fromStringList(result.supportedVersions());
    obj["capabilities"_L1] = McpProtocolServerCapabilities::toJson(result.capabilities());
    obj["ttlMs"_L1] = result.ttlMs();
    if (result.cacheScope() != McpProtocolUtils::CacheScope::Unknown) {
        obj["cacheScope"_L1] = McpProtocolUtils::convertCacheScopeToString(result.cacheScope());
    }
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    if (result.instructions().has_value()) {
        obj["instructions"_L1] = *result.instructions();
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolDiscoverResult::meta() const
{
    return mMeta;
}

void McpProtocolDiscoverResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QStringList McpProtocolDiscoverResult::supportedVersions() const
{
    return mSupportedVersions;
}

void McpProtocolDiscoverResult::setSupportedVersions(const QStringList &newSupportedVersions)
{
    mSupportedVersions = newSupportedVersions;
}

McpProtocolServerCapabilities McpProtocolDiscoverResult::capabilities() const
{
    return mCapabilities;
}

void McpProtocolDiscoverResult::setCapabilities(McpProtocolServerCapabilities newCapabilities)
{
    mCapabilities = std::move(newCapabilities);
}

std::optional<QString> McpProtocolDiscoverResult::instructions() const
{
    return mInstructions;
}

void McpProtocolDiscoverResult::setInstructions(std::optional<QString> newInstructions)
{
    mInstructions = std::move(newInstructions);
}

qint64 McpProtocolDiscoverResult::ttlMs() const
{
    return mTtlMs;
}

void McpProtocolDiscoverResult::setTtlMs(qint64 newTtlMs)
{
    mTtlMs = newTtlMs;
}

McpProtocolUtils::CacheScope McpProtocolDiscoverResult::cacheScope() const
{
    return mCacheScope;
}

void McpProtocolDiscoverResult::setCacheScope(McpProtocolUtils::CacheScope newCacheScope)
{
    mCacheScope = newCacheScope;
}
