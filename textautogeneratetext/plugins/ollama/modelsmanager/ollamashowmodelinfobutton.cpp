/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamashowmodelinfobutton.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaShowModelInfoButton::OllamaShowModelInfoButton(QWidget *parent)
    : QToolButton(parent)
{
    // TODO setIcon(QIcon::fromTheme(u"applications-network-symbolic"_s));
    setToolTip(i18nc("@info:tooltip", "Show Model Info"));
    setAutoRaise(true);
    connect(this, &QToolButton::clicked, this, &OllamaShowModelInfoButton::showModelInfoRequested);
}

OllamaShowModelInfoButton::~OllamaShowModelInfoButton() = default;

#include "moc_ollamashowmodelinfobutton.cpp"
