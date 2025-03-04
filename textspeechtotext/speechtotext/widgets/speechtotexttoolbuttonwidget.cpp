/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotexttoolbuttonwidget.h"
#include "textspeechtotext/speechtotextmanager.h"
#include <QHBoxLayout>
#include <QToolButton>

using namespace TextSpeechToText;
SpeechToTextToolButtonWidget::SpeechToTextToolButtonWidget(QWidget *parent)
    : QWidget{parent}
    , mToolButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mToolButton->setObjectName(QStringLiteral("mToolButton"));
    mainLayout->addWidget(mToolButton);
    connect(mToolButton, &QToolButton::clicked, this, &SpeechToTextToolButtonWidget::slotButtonClicked);
}

SpeechToTextToolButtonWidget::~SpeechToTextToolButtonWidget() = default;

void SpeechToTextToolButtonWidget::slotButtonClicked()
{
    SpeechToTextManager::self()->speechToText();
}

#include "moc_speechtotexttoolbuttonwidget.cpp"
