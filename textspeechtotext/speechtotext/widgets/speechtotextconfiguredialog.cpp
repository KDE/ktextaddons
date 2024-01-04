/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextconfiguredialog.h"
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
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mSpeechToTextConfigureWidget->setObjectName(QStringLiteral("mSpeechToTextConfigureWidget"));
    mainLayout->addWidget(mSpeechToTextConfigureWidget);
    mainLayout->addStretch();

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
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
