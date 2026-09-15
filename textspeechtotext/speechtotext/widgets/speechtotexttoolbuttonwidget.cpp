/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotexttoolbuttonwidget.h"

#include "textspeechtotext/speechtotextmanager.h"
#include <QHBoxLayout>
#include <QToolButton>

using namespace Qt::Literals::StringLiterals;
using namespace TextSpeechToText;
SpeechToTextToolButtonWidget::SpeechToTextToolButtonWidget(QWidget *parent)
    : QWidget{parent}
    , mToolButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mToolButton->setObjectName(u"mToolButton"_s);
    mToolButton->setCheckable(true);
    mainLayout->addWidget(mToolButton);
    connect(mToolButton, &QToolButton::clicked, this, &SpeechToTextToolButtonWidget::slotButtonClicked);
    connect(SpeechToTextManager::self(), &SpeechToTextManager::recordingChanged, this, [this](bool recording) {
        mToolButton->setChecked(recording);
        updateIcon();
    });
    updateIcon();
}

SpeechToTextToolButtonWidget::~SpeechToTextToolButtonWidget() = default;

void SpeechToTextToolButtonWidget::updateIcon()
{
    mToolButton->setIcon(mToolButton->isChecked() ? QIcon::fromTheme(u"mic-on"_s) : QIcon::fromTheme(u"mic-off"_s));
}

void SpeechToTextToolButtonWidget::slotButtonClicked()
{
    if (SpeechToTextManager::self()->isRecording()) {
        SpeechToTextManager::self()->stop();
    } else {
        SpeechToTextManager::self()->speechToText();
    }
    // Starting can fail (no engine, no microphone): keep the button in sync with reality.
    mToolButton->setChecked(SpeechToTextManager::self()->isRecording());
    updateIcon();
}

#include "moc_speechtotexttoolbuttonwidget.cpp"
