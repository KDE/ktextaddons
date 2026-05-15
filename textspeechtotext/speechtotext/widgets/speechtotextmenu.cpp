/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextmenu.h"

#include <KLocalizedString>
#include <QMenu>

using namespace Qt::Literals::StringLiterals;
using namespace TextSpeechToText;
SpeechToTextMenu::SpeechToTextMenu(QObject *parent)
    : QObject{parent}
    , mMenu(new QMenu)
{
    mMenu->setObjectName(u"menu"_s);
    mMenu->setTitle(i18n("Speech to Text…"));
    mMenu->setIcon(QIcon::fromTheme(u"preferences-desktop-locale"_s));
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
    // TODO update from specific plugins
}

QMenu *SpeechToTextMenu::menu() const
{
    return mMenu;
}

#include "moc_speechtotextmenu.cpp"
