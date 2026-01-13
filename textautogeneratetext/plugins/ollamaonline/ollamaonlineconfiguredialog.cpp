/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaonlineconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;
OllamaOnlineConfigureDialog::OllamaOnlineConfigureDialog(QWidget *parent)
    : KPageDialog(parent)
{
}

OllamaOnlineConfigureDialog::~OllamaOnlineConfigureDialog() = default;

#include "moc_ollamaonlineconfiguredialog.cpp"
