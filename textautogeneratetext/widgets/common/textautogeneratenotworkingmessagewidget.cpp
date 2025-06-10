/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratenotworkingmessagewidget.h"
#include <KLocalizedString>

using namespace TextAutoGenerateText;
TextAutoGenerateNotWorkingMessageWidget::TextAutoGenerateNotWorkingMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setCloseButtonVisible(false);
    setMessageType(KMessageWidget::MessageType::Error);
    setPosition(KMessageWidget::Header);

    auto startOllamaAction = new QAction(i18nc("@action", "Start Ollama"), this);
    startOllamaAction->setObjectName(QStringLiteral("decodeEncryptionKeyAction"));
    connect(startOllamaAction, &QAction::triggered, this, &TextAutoGenerateNotWorkingMessageWidget::startOllama);
    addAction(startOllamaAction);
}

TextAutoGenerateNotWorkingMessageWidget::~TextAutoGenerateNotWorkingMessageWidget() = default;

#include "moc_textautogeneratenotworkingmessagewidget.cpp"
