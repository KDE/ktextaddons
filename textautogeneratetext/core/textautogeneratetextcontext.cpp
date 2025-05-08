/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextcontext.h"

#include <QJsonArray>

using namespace TextAutoGenerateText;
TextAutoGenerateTextContext::TextAutoGenerateTextContext() = default;

TextAutoGenerateTextContext::~TextAutoGenerateTextContext() = default;

QVariant TextAutoGenerateTextContext::contextData() const
{
    return mContextData;
}

void TextAutoGenerateTextContext::setContextData(const QVariant &newContextData)
{
    mContextData = newContextData;
}

bool TextAutoGenerateTextContext::operator==(const TextAutoGenerateTextContext &other) const
{
    return other.contextData() == mContextData;
}

QJsonValue TextAutoGenerateTextContext::toJson() const
{
    return mContextData.value<QJsonArray>();
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextContext &t)
{
    d.space() << "contextData:" << t.contextData();
    return d;
}
