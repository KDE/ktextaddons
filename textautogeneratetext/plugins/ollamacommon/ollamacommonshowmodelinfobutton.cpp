/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonshowmodelinfobutton.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaCommonShowModelInfoButton::OllamaCommonShowModelInfoButton(QWidget *parent)
    : QToolButton(parent)
{
    setIcon(QIcon::fromTheme(u"documentinfo"_s));
    setToolTip(i18nc("@info:tooltip", "Show Model Info"));
    connect(this, &QToolButton::clicked, this, &OllamaCommonShowModelInfoButton::showModelInfoRequested);
}

OllamaCommonShowModelInfoButton::~OllamaCommonShowModelInfoButton() = default;

#include "moc_ollamacommonshowmodelinfobutton.cpp"
