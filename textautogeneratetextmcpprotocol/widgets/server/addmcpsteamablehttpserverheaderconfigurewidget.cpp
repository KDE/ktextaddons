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

    auto label = new QLabel(i18nc("@label:textbox", "Header:"), this);
    label->setObjectName(u"label"_s);
    mainLayout->addWidget(label);

    mHeaderLineEdit->setObjectName(u"mHeaderLineEdit"_s);
    mHeaderLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Name: Value"));
    mHeaderLineEdit->setClearButtonEnabled(true);
    mainLayout->addWidget(mHeaderLineEdit);
    KLineEditEventHandler::catchReturnKey(mHeaderLineEdit);
    connect(mHeaderLineEdit, &QLineEdit::textChanged, this, [this](const QString &str) {
        // Header must use "Name: Value" format
        const qsizetype index = str.indexOf(u':');
        Q_EMIT buttonOkEnabled(index > 0 && !str.left(index).trimmed().isEmpty());
    });
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
