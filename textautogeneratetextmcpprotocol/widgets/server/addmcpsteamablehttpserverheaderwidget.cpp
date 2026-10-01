/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpsteamablehttpserverheaderwidget.h"
#include "addmcpsteamablehttpserverheaderconfiguredialog.h"
#include "addmcpsteamablehttpserverheaderlistwidget.h"
#include <KLocalizedString>
#include <KMessageBox>
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

    mModifyHeaderButton = new QPushButton(i18nc("@action:button", "Modify"), this);
    mModifyHeaderButton->setObjectName(u"modifyHeaderButton"_s);
    buttonsLayout->addWidget(mModifyHeaderButton);
    connect(mModifyHeaderButton, &QPushButton::clicked, this, &AddMcpSteamableHttpServerHeaderWidget::slotModifyHeader);

    mRemoveHeaderButton = new QPushButton(i18nc("@action:button", "Remove"), this);
    mRemoveHeaderButton->setObjectName(u"removeHeaderButton"_s);
    buttonsLayout->addWidget(mRemoveHeaderButton);
    buttonsLayout->addStretch(1);
    connect(mRemoveHeaderButton, &QPushButton::clicked, this, &AddMcpSteamableHttpServerHeaderWidget::slotRemoveHeader);
    mainLayout->addLayout(buttonsLayout);

    connect(mListBox, &AddMcpSteamableHttpServerHeaderListWidget::itemSelectionChanged, this, &AddMcpSteamableHttpServerHeaderWidget::updateButtons);
    connect(mListBox, &AddMcpSteamableHttpServerHeaderListWidget::itemDoubleClicked, this, &AddMcpSteamableHttpServerHeaderWidget::slotModifyHeader);
    updateButtons();
}

void AddMcpSteamableHttpServerHeaderWidget::updateButtons()
{
    const bool hasSelection = mListBox->currentItem() && !mListBox->selectedItems().isEmpty();
    mModifyHeaderButton->setEnabled(hasSelection);
    mRemoveHeaderButton->setEnabled(hasSelection);
}

AddMcpSteamableHttpServerHeaderWidget::~AddMcpSteamableHttpServerHeaderWidget() = default;

void AddMcpSteamableHttpServerHeaderWidget::slotRemoveHeader()
{
    if (!mListBox->currentItem()) {
        return;
    }
    if (KMessageBox::ButtonCode::PrimaryAction
        == KMessageBox::questionTwoActions(this,
                                           i18n("Are you sure that you want to delete this header?"),
                                           i18nc("@title:window", "Remove Header"),
                                           KStandardGuiItem::remove(),
                                           KStandardGuiItem::cancel())) {
        delete mListBox->takeItem(mListBox->currentRow());
        updateButtons();
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
    if (!mListBox->currentItem()) {
        return;
    }
    QPointer<AddMcpSteamableHttpServerHeaderConfigureDialog> dlg = new AddMcpSteamableHttpServerHeaderConfigureDialog(this);
    dlg->setHeader(mListBox->currentText());
    if (dlg->exec()) {
        const QString header = dlg->header();
        mListBox->modifyHeader(header);
    }
    delete dlg;
}

QStringList AddMcpSteamableHttpServerHeaderWidget::headers() const
{
    return mListBox->headers();
}

void AddMcpSteamableHttpServerHeaderWidget::setHeaders(const QStringList &h)
{
    mListBox->setHeaders(h);
    updateButtons();
}

#include "moc_addmcpsteamablehttpserverheaderwidget.cpp"
