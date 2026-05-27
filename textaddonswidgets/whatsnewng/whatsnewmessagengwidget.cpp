/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewmessagengwidget.h"

#include "whatsnewngdialog.h"
#include <KLocalizedString>
#include <QCoreApplication>

using namespace Qt::Literals::StringLiterals;
using namespace TextAddonsWidgets;
WhatsNewMessageNgWidget::WhatsNewMessageNgWidget(const QString &applicationName, QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setCloseButtonVisible(true);
    setMessageType(Information);

    mApplicationName = applicationName;
    setText(i18n("What's new in %2. %1", QStringLiteral("<a href=\"show_whats_new\">%1</a>").arg(i18n("(Show News)")), mApplicationName));
    setPosition(KMessageWidget::Header);
    connect(this, &KMessageWidget::linkActivated, this, &WhatsNewMessageNgWidget::slotLinkActivated);
}

WhatsNewMessageNgWidget::WhatsNewMessageNgWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setCloseButtonVisible(true);
    setMessageType(Information);

    mApplicationName = QCoreApplication::applicationName();
    setText(i18n("What's new in %2. %1", QStringLiteral("<a href=\"show_whats_new\">%1</a>").arg(i18n("(Show News)")), mApplicationName));
    setPosition(KMessageWidget::Header);
    connect(this, &KMessageWidget::linkActivated, this, &WhatsNewMessageNgWidget::slotLinkActivated);
}

WhatsNewMessageNgWidget::~WhatsNewMessageNgWidget() = default;

void WhatsNewMessageNgWidget::setReleases(const QList<KAboutRelease> &info)
{
    mReleasesInfo = info;
}

void WhatsNewMessageNgWidget::slotLinkActivated(const QString &contents)
{
    if (contents == "show_whats_new"_L1) {
        WhatsNewNgDialog dlg(mApplicationName, this);
        dlg.setReleases(mReleasesInfo);
        dlg.exec();
    }
}

#include "moc_whatsnewmessagengwidget.cpp"
