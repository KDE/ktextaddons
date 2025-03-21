/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaconfiguredialog.h"
#include "ollamaconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

OllamaConfigureDialog::OllamaConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mOllamaConfigureWidget(new OllamaConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Ollama"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mOllamaConfigureWidget->setObjectName(QStringLiteral("mOllamaConfigureWidget"));
    mainLayout->addWidget(mOllamaConfigureWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &OllamaConfigureDialog::slotAccepted);
    connect(box, &QDialogButtonBox::rejected, this, &OllamaConfigureDialog::reject);
}

OllamaConfigureDialog::~OllamaConfigureDialog() = default;

void OllamaConfigureDialog::slotAccepted()
{
    mOllamaConfigureWidget->saveSettings();
    accept();
}

#include "moc_ollamaconfiguredialog.cpp"
