/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpsteamablehttpserverheaderwidget.h"
#include <KLocalizedString>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpSteamableHttpServerHeaderWidget::AddMcpSteamableHttpServerHeaderWidget(QWidget *parent)
    : QWidget{parent}
    , mListBox(new QListWidget(this))
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

    auto modifyHeaderButton = new QPushButton(i18nc("@action:button", "Modify"), this);
    modifyHeaderButton->setObjectName(u"modifyHeaderButton"_s);
    buttonsLayout->addWidget(modifyHeaderButton);

    auto removeHeaderButton = new QPushButton(i18nc("@action:button", "Remove"), this);
    removeHeaderButton->setObjectName(u"removeHeaderButton"_s);
    buttonsLayout->addWidget(removeHeaderButton);
    buttonsLayout->addStretch(1);
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
