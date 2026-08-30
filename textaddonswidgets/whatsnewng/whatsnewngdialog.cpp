/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewngdialog.h"
#include "whatsnewng/whatsnewngwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QCoreApplication>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
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
    readConfig();
}

WhatsNewNgDialog::~WhatsNewNgDialog()
{
    writeConfig();
}

void WhatsNewNgDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myWhatsNewNgDialogNgGroupName), 400, 300);
}

void WhatsNewNgDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myWhatsNewNgDialogNgGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_whatsnewngdialog.cpp"
