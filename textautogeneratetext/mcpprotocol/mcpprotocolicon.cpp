/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolicon.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolIcon::McpProtocolIcon() = default;

McpProtocolIcon::~McpProtocolIcon() = default;

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

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolIcon &t)
{
    d.space() << "src:" << t.src();
    d.space() << "sizes:" << t.sizes();
    d.space() << "mimeType:" << t.mimeType();
    d.space() << "theme:" << t.theme();
    return d;
}

McpProtocolIcon McpProtocolIcon::fromJson(const QJsonObject &obj)
{
    return {};
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
