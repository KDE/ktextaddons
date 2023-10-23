/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextmenu.h"
#include <KLocalizedString>
#include <QMenu>

using namespace TextSpeechToText;
SpeechToTextMenu::SpeechToTextMenu(QObject *parent)
    : QObject{parent}
    , mMenu(new QMenu)
{
    mMenu->setObjectName(QStringLiteral("menu"));
    mMenu->setTitle(i18n("Speech to Text..."));
    mMenu->setIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop-locale")));
    updateMenu();
}

SpeechToTextMenu::~SpeechToTextMenu()
{
    delete mMenu;
}

bool SpeechToTextMenu::isEmpty() const
{
    return mMenu->isEmpty();
}

void SpeechToTextMenu::updateMenu()
{
    mMenu->clear();
    // TODO
}

QMenu *SpeechToTextMenu::menu() const
{
    return mMenu;
}

#include "moc_speechtotextmenu.cpp"
