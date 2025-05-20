/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralconfigurewidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>

MistralConfigureWidget::MistralConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mApiKey(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
    mApiKey->setObjectName(QStringLiteral("mApiKey"));

    mainLayout->addRow(i18n("Api Key:"), mApiKey);
    KLineEditEventHandler::catchReturnKey(mApiKey);

    // TODO add key here.
    // Store key in wallet ?
}

MistralConfigureWidget::~MistralConfigureWidget() = default;

void MistralConfigureWidget::setApiKey(const QString &key)
{
    mApiKey->setText(key);
}

QString MistralConfigureWidget::apiKey() const
{
    return mApiKey->text();
}

#include "moc_mistralconfigurewidget.cpp"
