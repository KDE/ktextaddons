/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotmarianinterface.h"

BergamotMarianInterface::BergamotMarianInterface(QObject *parent)
    : QObject{parent}
{
}

BergamotMarianInterface::~BergamotMarianInterface() = default;

void BergamotMarianInterface::translate(const QString &str)
{
    // TODO
}

#include "moc_bergamotmarianinterface.cpp"
