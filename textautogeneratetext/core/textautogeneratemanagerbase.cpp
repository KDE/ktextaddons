/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanagerbase.h"

using namespace TextAutoGenerateText;
TextAutoGenerateManagerBase::TextAutoGenerateManagerBase(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateReply *TextAutoGenerateManagerBase::getCompletion(const TextAutoGenerateTextRequest &request)
{
    Q_UNUSED(request)
    return {};
}

TextAutoGenerateManagerBase::~TextAutoGenerateManagerBase() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateManagerBase::ModelsInfo &t)
{
    d.space() << "models:" << t.models;
    d.space() << "hasError:" << t.hasError;
    d.space() << "isReady:" << t.isReady;
    return d;
}

#include "moc_textautogeneratemanagerbase.cpp"
