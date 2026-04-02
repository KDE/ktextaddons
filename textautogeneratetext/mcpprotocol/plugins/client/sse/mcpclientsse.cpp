/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientsse.h"

McpClientSse::McpClientSse(QObject *parent)
    : QObject{parent}
{
}

McpClientSse::~McpClientSse() = default;

#include "moc_mcpclientsse.cpp"
