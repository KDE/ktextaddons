/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextselectdevicewidget.h"
#include <KLocalizedString>
#include <QComboBox>
#include <QHBoxLayout>

using namespace TextSpeechToText;
SpeechToTextSelectDeviceWidget::SpeechToTextSelectDeviceWidget(QWidget *parent)
    : QWidget{parent}
    , mDeviceComboBox(new QComboBox(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mDeviceComboBox->setObjectName(QStringLiteral("mDeviceComboBox"));
    mainLayout->addWidget(mDeviceComboBox);
}

SpeechToTextSelectDeviceWidget::~SpeechToTextSelectDeviceWidget() = default;

#include "moc_speechtotextselectdevicewidget.cpp"
