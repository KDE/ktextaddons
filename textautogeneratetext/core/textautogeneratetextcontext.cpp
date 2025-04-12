/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextcontext.h"

#include <QJsonArray>

using namespace TextAutogenerateText;
TextAutogenerateTextContext::TextAutogenerateTextContext() = default;

TextAutogenerateTextContext::~TextAutogenerateTextContext() = default;

QVariant TextAutogenerateTextContext::contextData() const
{
    return mContextData;
}

void TextAutogenerateTextContext::setContextData(const QVariant &newContextData)
{
    mContextData = newContextData;
}

bool TextAutogenerateTextContext::operator==(const TextAutogenerateTextContext &other) const
{
    return other.contextData() == mContextData;
}

QJsonValue TextAutogenerateTextContext::toJson() const
{
    return mContextData.value<QJsonArray>();
}

QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutogenerateTextContext &t)
{
    d.space() << "contextData:" << t.contextData();
    return d;
}
