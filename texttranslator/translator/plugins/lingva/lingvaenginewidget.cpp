/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lingvaenginewidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)
#include <TextAddonsWidgets/LineEditCatchReturnKey>
#else
#include <KLineEditEventHandler>
#endif

LingvaEngineWidget::LingvaEngineWidget(QWidget *parent)
    : QWidget{parent}
    , mServerUrl(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mServerUrl->setObjectName(QStringLiteral("mServerUrl"));
    mServerUrl->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Server Url:"), mServerUrl);
#if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)
    new TextAddonsWidgets::LineEditCatchReturnKey(mServerUrl, this);
#else
    KLineEditEventHandler::catchReturnKey(mServerUrl);
#endif
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
