/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineconfigurewidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KLineEditEventHandler>

#include <KLocalizedString>
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>

DeeplEngineConfigureWidget::DeeplEngineConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mUseFreeLicense(new QCheckBox(i18nc("@option:check", "Use Free License Key"), this))
    , mApiKey(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
    KLineEditEventHandler::catchReturnKey(mApiKey);
    mUseFreeLicense->setObjectName(u"mUseFreeLicense"_s);
    mainLayout->addWidget(mUseFreeLicense);

    mApiKey->setObjectName(u"mApiKey"_s);
    mApiKey->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Api Key:"), mApiKey);
}

DeeplEngineConfigureWidget::~DeeplEngineConfigureWidget() = default;

void DeeplEngineConfigureWidget::setUseFreeLicenceKey(bool b)
{
    mUseFreeLicense->setChecked(b);
}

bool DeeplEngineConfigureWidget::useFreeLicenceKey() const
{
    return mUseFreeLicense->isChecked();
}

QString DeeplEngineConfigureWidget::apiKey() const
{
    return mApiKey->text();
}

void DeeplEngineConfigureWidget::setApiKey(const QString &key)
{
    mApiKey->setText(key);
}

#include "moc_deeplengineconfigurewidget.cpp"
