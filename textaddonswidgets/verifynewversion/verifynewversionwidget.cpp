/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "verifynewversionwidget.h"
#include "textaddonswidgets_debug.h"
#include "verifynewversion/checknewversiondialog.h"
#include "verifynewversionutils.h"
#include <KLocalizedString>
#include <QAction>
#include <QDesktopServices>
#include <QUrl>
using namespace TextAddonsWidgets;
using namespace Qt::Literals::StringLiterals;
VerifyNewVersionWidget::VerifyNewVersionWidget(QObject *parent)
    : QObject{parent}
{
}

VerifyNewVersionWidget::~VerifyNewVersionWidget() = default;

bool VerifyNewVersionWidget::canVerifyNewVersion() const
{
    return VerifyNewVersionUtils::canVerifyNewVersion();
}

QAction *VerifyNewVersionWidget::verifyNewVersionAction()
{
    if (!mVerifyNewVersionAction) {
        // TODO add icon
        mVerifyNewVersionAction = new QAction(i18n("Check New Version"), this);
        connect(mVerifyNewVersionAction, &QAction::triggered, this, &VerifyNewVersionWidget::slotVerifyNewVersion);
    }
    return mVerifyNewVersionAction;
}

void VerifyNewVersionWidget::generateUrlInfo([[maybe_unused]] const QString &stableBranchVersion, [[maybe_unused]] const QString &url)
{
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
    const QString defaultUrlPath = url;
    const QString stableBranch = stableBranchVersion;
    QString osName;

    TextAddonsWidgets::VerifyNewVersionWidget::OsVersion osVersion = TextAddonsWidgets::VerifyNewVersionWidget::OsVersionUnknown;

#if defined(Q_OS_WIN)
    osName = u"windows"_s;
    osVersion = TextAddonsWidgets::VerifyNewVersionWidget::OsVersion::Windows;
#else if defined(Q_OS_MACOS)
#ifdef Q_PROCESSOR_ARM_64
    osName = u"macos-arm64"_s;
    osVersion = TextAddonsWidgets::VerifyNewVersionWidget::OsVersion::MacOsArm64;
#else
    osName = u"macos-x86_64"_s;
    osVersion = TextAddonsWidgets::VerifyNewVersionWidget::OsVersion::MacOs;
#endif
#endif

#if KAICHAT_STABLE_VERSION
    const QString url = defaultUrlPath + u"/%1/%2/"_s.arg(stableBranch, osName);
#else
    const QString url = defaultUrlPath + u"/master/%1/"_s.arg(osName);
#endif
    addOsUrlInfo(osVersion, url);
#endif
}

void VerifyNewVersionWidget::addOsUrlInfo(OsVersion os, const QString &url)
{
    mUrls.insert(os, url);
}

void VerifyNewVersionWidget::slotVerifyNewVersion()
{
    QUrl url;
#ifdef Q_OS_WIN
    url = QUrl(mUrls.value(VerifyNewVersionWidget::OsVersion::Windows));
#endif

#ifdef Q_OS_MACOS
#ifdef Q_PROCESSOR_ARM_64
    url = QUrl(mUrls.value(VerifyNewVersionWidget::OsVersion::MacOsArm64));
#else
    url = QUrl(mUrls.value(VerifyNewVersionWidget::OsVersion::MacOs));
#endif
#endif
    if (!url.isEmpty()) {
        CheckNewVersionDialog dlg(nullptr);
        dlg.checkNewVersion();
        dlg.exec();
    }
}

#include "moc_verifynewversionwidget.cpp"
