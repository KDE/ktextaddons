/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checknewversiondialog.h"
#include "checknewversionwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;

using namespace TextAddonsWidgets;
CheckNewVersionDialog::CheckNewVersionDialog(QWidget *parent)
    : QDialog(parent)
    , mVerifyNewVersionWidget(new CheckNewVersionWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Check New Version"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mVerifyNewVersionWidget->setObjectName(u"mVerifyNewVersionWidget"_s);
    mainLayout->addWidget(mVerifyNewVersionWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckNewVersionDialog::reject);
    resize(300, 200);
}

CheckNewVersionDialog::~CheckNewVersionDialog() = default;

void CheckNewVersionDialog::checkNewVersion()
{
    mVerifyNewVersionWidget->checkNewVersion();
}

void CheckNewVersionDialog::setUrl(const QUrl &url)
{
    mVerifyNewVersionWidget->setUrl(url);
}

#include "moc_checknewversiondialog.cpp"
