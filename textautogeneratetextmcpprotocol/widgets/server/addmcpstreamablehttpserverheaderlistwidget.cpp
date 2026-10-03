/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstreamablehttpserverheaderlistwidget.h"

using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpStreamableHttpServerHeaderListWidget::AddMcpStreamableHttpServerHeaderListWidget(QWidget *parent)
    : QListWidget(parent)
{
}

AddMcpStreamableHttpServerHeaderListWidget::~AddMcpStreamableHttpServerHeaderListWidget() = default;

void AddMcpStreamableHttpServerHeaderListWidget::setHeaders(const QStringList &lst)
{
    clear();
    addItems(lst);
}

QStringList AddMcpStreamableHttpServerHeaderListWidget::headers() const
{
    QStringList lst;
    lst.reserve(count());
    for (int i = 0; i < count(); ++i) {
        lst.append(item(i)->text());
    }
    return lst;
}

void AddMcpStreamableHttpServerHeaderListWidget::addHeader(const QString &str)
{
    addItem(str);
}

void AddMcpStreamableHttpServerHeaderListWidget::modifyHeader(const QString &str)
{
    if (auto c = currentItem(); c) {
        c->setText(str);
    }
}

QString AddMcpStreamableHttpServerHeaderListWidget::currentText() const
{
    if (auto c = currentItem(); c) {
        return c->text();
    }
    return {};
}

#include "moc_addmcpstreamablehttpserverheaderlistwidget.cpp"
