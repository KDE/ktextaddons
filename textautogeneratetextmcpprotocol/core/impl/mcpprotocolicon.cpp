/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolicon.h"
#include <QDebug>
#include <QJsonObject>

#include <QJsonArray>
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

McpProtocolIcon McpProtocolIcon::fromJson(const QJsonObject &obj)
{
    McpProtocolIcon icon;
    icon.setSrc(obj["src"_L1].toString());
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
        icon.setSizes(list_sizes);
    }
    if (const QJsonValue themeValue = obj.value("theme"_L1); themeValue.isString()) {
        icon.setTheme(themeValue.toString());
    }
    return icon;
}

QJsonObject McpProtocolIcon::toJson(const McpProtocolIcon &image)
{
    QJsonObject obj;
    obj["src"_L1] = image.src();

    if (image.mimeType().has_value()) {
        obj["mimeType"_L1] = *image.mimeType();
    }
    if (image.theme().has_value()) {
        obj["theme"_L1] = *image.theme();
    }
    if (image.sizes().has_value()) {
        QJsonArray sizes;
        const QStringList lst = *image.sizes();
        for (const auto &t : lst) {
            sizes.append(t);
        }
        obj["sizes"_L1] = sizes;
    }
    return obj;
}
