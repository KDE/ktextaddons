/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewngdialog.h"
#include "whatsnewng/whatsnewngwidget.h"

#include <KLocalizedString>
#include <QCoreApplication>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

using namespace Qt::Literals::StringLiterals;

namespace
{
const char myWhatsNewNgDialogNgGroupName[] = "WhatsNewNgDialogNg";
}
using namespace TextAddonsWidgets;
WhatsNewNgDialog::WhatsNewNgDialog(const QString &applicationName, QWidget *parent)
    : QDialog(parent)
    , mWhatsNewWidget(new WhatsNewNgWidget(this))
{
    setWindowTitle(i18nc("@title:window", "What's new in %1", applicationName));
    initialize();
}

WhatsNewNgDialog::WhatsNewNgDialog(QWidget *parent)
    : WhatsNewNgDialog(QCoreApplication::applicationName(), parent)
{
}

void WhatsNewNgDialog::setReleases(const QList<KAboutRelease> &info)
{
    mWhatsNewWidget->setReleases(info);
}

void WhatsNewNgDialog::initialize()
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mWhatsNewWidget->setObjectName(u"mWhatsNewWidget"_s);
    mainLayout->addWidget(mWhatsNewWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &WhatsNewNgDialog::reject);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myWhatsNewNgDialogNgGroupName), QSize(400, 300));
}

WhatsNewNgDialog::~WhatsNewNgDialog() = default;

#include "moc_whatsnewngdialog.cpp"
