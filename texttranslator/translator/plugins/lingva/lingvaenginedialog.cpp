/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lingvaenginedialog.h"
using namespace Qt::Literals::StringLiterals;

#include "lingvaenginewidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

LingvaEngineDialog::LingvaEngineDialog(QWidget *parent)
    : QDialog(parent)
    , mConfigureWidget(new LingvaEngineWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Engine"));
    mConfigureWidget->setObjectName(u"mConfigureWidget"_s);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->addWidget(mConfigureWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &LingvaEngineDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &LingvaEngineDialog::reject);
}

LingvaEngineDialog::~LingvaEngineDialog() = default;

QString LingvaEngineDialog::serverUrl() const
{
    return mConfigureWidget->serverUrl();
}

void LingvaEngineDialog::setServerUrl(const QString &serverUrl)
{
    mConfigureWidget->setServerUrl(serverUrl);
}

#include "moc_lingvaenginedialog.cpp"
