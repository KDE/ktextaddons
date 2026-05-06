/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstdioserverwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpStdioServerWidget::AddMcpStdioServerWidget(QWidget *parent)
    : QWidget{parent}
    , mCommandLineEdit(new QLineEdit(this))
    , mArgumentsLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->setSpacing(0);

    mCommandLineEdit->setObjectName(u"mCommandLineEdit"_s);
    mainLayout->addRow(i18n("Command:"), mCommandLineEdit);
    KLineEditEventHandler::catchReturnKey(mCommandLineEdit);

    mArgumentsLineEdit->setObjectName(u"mArgumentsLineEdit"_s);
    mainLayout->addRow(i18n("Arguments:"), mArgumentsLineEdit);
    KLineEditEventHandler::catchReturnKey(mArgumentsLineEdit);

    connect(mCommandLineEdit, &QLineEdit::textChanged, this, &AddMcpStdioServerWidget::settingChanged);
    connect(mArgumentsLineEdit, &QLineEdit::textChanged, this, &AddMcpStdioServerWidget::settingChanged);
}

AddMcpStdioServerWidget::~AddMcpStdioServerWidget() = default;

#include "moc_addmcpstdioserverwidget.cpp"
