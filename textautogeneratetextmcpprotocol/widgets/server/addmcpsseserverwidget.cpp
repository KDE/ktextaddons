/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpsseserverwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpSseServerWidget::AddMcpSseServerWidget(QWidget *parent)
    : AddMcpServerBaseWidget{parent}
    , mServerUrlLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mServerUrlLineEdit->setObjectName(u"mServerUrlLineEdit"_s);
    mServerUrlLineEdit->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Url:"), mServerUrlLineEdit);
    KLineEditEventHandler::catchReturnKey(mServerUrlLineEdit);
    connect(mServerUrlLineEdit, &QLineEdit::textChanged, this, &AddMcpSseServerWidget::settingChanged);
}

AddMcpSseServerWidget::~AddMcpSseServerWidget() = default;

void AddMcpSseServerWidget::setUrl(const QString &str)
{
    mServerUrlLineEdit->setText(str);
}

QString AddMcpSseServerWidget::url() const
{
    return mServerUrlLineEdit->text();
}

bool AddMcpSseServerWidget::isValid() const
{
    return !mServerUrlLineEdit->text().isEmpty();
}

#include "moc_addmcpsseserverwidget.cpp"
