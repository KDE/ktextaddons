/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateconfiguredialog.h"
#include "textautogenerateconfigurewidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace TextAutogenerateText;
TextAutogenerateConfigureDialog::TextAutogenerateConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutogenerateConfigureWidget(new TextAutogenerateConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure IA"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mTextAutogenerateConfigureWidget->setObjectName(QStringLiteral("mTextAutogenerateConfigureWidget"));
    mainLayout->addWidget(mTextAutogenerateConfigureWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(QStringLiteral("button"));
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutogenerateConfigureDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutogenerateConfigureDialog::accept);
}

TextAutogenerateConfigureDialog::~TextAutogenerateConfigureDialog() = default;

#include "moc_textautogenerateconfiguredialog.cpp"
