/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextselectdevicewidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>

using namespace TextSpeechToText;
SpeechToTextSelectDeviceWidget::SpeechToTextSelectDeviceWidget(QWidget *parent)
    : QWidget{parent}
{
}

SpeechToTextSelectDeviceWidget::~SpeechToTextSelectDeviceWidget() = default;

#include "moc_speechtotextselectdevicewidget.cpp"
