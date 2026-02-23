/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratepowersavermessagewidget.h"
#include <KLocalizedString>

using namespace TextAutoGenerateText;
TextAutoGeneratePowerSaverMessageWidget::TextAutoGeneratePowerSaverMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setMessageType(KMessageWidget::MessageType::Warning);
    setPosition(KMessageWidget::Header);
    setText(i18n("Power saver mode is enabled, this will slow down message generation."));
    setVisible(false);
}

TextAutoGeneratePowerSaverMessageWidget::~TextAutoGeneratePowerSaverMessageWidget() = default;

#include "moc_textautogeneratepowersavermessagewidget.cpp"
