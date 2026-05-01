/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpserverdialog.h"
#include "addmcpserverwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
AddMcpServerDialog::AddMcpServerDialog(QWidget *parent)
    : QDialog(parent)
    , mAddMcpServerWidget(new AddMcpServerWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Server"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mAddMcpServerWidget->setObjectName(u"mAddMcpServerWidget"_s);
    mainLayout->addWidget(mAddMcpServerWidget);
    auto button = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    auto buttonOk = button->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(button, &QDialogButtonBox::rejected, this, &AddMcpServerDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &AddMcpServerDialog::accept);
    connect(mAddMcpServerWidget, &AddMcpServerWidget::buttonOkEnabled, this, [buttonOk](bool state) {
        buttonOk->setEnabled(state);
    });
}

AddMcpServerDialog::~AddMcpServerDialog() = default;

void AddMcpServerDialog::setServerWidgetInfo(const AddMcpServerWidget::McpServerWidgetInfo &info)
{
    mAddMcpServerWidget->setServerWidgetInfo(info);
}

AddMcpServerWidget::McpServerWidgetInfo AddMcpServerDialog::serverWidgetInfo() const
{
    return mAddMcpServerWidget->serverWidgetInfo();
}

#include "moc_addmcpserverdialog.cpp"
