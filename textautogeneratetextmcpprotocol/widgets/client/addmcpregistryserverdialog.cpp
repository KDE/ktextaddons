/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpregistryserverdialog.h"
#include "addmcpregistryserverwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerInfo>

namespace
{
const char myAddMcpRegistryServerDialogGroupName[] = "AddMcpRegistryServerDialog";
}
using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
AddMcpRegistryServerDialog::AddMcpRegistryServerDialog(QWidget *parent)
    : QDialog(parent)
    , mAddMcpRegistryServerWidget(new AddMcpRegistryServerWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Server from MCP Registry"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mAddMcpRegistryServerWidget->setObjectName(u"mAddMcpRegistryServerWidget"_s);
    mainLayout->addWidget(mAddMcpRegistryServerWidget);
    auto button = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    auto buttonOk = button->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(button, &QDialogButtonBox::rejected, this, &AddMcpRegistryServerDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &AddMcpRegistryServerDialog::accept);
    connect(mAddMcpRegistryServerWidget,
            &AddMcpRegistryServerWidget::currentServerChanged,
            this,
            [buttonOk](const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &info) {
                buttonOk->setEnabled(info.isValid());
            });
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myAddMcpRegistryServerDialogGroupName), QSize(800, 500));
}

AddMcpRegistryServerDialog::~AddMcpRegistryServerDialog() = default;

TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo AddMcpRegistryServerDialog::serverInfo() const
{
    return mAddMcpRegistryServerWidget->currentServerInfo();
}

#include "moc_addmcpregistryserverdialog.cpp"
