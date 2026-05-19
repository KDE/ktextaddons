/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratenotworkingmessagewidget.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateNotWorkingMessageWidget::TextAutoGenerateNotWorkingMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setCloseButtonVisible(false);
    setMessageType(KMessageWidget::MessageType::Error);
    setPosition(KMessageWidget::Header);
}

TextAutoGenerateNotWorkingMessageWidget::~TextAutoGenerateNotWorkingMessageWidget() = default;

void TextAutoGenerateNotWorkingMessageWidget::setMessageInfo(const QString &errorMessage)
{
    setText(errorMessage);
}

#include "moc_textautogeneratenotworkingmessagewidget.cpp"
