/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextconfigurewidget.h"
#include "speechtotextcomboboxwidget.h"
#include "speechtotextselectdevicewidget.h"
#include <KLocalizedString>
#include <KSharedConfig>
#include <QVBoxLayout>

using namespace TextSpeechToText;

SpeechToTextConfigureWidget::SpeechToTextConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mSpeechToTextComboBox(new SpeechToTextComboBoxWidget(this))
    , mSpeechToTextDevice(new SpeechToTextSelectDeviceWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mSpeechToTextDevice->setObjectName(QStringLiteral("mSpeechToTextDevice"));
    mainLayout->addWidget(mSpeechToTextDevice);

    mSpeechToTextComboBox->setObjectName(QStringLiteral("mSpeechToTextComboBox"));
    mainLayout->addWidget(mSpeechToTextComboBox);
    mSpeechToTextComboBox->fillEngine();
}

SpeechToTextConfigureWidget::~SpeechToTextConfigureWidget() = default;

void SpeechToTextConfigureWidget::loadSettings()
{
    mSpeechToTextComboBox->load();
    mSpeechToTextDevice->loadSettings();
}

void SpeechToTextConfigureWidget::saveSettings()
{
    mSpeechToTextComboBox->save();
    mSpeechToTextDevice->saveSettings();
}

#include "moc_speechtotextconfigurewidget.cpp"
