/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateelicitationdialog.h"
#include "widgets/mcp/textautogenerateelicitationwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateElicitationDialog::TextAutoGenerateElicitationDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateElicitationWidget(new TextAutoGenerateElicitationWidget(this))
{
    // TODO add server name
    setWindowTitle(i18nc("@title:window", "Request from %1"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateElicitationWidget->setObjectName(u"mTextAutoGenerateElicitationWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateElicitationWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->button(QDialogButtonBox::Ok)->setText(i18nc("@action:button", "Accept"));
    button->setObjectName(u"button"_s);
    auto declineButton = new QPushButton(i18nc("@action:button", "Decline"), this);
    declineButton->setObjectName(u"button"_s);
    button->addButton(declineButton, QDialogButtonBox::ActionRole);
    mainLayout->addWidget(button);

    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateElicitationDialog::slotAccepted);
    connect(declineButton, &QPushButton::clicked, this, &TextAutoGenerateElicitationDialog::slotDeclined);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateElicitationDialog::slotRejected);
}

TextAutoGenerateElicitationDialog::~TextAutoGenerateElicitationDialog() = default;

void TextAutoGenerateElicitationDialog::slotAccepted()
{
    // TODO
    accept();
}

void TextAutoGenerateElicitationDialog::slotDeclined()
{
    // TODO
    accept();
}

void TextAutoGenerateElicitationDialog::slotRejected()
{
    // TODO
    reject();
}

#include "moc_textautogenerateelicitationdialog.cpp"
