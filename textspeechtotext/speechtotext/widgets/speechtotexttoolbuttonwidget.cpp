/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotexttoolbuttonwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "textspeechtotext/speechtotextmanager.h"
#include <QHBoxLayout>
#include <QToolButton>

using namespace TextSpeechToText;
SpeechToTextToolButtonWidget::SpeechToTextToolButtonWidget(QWidget *parent)
    : QWidget{parent}
    , mToolButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mToolButton->setObjectName(u"mToolButton"_s);
    mainLayout->addWidget(mToolButton);
    connect(mToolButton, &QToolButton::clicked, this, &SpeechToTextToolButtonWidget::slotButtonClicked);
}

SpeechToTextToolButtonWidget::~SpeechToTextToolButtonWidget() = default;

void SpeechToTextToolButtonWidget::slotButtonClicked()
{
    SpeechToTextManager::self()->speechToText();
}

#include "moc_speechtotexttoolbuttonwidget.cpp"
