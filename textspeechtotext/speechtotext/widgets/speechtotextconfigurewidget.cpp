/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextconfigurewidget.h"

#include "speechtotext/widgets/speechtotextlanguagecomboboxwidget.h"
#include "speechtotextenginecomboboxwidget.h"
#include "speechtotextselectdevicewidget.h"
#include <KLocalizedString>
#include <KSharedConfig>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextSpeechToText;

SpeechToTextConfigureWidget::SpeechToTextConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mSpeechToTextComboBox(new SpeechToTextEngineComboBoxWidget(this))
    , mSpeechToTextDevice(new SpeechToTextSelectDeviceWidget(this))
    , mSpeechToTextLanguage(new SpeechToTextLanguageComboBoxWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mSpeechToTextDevice->setObjectName(u"mSpeechToTextDevice"_s);
    mainLayout->addWidget(mSpeechToTextDevice);

    mSpeechToTextComboBox->setObjectName(u"mSpeechToTextComboBox"_s);
    mainLayout->addWidget(mSpeechToTextComboBox);

    mSpeechToTextLanguage->setObjectName(u"mSpeechToTextLanguage"_s);
    mainLayout->addWidget(mSpeechToTextLanguage);

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
