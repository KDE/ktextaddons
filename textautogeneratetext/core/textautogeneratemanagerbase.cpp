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

TextAutoGenerateManagerBase::~TextAutoGenerateManagerBase() = default;

#include "moc_textautogeneratemanagerbase.cpp"
