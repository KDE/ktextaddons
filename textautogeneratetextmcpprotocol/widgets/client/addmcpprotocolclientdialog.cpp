/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpprotocolclientdialog.h"
#include "client/addmcpprotocolclientwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpProtocolClientDialog::AddMcpProtocolClientDialog(QWidget *parent)
    : QDialog(parent)
    , mAddMcpProtocolClientWidget(new AddMcpProtocolClientWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Server Configuration"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mAddMcpProtocolClientWidget->setObjectName(u"mAddMcpProtocolClientWidget"_s);
    mainLayout->addWidget(mAddMcpProtocolClientWidget);
}

AddMcpProtocolClientDialog::~AddMcpProtocolClientDialog() = default;

#include "moc_addmcpprotocolclientdialog.cpp"
