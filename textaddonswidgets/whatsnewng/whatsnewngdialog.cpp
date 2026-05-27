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
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
const char myWhatsNewNgDialogNgGroupName[] = "WhatsNewNgDialogNg";
}
using namespace TextAddonsWidgets;
WhatsNewNgDialog::WhatsNewNgDialog(const QString &applicationId, const QString &applicationName, QWidget *parent)
    : QDialog(parent)
    , mWhatsNewWidget(new WhatsNewNgWidget(this, applicationId))
{
    setWindowTitle(i18nc("@title:window", "What's new in %1", applicationName));
    initialize();
}

WhatsNewNgDialog::WhatsNewNgDialog(QWidget *parent)
    : QDialog(parent)
    , mWhatsNewWidget(new WhatsNewNgWidget(this))
{
    setWindowTitle(i18nc("@title:window", "What's new in %1", QCoreApplication::applicationName()));
    initialize();
}

void WhatsNewNgDialog::initialize()
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mWhatsNewWidget->setObjectName(QStringLiteral("mWhatsNewWidget"));
    mainLayout->addWidget(mWhatsNewWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(QStringLiteral("button"));
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
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myWhatsNewNgDialogNgGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void WhatsNewNgDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myWhatsNewNgDialogNgGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_whatsnewngdialog.cpp"
