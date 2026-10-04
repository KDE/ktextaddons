/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpstreamablehttpserverheaderconfiguredialog.h"
#include "server/addmcpstreamablehttpserverheaderconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

namespace
{
const char myAddMcpStreamableHttpServerHeaderConfigureDialogGroupName[] = "AddMcpStreamableHttpServerHeaderConfigureDialog";
}
using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
AddMcpStreamableHttpServerHeaderConfigureDialog::AddMcpStreamableHttpServerHeaderConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mAddMcpStreamableHttpServerHeaderConfigureWidget(new AddMcpStreamableHttpServerHeaderConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Custom Header"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mAddMcpStreamableHttpServerHeaderConfigureWidget->setObjectName(u"mAddMcpStreamableHttpServerHeaderConfigureWidget"_s);
    mainLayout->addWidget(mAddMcpStreamableHttpServerHeaderConfigureWidget);
    auto button = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    auto buttonOk = button->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(button, &QDialogButtonBox::rejected, this, &AddMcpStreamableHttpServerHeaderConfigureDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &AddMcpStreamableHttpServerHeaderConfigureDialog::accept);
    connect(mAddMcpStreamableHttpServerHeaderConfigureWidget, &AddMcpStreamableHttpServerHeaderConfigureWidget::buttonOkEnabled, this, [buttonOk](bool state) {
        buttonOk->setEnabled(state);
    });
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this,
                                                             QLatin1StringView(myAddMcpStreamableHttpServerHeaderConfigureDialogGroupName),
                                                             QSize(400, 200));
}

AddMcpStreamableHttpServerHeaderConfigureDialog::~AddMcpStreamableHttpServerHeaderConfigureDialog() = default;

void AddMcpStreamableHttpServerHeaderConfigureDialog::setHeader(const QString &str)
{
    // Used to modify an existing header
    setWindowTitle(i18nc("@title:window", "Modify Custom Header"));
    mAddMcpStreamableHttpServerHeaderConfigureWidget->setHeader(str);
}

QString AddMcpStreamableHttpServerHeaderConfigureDialog::header() const
{
    return mAddMcpStreamableHttpServerHeaderConfigureWidget->header();
}

#include "moc_addmcpstreamablehttpserverheaderconfiguredialog.cpp"
