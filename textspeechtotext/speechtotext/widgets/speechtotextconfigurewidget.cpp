/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextconfigurewidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
using namespace TextSpeechToText;

SpeechToTextConfigureWidget::SpeechToTextConfigureWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
}

SpeechToTextConfigureWidget::~SpeechToTextConfigureWidget() = default;

void SpeechToTextConfigureWidget::loadSettings()
{
    // TODO
}

void SpeechToTextConfigureWidget::saveSettings()
{
    // TODO
}

#include "moc_speechtotextconfigurewidget.cpp"
