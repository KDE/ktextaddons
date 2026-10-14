/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolicon.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>

#include <QJsonArray>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolIcon::McpProtocolIcon() = default;

bool McpProtocolIcon::operator==(const McpProtocolIcon &other) const = default;

std::optional<QString> McpProtocolIcon::mimeType() const
{
    return mMimeType;
}

void McpProtocolIcon::setMimeType(std::optional<QString> newMimeType)
{
    mMimeType = std::move(newMimeType);
}

std::optional<QStringList> McpProtocolIcon::sizes() const
{
    return mSizes;
}

void McpProtocolIcon::setSizes(std::optional<QStringList> newSizes)
{
    mSizes = std::move(newSizes);
}

std::optional<QString> McpProtocolIcon::theme() const
{
    return mTheme;
}

void McpProtocolIcon::setTheme(std::optional<QString> newTheme)
{
    mTheme = std::move(newTheme);
}

QString McpProtocolIcon::src() const
{
    return mSrc;
}

void McpProtocolIcon::setSrc(const QString &newSrc)
{
    mSrc = newSrc;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolIcon &t)
{
    d.space() << "src:" << t.src();
    d.space() << "sizes:" << t.sizes();
    d.space() << "mimeType:" << t.mimeType();
    d.space() << "theme:" << t.theme();
    return d;
}

bool McpProtocolIcon::isValid() const
{
    return !mSrc.isEmpty();
}

McpProtocolIcon McpProtocolIcon::fromJson(const QJsonObject &obj)
{
    McpProtocolIcon icon;
    if (const QJsonValue srcValue = obj.value("src"_L1); srcValue.isString()) {
        icon.setSrc(srcValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolIcon: missing required field 'src'";
        return {};
    }
    if (obj.contains("mimeType"_L1)) {
        icon.setMimeType(obj.value("mimeType"_L1).toString());
    }
    if (const QJsonValue sizesValue = obj.value("sizes"_L1); sizesValue.isArray()) {
        const QJsonArray arr = sizesValue.toArray();
        QStringList list_sizes;
        list_sizes.reserve(arr.count());
        for (const auto &v : arr) {
            list_sizes.append(v.toString());
        }
        icon.setSizes(std::move(list_sizes));
    }
    if (const QJsonValue themeValue = obj.value("theme"_L1); themeValue.isString()) {
        // Optional enum: "light" or "dark", ignore unknown values
        if (const QString theme = themeValue.toString(); theme == "light"_L1 || theme == "dark"_L1) {
            icon.setTheme(theme);
        }
    }
    return icon;
}

QJsonObject McpProtocolIcon::toJson(const McpProtocolIcon &icon)
{
    QJsonObject obj;
    obj["src"_L1] = icon.src();

    if (icon.mimeType().has_value()) {
        obj["mimeType"_L1] = *icon.mimeType();
    }
    if (icon.theme().has_value()) {
        obj["theme"_L1] = *icon.theme();
    }
    if (icon.sizes().has_value()) {
        QJsonArray sizes;
        const QStringList lst = *icon.sizes();
        for (const auto &t : lst) {
            sizes.append(t);
        }
        obj["sizes"_L1] = sizes;
    }
    return obj;
}
