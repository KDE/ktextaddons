/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpsteamablehttpserverheaderlistwidget.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpSteamableHttpServerHeaderListWidget::AddMcpSteamableHttpServerHeaderListWidget(QWidget *parent)
    : QListWidget(parent)
{
}

AddMcpSteamableHttpServerHeaderListWidget::~AddMcpSteamableHttpServerHeaderListWidget() = default;

void AddMcpSteamableHttpServerHeaderListWidget::setHeaders(const QStringList &lst)
{
    addItems(lst);
}

QStringList AddMcpSteamableHttpServerHeaderListWidget::headers() const
{
    QStringList lst;
    for (int i = 0; i < count(); ++i) {
        lst.append(item(i)->text());
    }
    return lst;
}

void AddMcpSteamableHttpServerHeaderListWidget::addHeader(const QString &str)
{
    addItem(str);
}

QString AddMcpSteamableHttpServerHeaderListWidget::currentText() const
{
    if (auto c = currentItem(); c) {
        return c->text();
    }
    return {};
}

#include "moc_addmcpsteamablehttpserverheaderlistwidget.cpp"
