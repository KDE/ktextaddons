/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpsteamablehttpserverheaderwidget.h"
#include "addmcpsteamablehttpserverheaderconfiguredialog.h"
#include "addmcpsteamablehttpserverheaderlistwidget.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QListWidget>
#include <QPointer>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpSteamableHttpServerHeaderWidget::AddMcpSteamableHttpServerHeaderWidget(QWidget *parent)
    : QWidget{parent}
    , mListBox(new AddMcpSteamableHttpServerHeaderListWidget(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mListBox->setObjectName(u"mListBox"_s);
    mainLayout->addWidget(mListBox);

    auto buttonsLayout = new QVBoxLayout;
    buttonsLayout->setObjectName(u"buttonsLayout"_s);
    buttonsLayout->setContentsMargins(QMargins{});

    auto addHeaderButton = new QPushButton(i18nc("@action:button", "Add"), this);
    addHeaderButton->setObjectName(u"addHeaderButton"_s);
    buttonsLayout->addWidget(addHeaderButton);
    connect(addHeaderButton, &QPushButton::clicked, this, &AddMcpSteamableHttpServerHeaderWidget::slotAddHeader);

    auto modifyHeaderButton = new QPushButton(i18nc("@action:button", "Modify"), this);
    modifyHeaderButton->setObjectName(u"modifyHeaderButton"_s);
    buttonsLayout->addWidget(modifyHeaderButton);
    connect(modifyHeaderButton, &QPushButton::clicked, this, &AddMcpSteamableHttpServerHeaderWidget::slotModifyHeader);

    auto removeHeaderButton = new QPushButton(i18nc("@action:button", "Remove"), this);
    removeHeaderButton->setObjectName(u"removeHeaderButton"_s);
    buttonsLayout->addWidget(removeHeaderButton);
    buttonsLayout->addStretch(1);
    connect(removeHeaderButton, &QPushButton::clicked, this, &AddMcpSteamableHttpServerHeaderWidget::slotRemoveHeader);
    mainLayout->addLayout(buttonsLayout);
}

AddMcpSteamableHttpServerHeaderWidget::~AddMcpSteamableHttpServerHeaderWidget() = default;

void AddMcpSteamableHttpServerHeaderWidget::slotRemoveHeader()
{
    if (KMessageBox::ButtonCode::PrimaryAction
        == KMessageBox::questionTwoActions(this,
                                           i18n("Are you sure that you want to delete this header?"),
                                           i18nc("@title:window", "Remove Header"),
                                           KStandardGuiItem::remove(),
                                           KStandardGuiItem::cancel())) {
        // TODO
    }
}

void AddMcpSteamableHttpServerHeaderWidget::slotAddHeader()
{
    QPointer<AddMcpSteamableHttpServerHeaderConfigureDialog> dlg = new AddMcpSteamableHttpServerHeaderConfigureDialog(this);
    if (dlg->exec()) {
        const QString header = dlg->header();
        mListBox->addHeader(header);
    }
    delete dlg;
}

void AddMcpSteamableHttpServerHeaderWidget::slotModifyHeader()
{
    QPointer<AddMcpSteamableHttpServerHeaderConfigureDialog> dlg = new AddMcpSteamableHttpServerHeaderConfigureDialog(this);
    if (dlg->exec()) {
        const QString header = dlg->header();
        mListBox->addHeader(header);
    }
    delete dlg;
    // TODO
}

QStringList AddMcpSteamableHttpServerHeaderWidget::headers() const
{
    return mListBox->headers();
}

void AddMcpSteamableHttpServerHeaderWidget::setHeaders(const QStringList &h)
{
    mListBox->setHeaders(h);
}

#include "moc_addmcpsteamablehttpserverheaderwidget.cpp"
