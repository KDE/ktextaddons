/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistrootsresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListRootsResult::McpProtocolListRootsResult() = default;

bool McpProtocolListRootsResult::operator==(const McpProtocolListRootsResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListRootsResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "roots:" << t.roots();
    return d;
}

McpProtocolListRootsResult McpProtocolListRootsResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListRootsResult prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue rootsValue = obj.value("roots"_L1); rootsValue.isArray()) {
        const QJsonArray arr = rootsValue.toArray();
        QList<McpProtocolRoot> roots;
        roots.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            roots.append(McpProtocolRoot::fromJson(v.toObject()));
        }
        prompt.setRoots(roots);
    }
    return prompt;
}

QJsonObject McpProtocolListRootsResult::toJson(const McpProtocolListRootsResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    QJsonArray arr_roots;
    for (const auto &v : boolean.roots()) {
        arr_roots.append(McpProtocolRoot::toJson(v));
    }
    obj.insert("roots"_L1, arr_roots);
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolListRootsResult::meta() const
{
    return mMeta;
}

void McpProtocolListRootsResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QList<McpProtocolRoot> McpProtocolListRootsResult::roots() const
{
    return mRoots;
}

void McpProtocolListRootsResult::setRoots(const QList<McpProtocolRoot> &newRoots)
{
    mRoots = newRoots;
}
