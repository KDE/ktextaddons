/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "libretranslateengineconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

LibreTranslateEngineConfigureDialog::LibreTranslateEngineConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mConfigureWidget(new LibreTranslateEngineConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Engine"));

    mConfigureWidget->setObjectName(u"mConfigureWidget"_s);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->addWidget(mConfigureWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &LibreTranslateEngineConfigureDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &LibreTranslateEngineConfigureDialog::reject);
}

LibreTranslateEngineConfigureDialog::~LibreTranslateEngineConfigureDialog() = default;

QString LibreTranslateEngineConfigureDialog::serverUrl() const
{
    return mConfigureWidget->serverUrl();
}

void LibreTranslateEngineConfigureDialog::setServerUrl(const QString &serverUrl)
{
    mConfigureWidget->setServerUrl(serverUrl);
}

QString LibreTranslateEngineConfigureDialog::apiKey() const
{
    return mConfigureWidget->apiKey();
}

void LibreTranslateEngineConfigureDialog::setApiKey(const QString &key)
{
    mConfigureWidget->setApiKey(key);
}

bool LibreTranslateEngineConfigureDialog::serverRequiredApiKey() const
{
    return mConfigureWidget->serverRequiredApiKey();
}

void LibreTranslateEngineConfigureDialog::setServerRequiredApiKey(bool state)
{
    mConfigureWidget->setServerRequiredApiKey(state);
}

#include "moc_libretranslateengineconfiguredialog.cpp"
