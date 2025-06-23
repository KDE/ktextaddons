/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "deeplengineconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

DeeplEngineConfigureDialog::DeeplEngineConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mConfigureWidget(new DeeplEngineConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Engine"));
    mConfigureWidget->setObjectName(u"mConfigureWidget"_s);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->addWidget(mConfigureWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &DeeplEngineConfigureDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DeeplEngineConfigureDialog::reject);
}

DeeplEngineConfigureDialog::~DeeplEngineConfigureDialog() = default;

void DeeplEngineConfigureDialog::setUseFreeLicenceKey(bool b)
{
    mConfigureWidget->setUseFreeLicenceKey(b);
}

bool DeeplEngineConfigureDialog::useFreeLicenceKey() const
{
    return mConfigureWidget->useFreeLicenceKey();
}

QString DeeplEngineConfigureDialog::apiKey() const
{
    return mConfigureWidget->apiKey();
}

void DeeplEngineConfigureDialog::setApiKey(const QString &key)
{
    mConfigureWidget->setApiKey(key);
}

#include "moc_deeplengineconfiguredialog.cpp"
