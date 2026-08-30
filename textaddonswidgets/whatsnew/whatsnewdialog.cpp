/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewdialog.h"
#include "whatsnewwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

using namespace Qt::Literals::StringLiterals;

namespace
{
const char myWhatsNewDialogGroupName[] = "WhatsNewDialog";
}
using namespace TextAddonsWidgets;
WhatsNewDialog::WhatsNewDialog(const QList<TextAddonsWidgets::WhatsNewInfo> &infos, QWidget *parent, const QString &applicationName)
    : QDialog(parent)
    , mWhatsNewWidget(new WhatsNewWidget(infos, this))
{
    setWindowTitle(i18nc("@title:window", "What's new in %1", applicationName));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mWhatsNewWidget->setObjectName(u"mWhatsNewWidget"_s);
    mainLayout->addWidget(mWhatsNewWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &WhatsNewDialog::reject);
    readConfig();
}

WhatsNewDialog::~WhatsNewDialog()
{
    writeConfig();
}

void WhatsNewDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myWhatsNewDialogGroupName), 400, 300);
}

void WhatsNewDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myWhatsNewDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void WhatsNewDialog::updateInformations()
{
    mWhatsNewWidget->updateInformations();
}

#include "moc_whatsnewdialog.cpp"
