/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpsteamablehttpserverwidget.h"
#include <KLocalizedString>
#include <QLineEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpSteamableHttpServerWidget::AddMcpSteamableHttpServerWidget(QWidget *parent)
    : QWidget{parent}
    , mServerUrlLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->setSpacing(0);

    mServerUrlLineEdit->setObjectName(u"mServerUrlLineEdit"_s);
    mainLayout->addWidget(mServerUrlLineEdit);
}

AddMcpSteamableHttpServerWidget::~AddMcpSteamableHttpServerWidget() = default;

void AddMcpSteamableHttpServerWidget::setUrl(const QString &str)
{
    mServerUrlLineEdit->setText(str);
}

QString AddMcpSteamableHttpServerWidget::url() const
{
    return mServerUrlLineEdit->text();
}

#include "moc_addmcpsteamablehttpserverwidget.cpp"
