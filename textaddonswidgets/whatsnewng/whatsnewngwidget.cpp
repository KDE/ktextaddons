/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewngwidget.h"
#include "whatsnew/whatsnewcomboboxwidget.h"
#include <KAboutData>
#include <KLocalizedString>
#include <QDate>
#include <QDebug>
#include <QLocale>
#include <QTextBrowser>
#include <QVBoxLayout>
namespace
{
constexpr int allVersion = -1;
}
using namespace TextAddonsWidgets;
WhatsNewNgWidget::WhatsNewNgWidget(QWidget *parent)
    : QWidget{parent}
    , mLabelInfo(new QTextBrowser(this))
    , mWhatsNewComboBoxWidget(new WhatsNewComboBoxWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mWhatsNewComboBoxWidget->setObjectName(QStringLiteral("mWhatsNewComboBoxWidget"));
    mainLayout->addWidget(mWhatsNewComboBoxWidget);
    connect(mWhatsNewComboBoxWidget, &WhatsNewComboBoxWidget::versionChanged, this, &WhatsNewNgWidget::slotVersionChanged);

    mLabelInfo->setObjectName(QStringLiteral("mLabelInfo"));
    mLabelInfo->setReadOnly(true);
    mLabelInfo->setOpenExternalLinks(true);
    mLabelInfo->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);
    mainLayout->addWidget(mLabelInfo);
}

WhatsNewNgWidget::~WhatsNewNgWidget() = default;

void WhatsNewNgWidget::setReleases(const QList<KAboutRelease> &info)
{
    mWhatsNewComboBoxWidget->clear();
    mAboutRelease = info;
    initialize();
}

void WhatsNewNgWidget::initialize()
{
    mWhatsNewComboBoxWidget->addVersion(i18n("All Versions"), allVersion);
    for (int i = 0, total = mAboutRelease.count(); i < total; ++i) {
        const auto &info = mAboutRelease.at(i);
        mWhatsNewComboBoxWidget->addVersion(info.version(), i);
    }
}

void WhatsNewNgWidget::slotVersionChanged(int type)
{
    if (mAboutRelease.isEmpty()) {
        mLabelInfo->clear();
        return;
    }
    if (type == allVersion) { // All
        QString message;
        message += i18n("<h1>What's New History</h1>");
        for (int i = 0, total = mAboutRelease.count(); i < total; ++i) {
            const auto &info = mAboutRelease.at(i);
            message += generateVersionHeader(info);
            message += info.description();
            message += generateUrl(info);
        }
        mLabelInfo->setHtml(generateStartEndHtml(message));
    } else if (type >= 0 && type < mAboutRelease.count()) {
        const auto &info = mAboutRelease.at(type);
        const QString message = generateVersionHeader(info) + info.description() + generateUrl(info);
        mLabelInfo->setHtml(message);
    }
}

QString WhatsNewNgWidget::generateUrl(const KAboutRelease &release) const
{
    if (release.url().isValid()) {
        return i18n("<b><i><a href=\"%1\">Release Note</a></i></b>", release.url().toString());
    }
    return {};
}

QString WhatsNewNgWidget::generateVersionHeader(const KAboutRelease &release) const
{
    const QDate date = release.date();
    if (date.isValid()) {
        return i18n("<h3><i>What's New in Version %1 (Released: %2)</i></h3>", release.version(), QLocale().toString(date, QLocale::ShortFormat));
    } else {
        return i18n("<h3><i>What's New in Version %1 (Unreleased)</i></h3>", release.version());
    }
}

QString WhatsNewNgWidget::generateStartEndHtml(const QString &str) const
{
    const QString message = QStringLiteral("<qt>") + str + QStringLiteral("</qt>");
    return message;
}

#include "moc_whatsnewngwidget.cpp"
