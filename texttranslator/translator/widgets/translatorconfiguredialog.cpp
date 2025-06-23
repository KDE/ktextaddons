/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "translatorconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace TextTranslator;
TranslatorConfigureDialog::TranslatorConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mTranslatorConfigureWidget(new TranslatorConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Translator"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTranslatorConfigureWidget->setObjectName(u"mTranslatorConfigureWidget"_s);
    mainLayout->addWidget(mTranslatorConfigureWidget);
    mainLayout->addStretch();

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &TranslatorConfigureDialog::slotAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &TranslatorConfigureDialog::reject);
    mTranslatorConfigureWidget->loadSettings();
}

TranslatorConfigureDialog::~TranslatorConfigureDialog() = default;

void TranslatorConfigureDialog::slotAccept()
{
    mTranslatorConfigureWidget->saveSettings();
    accept();
}
