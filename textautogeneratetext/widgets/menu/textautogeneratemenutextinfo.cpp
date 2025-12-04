/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemenutextinfo.h"
#include <QDebug>
using namespace TextAutoGenerateText;
TextAutoGenerateMenuTextInfo::TextAutoGenerateMenuTextInfo() = default;

TextAutoGenerateMenuTextInfo::~TextAutoGenerateMenuTextInfo() = default;

bool TextAutoGenerateMenuTextInfo::enabled() const
{
    return mEnabled;
}

void TextAutoGenerateMenuTextInfo::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

QString TextAutoGenerateMenuTextInfo::requestText() const
{
    return mRequestText;
}

void TextAutoGenerateMenuTextInfo::setRequestText(const QString &newRequestText)
{
    mRequestText = newRequestText;
}

bool TextAutoGenerateMenuTextInfo::operator==(const TextAutoGenerateMenuTextInfo &other) const
{
    return mEnabled == other.mEnabled && mRequestText == other.mRequestText;
}

QDebug operator<<(QDebug d, const TextAutoGenerateMenuTextInfo &t)
{
    d.space() << "enabled:" << t.enabled();
    d.space() << "requestText:" << t.requestText();
    return d;
}
