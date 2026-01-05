/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamashowmodelinfobutton.h"

using namespace Qt::Literals::StringLiterals;

OllamaShowModelInfoButton::OllamaShowModelInfoButton(QWidget *parent)
    : QToolButton(parent)
{
    // TODO setIcon(QIcon::fromTheme(u"applications-network-symbolic"_s));
    setAutoRaise(true);
    connect(this, &QToolButton::clicked, this, [this]() {
        // TODO
    });
}

OllamaShowModelInfoButton::~OllamaShowModelInfoButton() = default;
