/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "speechtotextconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace TextSpeechToText;
SpeechToTextConfigureDialog::SpeechToTextConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mSpeechToTextConfigureWidget(new SpeechToTextConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Speech To Text"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mSpeechToTextConfigureWidget->setObjectName(u"mSpeechToTextConfigureWidget"_s);
    mainLayout->addWidget(mSpeechToTextConfigureWidget);
    mainLayout->addStretch();

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &SpeechToTextConfigureDialog::slotAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SpeechToTextConfigureDialog::reject);
    mSpeechToTextConfigureWidget->loadSettings();
}

SpeechToTextConfigureDialog::~SpeechToTextConfigureDialog() = default;

void SpeechToTextConfigureDialog::slotAccept()
{
    mSpeechToTextConfigureWidget->saveSettings();
    accept();
}

#include "moc_speechtotextconfiguredialog.cpp"
