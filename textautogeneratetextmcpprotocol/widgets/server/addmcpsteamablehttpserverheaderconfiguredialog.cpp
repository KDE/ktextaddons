/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpsteamablehttpserverheaderconfiguredialog.h"
#include "server/addmcpsteamablehttpserverheaderconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
AddMcpSteamableHttpServerHeaderConfigureDialog::AddMcpSteamableHttpServerHeaderConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mAddMcpSteamableHttpServerHeaderConfigureWidget(new AddMcpSteamableHttpServerHeaderConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Custom Header"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mAddMcpSteamableHttpServerHeaderConfigureWidget->setObjectName(u"mAddMcpSteamableHttpServerHeaderConfigureWidget"_s);
    mainLayout->addWidget(mAddMcpSteamableHttpServerHeaderConfigureWidget);
    auto button = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    auto buttonOk = button->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(button, &QDialogButtonBox::rejected, this, &AddMcpSteamableHttpServerHeaderConfigureDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &AddMcpSteamableHttpServerHeaderConfigureDialog::accept);
    // TODO connect(mAddMcpServerWidget, &AddMcpServerWidget::buttonOkEnabled, this, [buttonOk](bool state) {
    // TODO buttonOk->setEnabled(state);
    // TODO });
}

AddMcpSteamableHttpServerHeaderConfigureDialog::~AddMcpSteamableHttpServerHeaderConfigureDialog() = default;

void AddMcpSteamableHttpServerHeaderConfigureDialog::setHeader(const QString &str)
{
    mAddMcpSteamableHttpServerHeaderConfigureWidget->setHeader(str);
}

QString AddMcpSteamableHttpServerHeaderConfigureDialog::header() const
{
    return mAddMcpSteamableHttpServerHeaderConfigureWidget->header();
}

#include "moc_addmcpsteamablehttpserverheaderconfiguredialog.cpp"
