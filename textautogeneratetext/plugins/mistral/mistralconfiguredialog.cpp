/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralconfiguredialog.h"
#include "mistralconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

MistralConfigureDialog::MistralConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mMistralConfigureWidget(new MistralConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Mistral IA"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &MistralConfigureDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &MistralConfigureDialog::reject);
}

MistralConfigureDialog::~MistralConfigureDialog() = default;

#include "moc_mistralconfiguredialog.cpp"
