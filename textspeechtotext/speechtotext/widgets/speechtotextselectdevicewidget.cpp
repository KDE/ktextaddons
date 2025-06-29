/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextselectdevicewidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QAudioDevice>
#include <QMediaDevices>

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>

using namespace TextSpeechToText;
namespace
{
const char mySoundGroupName[] = "Speech To Text";
}
SpeechToTextSelectDeviceWidget::SpeechToTextSelectDeviceWidget(QWidget *parent)
    : QWidget{parent}
    , mDeviceComboBox(new QComboBox(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18nc("@label:textbox", "Input:"), this);
    label->setObjectName(u"label"_s);
    label->setTextFormat(Qt::PlainText);
    mainLayout->addWidget(label);

    mDeviceComboBox->setObjectName(u"mDeviceComboBox"_s);
    mainLayout->addWidget(mDeviceComboBox);
    initializeInput();
}

SpeechToTextSelectDeviceWidget::~SpeechToTextSelectDeviceWidget() = default;

void SpeechToTextSelectDeviceWidget::loadSettings()
{
    KConfigGroup group(KSharedConfig::openConfig(), QLatin1StringView(mySoundGroupName));
    const QByteArray deviceIdentifier = group.readEntry("SoundDevice", QByteArray());
    if (!deviceIdentifier.isEmpty()) {
        const int nbDevice{mDeviceComboBox->count()};
        for (int i = 0; i < nbDevice; ++i) {
            const QAudioDevice audioDevice = mDeviceComboBox->itemData(i).value<QAudioDevice>();
            if (audioDevice.id() == deviceIdentifier) {
                mDeviceComboBox->setCurrentIndex(i);
                break;
            }
        }
    }
}

void SpeechToTextSelectDeviceWidget::saveSettings()
{
    KConfigGroup group(KSharedConfig::openConfig(), QLatin1StringView(mySoundGroupName));
    const auto device = mDeviceComboBox->itemData(mDeviceComboBox->currentIndex()).value<QAudioDevice>();
    if (!device.isNull()) {
        const QByteArray deviceIdentifier = device.id();
        group.writeEntry("SoundDevice", deviceIdentifier);
    }
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
