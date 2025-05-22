/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openaiconfigurewidget.h"
#include <KAuthorized>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KPasswordLineEdit>
#include <QFormLayout>

OpenAIConfigureWidget::OpenAIConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mApiKey(new KPasswordLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
    mApiKey->setObjectName(QStringLiteral("mApiKey"));

    mApiKey->setObjectName(QStringLiteral("mPasswordLineEdit"));
    mApiKey->setRevealPasswordMode(KAuthorized::authorize(QStringLiteral("lineedit_reveal_password")) ? KPassword::RevealMode::OnlyNew
                                                                                                      : KPassword::RevealMode::Never);

    mainLayout->addRow(i18n("Api Key:"), mApiKey);
    KLineEditEventHandler::catchReturnKey(mApiKey->lineEdit());

    // TODO add key here.
    // Store key in wallet ?
}

OpenAIConfigureWidget::~OpenAIConfigureWidget() = default;

void OpenAIConfigureWidget::setApiKey(const QString &key)
{
    mApiKey->setPassword(key);
}

QString OpenAIConfigureWidget::apiKey() const
{
    return mApiKey->password();
}

#include "moc_openaiconfigurewidget.cpp"
