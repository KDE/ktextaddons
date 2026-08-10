/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpsteamablehttpserverheaderconfigurewidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
AddMcpSteamableHttpServerHeaderConfigureWidget::AddMcpSteamableHttpServerHeaderConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mHeaderLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mHeaderLineEdit->setObjectName(u"mHeaderLineEdit"_s);
    mHeaderLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Define Header…"));
    mHeaderLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mHeaderLineEdit);
}

AddMcpSteamableHttpServerHeaderConfigureWidget::~AddMcpSteamableHttpServerHeaderConfigureWidget() = default;

void AddMcpSteamableHttpServerHeaderConfigureWidget::setHeader(const QString &str)
{
    mHeaderLineEdit->setText(str);
}

QString AddMcpSteamableHttpServerHeaderConfigureWidget::header() const
{
    return mHeaderLineEdit->text();
}

#include "moc_addmcpsteamablehttpserverheaderconfigurewidget.cpp"
