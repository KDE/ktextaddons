/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpstreamablehttpserverheaderwidget.h"
#include "addmcpstreamablehttpserverheaderconfiguredialog.h"
#include "addmcpstreamablehttpserverheaderlistwidget.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QPointer>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpStreamableHttpServerHeaderWidget::AddMcpStreamableHttpServerHeaderWidget(QWidget *parent)
    : QWidget{parent}
    , mListBox(new AddMcpStreamableHttpServerHeaderListWidget(this))
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
    connect(addHeaderButton, &QPushButton::clicked, this, &AddMcpStreamableHttpServerHeaderWidget::slotAddHeader);

    mModifyHeaderButton = new QPushButton(i18nc("@action:button", "Modify"), this);
    mModifyHeaderButton->setObjectName(u"modifyHeaderButton"_s);
    buttonsLayout->addWidget(mModifyHeaderButton);
    connect(mModifyHeaderButton, &QPushButton::clicked, this, &AddMcpStreamableHttpServerHeaderWidget::slotModifyHeader);

    mRemoveHeaderButton = new QPushButton(i18nc("@action:button", "Remove"), this);
    mRemoveHeaderButton->setObjectName(u"removeHeaderButton"_s);
    buttonsLayout->addWidget(mRemoveHeaderButton);
    buttonsLayout->addStretch(1);
    connect(mRemoveHeaderButton, &QPushButton::clicked, this, &AddMcpStreamableHttpServerHeaderWidget::slotRemoveHeader);
    mainLayout->addLayout(buttonsLayout);

    connect(mListBox, &AddMcpStreamableHttpServerHeaderListWidget::itemSelectionChanged, this, &AddMcpStreamableHttpServerHeaderWidget::updateButtons);
    connect(mListBox, &AddMcpStreamableHttpServerHeaderListWidget::itemDoubleClicked, this, &AddMcpStreamableHttpServerHeaderWidget::slotModifyHeader);
    updateButtons();
}

void AddMcpStreamableHttpServerHeaderWidget::updateButtons()
{
    const bool hasSelection = mListBox->currentItem() && !mListBox->selectedItems().isEmpty();
    mModifyHeaderButton->setEnabled(hasSelection);
    mRemoveHeaderButton->setEnabled(hasSelection);
}

AddMcpStreamableHttpServerHeaderWidget::~AddMcpStreamableHttpServerHeaderWidget() = default;

void AddMcpStreamableHttpServerHeaderWidget::slotRemoveHeader()
{
    if (!mListBox->currentItem()) {
        return;
    }
    if (KMessageBox::ButtonCode::PrimaryAction
        == KMessageBox::questionTwoActions(this,
                                           i18nc("@info", "Are you sure that you want to delete this header?"),
                                           i18nc("@title:window", "Remove Header"),
                                           KStandardGuiItem::remove(),
                                           KStandardGuiItem::cancel())) {
        delete mListBox->takeItem(mListBox->currentRow());
        updateButtons();
    }
}

void AddMcpStreamableHttpServerHeaderWidget::slotAddHeader()
{
    QPointer<AddMcpStreamableHttpServerHeaderConfigureDialog> dlg = new AddMcpStreamableHttpServerHeaderConfigureDialog(this);
    if (dlg->exec()) {
        const QString header = dlg->header();
        mListBox->addHeader(header);
    }
    delete dlg;
}

void AddMcpStreamableHttpServerHeaderWidget::slotModifyHeader()
{
    if (!mListBox->currentItem()) {
        return;
    }
    QPointer<AddMcpStreamableHttpServerHeaderConfigureDialog> dlg = new AddMcpStreamableHttpServerHeaderConfigureDialog(this);
    dlg->setHeader(mListBox->currentText());
    if (dlg->exec()) {
        const QString header = dlg->header();
        mListBox->modifyHeader(header);
    }
    delete dlg;
}

QStringList AddMcpStreamableHttpServerHeaderWidget::headers() const
{
    return mListBox->headers();
}

void AddMcpStreamableHttpServerHeaderWidget::setHeaders(const QStringList &h)
{
    mListBox->setHeaders(h);
    updateButtons();
}

#include "moc_addmcpstreamablehttpserverheaderwidget.cpp"
