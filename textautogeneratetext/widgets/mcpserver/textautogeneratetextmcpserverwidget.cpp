/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpserverwidget.h"
#include "textautogenerateaddmcpserverdialog.h"
#include "textautogeneratetextmcpserverlistview.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPointer>
#include <QToolButton>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextMcpServerWidget::TextAutoGenerateTextMcpServerWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mMcpServerListView(new TextAutoGenerateTextMcpServerListView(manager, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->setSpacing(0);

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setContentsMargins({});
    hboxLayout->setObjectName(u"hboxLayout"_s);

    mainLayout->addLayout(hboxLayout);

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    hboxLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mMcpServerListView, &TextAutoGenerateTextMcpServerListView::slotSearchChanged);

    auto addMcpServerButton = new QToolButton(this);
    addMcpServerButton->setObjectName(u"addMcpServerButton"_s);
    addMcpServerButton->setIcon(QIcon::fromTheme(u"list-add"_s));
    addMcpServerButton->setToolTip(i18nc("@info:tooltip", "Add Instance…"));
    addMcpServerButton->setAutoRaise(true);
    hboxLayout->addWidget(addMcpServerButton);
    connect(addMcpServerButton, &QToolButton::clicked, this, &TextAutoGenerateTextMcpServerWidget::slotAddServer);

    mMcpServerListView->setObjectName(u"mMcpServerListView"_s);
    mainLayout->addWidget(mMcpServerListView);

    connect(mMcpServerListView, &TextAutoGenerateTextMcpServerListView::addServer, this, &TextAutoGenerateTextMcpServerWidget::slotAddServer);
    connect(mMcpServerListView, &TextAutoGenerateTextMcpServerListView::removeServer, this, &TextAutoGenerateTextMcpServerWidget::slotRemoveServer);
    connect(mMcpServerListView, &TextAutoGenerateTextMcpServerListView::editServer, this, &TextAutoGenerateTextMcpServerWidget::slotEditServer);
}

TextAutoGenerateTextMcpServerWidget::~TextAutoGenerateTextMcpServerWidget() = default;

void TextAutoGenerateTextMcpServerWidget::slotAddServer()
{
    QPointer<TextAutoGenerateAddMcpServerDialog> dlg = new TextAutoGenerateAddMcpServerDialog(this);
    if (dlg->exec()) {
        // TODO
    }
    delete dlg;
}

void TextAutoGenerateTextMcpServerWidget::slotRemoveServer(const QByteArray &identifier)
{
    // TODO
}

void TextAutoGenerateTextMcpServerWidget::slotEditServer(const QByteArray &identifier)
{
    QPointer<TextAutoGenerateAddMcpServerDialog> dlg = new TextAutoGenerateAddMcpServerDialog(this);
    if (dlg->exec()) {
        // TODO
    }
    delete dlg;
}

#include "moc_textautogeneratetextmcpserverwidget.cpp"
