/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextclient.h"
using namespace TextAutogenerateText;
TextAutogenerateTextClient::TextAutogenerateTextClient(QObject *parent)
    : QObject{parent}
{
}

TextAutogenerateTextClient::~TextAutogenerateTextClient() = default;

bool TextAutogenerateTextClient::hasConfigurationDialog() const
{
    return false;
}

bool TextAutogenerateTextClient::showConfigureDialog(QWidget *parentWidget)
{
    Q_UNUSED(parentWidget);
    // Nothing by default
    return false;
}

#include "moc_textautogeneratetextclient.cpp"
