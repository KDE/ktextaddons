/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lingvaenginewidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>

LingvaEngineWidget::LingvaEngineWidget(QWidget *parent)
    : QWidget{parent}
    , mServerUrl(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mServerUrl->setObjectName(u"mServerUrl"_s);
    mServerUrl->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Server Url:"), mServerUrl);
    KLineEditEventHandler::catchReturnKey(mServerUrl);
}

LingvaEngineWidget::~LingvaEngineWidget() = default;

QString LingvaEngineWidget::serverUrl() const
{
    return mServerUrl->text();
}

void LingvaEngineWidget::setServerUrl(const QString &serverUrl)
{
    mServerUrl->setText(serverUrl);
}

#include "moc_lingvaenginewidget.cpp"
