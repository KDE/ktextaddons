/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddinstancedialog.h"
#include "textautogenerateaddinstancewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateAddInstanceDialog::TextAutoGenerateAddInstanceDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateAddInstanceWidget(new TextAutoGenerateAddInstanceWidget(manager, this))
{
    setWindowTitle(i18nc("@title:window", "Add Instance"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mTextAutoGenerateAddInstanceWidget->setObjectName(QStringLiteral("mTextAutoGenerateAddInstanceWidget"));
    mainLayout->addWidget(mTextAutoGenerateAddInstanceWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    button->setObjectName(QStringLiteral("button"));
    mainLayout->addWidget(button);
    auto buttonOk = button->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateAddInstanceDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateAddInstanceDialog::accept);
    connect(mTextAutoGenerateAddInstanceWidget, &TextAutoGenerateAddInstanceWidget::buttonOkEnabled, this, [buttonOk](bool state) {
        buttonOk->setEnabled(state);
    });
}

TextAutoGenerateAddInstanceDialog::~TextAutoGenerateAddInstanceDialog() = default;

TextAutoGenerateTextClient::SupportedServer TextAutoGenerateAddInstanceDialog::selectedInstanceType() const
{
    return mTextAutoGenerateAddInstanceWidget->selectedInstanceType();
}

QString TextAutoGenerateAddInstanceDialog::instanceName() const
{
    return mTextAutoGenerateAddInstanceWidget->instanceName();
}

#include "moc_textautogenerateaddinstancedialog.cpp"
