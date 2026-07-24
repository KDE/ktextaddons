/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpsteamablehttpserverheaderwidget.h"
#include <KLocalizedString>
#include <QListWidget>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpSteamableHttpServerHeaderWidget::AddMcpSteamableHttpServerHeaderWidget(QWidget *parent)
    : QWidget{parent}
    , mListBox(new QListWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mListBox->setObjectName(u"mListBox"_s);
    mainLayout->addWidget(mListBox);
}

AddMcpSteamableHttpServerHeaderWidget::~AddMcpSteamableHttpServerHeaderWidget() = default;

QStringList AddMcpSteamableHttpServerHeaderWidget::headers() const
{
    // TODO
    return {};
}

void AddMcpSteamableHttpServerHeaderWidget::setHeaders(const QStringList &h)
{
    mListBox->addItems(h);
}

#include "moc_addmcpsteamablehttpserverheaderwidget.cpp"
