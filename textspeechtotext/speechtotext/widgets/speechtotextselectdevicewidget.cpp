/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextselectdevicewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QAudioDevice>
#include <QMediaDevices>

#include <QComboBox>
#include <QHBoxLayout>

using namespace TextSpeechToText;
namespace
{
const char mySoundGroupName[] = "Message Sound";
}
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

void SpeechToTextSelectDeviceWidget::loadSettings()
{
    KConfigGroup group(KSharedConfig::openConfig(), mySoundGroupName);
    // TODO
}

void SpeechToTextSelectDeviceWidget::saveSettings()
{
    KConfigGroup group(KSharedConfig::openConfig(), mySoundGroupName);
    // TODO
}

void SpeechToTextSelectDeviceWidget::initializeInput()
{
    mDeviceComboBox->addItem(i18n("Default"), QVariant(QString()));
    for (const auto &device : QMediaDevices::audioInputs()) {
        const auto name = device.description();
        mDeviceComboBox->addItem(name, QVariant::fromValue(device));
    }
}

#include "moc_speechtotextselectdevicewidget.cpp"
