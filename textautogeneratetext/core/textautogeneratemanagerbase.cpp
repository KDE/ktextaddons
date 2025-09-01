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

TextAutoGenerateReply *TextAutoGenerateManagerBase::getCompletion([[maybe_unused]] const TextAutoGenerateTextRequest &request)
{
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
