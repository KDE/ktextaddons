/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateconfiguredialog.h"

#include "textautogenerateconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateConfigureDialog::TextAutoGenerateConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateConfigureWidget(new TextAutoGenerateConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure IA"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mTextAutoGenerateConfigureWidget->setObjectName(QStringLiteral("mTextAutoGenerateConfigureWidget"));
    mainLayout->addWidget(mTextAutoGenerateConfigureWidget);

    mainLayout->addStretch(1);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(QStringLiteral("button"));
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateConfigureDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateConfigureDialog::accept);

    mTextAutoGenerateConfigureWidget->loadSettings();
}

TextAutoGenerateConfigureDialog::~TextAutoGenerateConfigureDialog() = default;

void TextAutoGenerateConfigureDialog::saveSettings()
{
    mTextAutoGenerateConfigureWidget->saveSettings();
}

#include "moc_textautogenerateconfiguredialog.cpp"
