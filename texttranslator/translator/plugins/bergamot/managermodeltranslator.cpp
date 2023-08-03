/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "managermodeltranslator.h"

ManagerModelTranslator::ManagerModelTranslator(QObject *parent)
    : QObject{parent}
{
}

ManagerModelTranslator::~ManagerModelTranslator() = default;

#include "moc_managermodeltranslator.cpp"
