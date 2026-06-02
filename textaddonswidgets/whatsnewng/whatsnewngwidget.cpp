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
    mAboutRelease = info;
    initialize();
}

void WhatsNewNgWidget::initialize()
{
    mWhatsNewComboBoxWidget->addVersion(i18n("All Versions"), allVersion);
    for (int i = 0; i < mAboutRelease.count(); i++) {
        const auto &info = mAboutRelease.at(i);
        mWhatsNewComboBoxWidget->addVersion(i18n("Version %1", info.version()), i);
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
        for (int i = 0; i < mAboutRelease.count(); i++) {
            const auto &info = mAboutRelease.at(i);
            message += generateVersionHeader(i);
            message += featuresChangeStr();
            message += info.description();
        }
        mLabelInfo->setHtml(generateStartEndHtml(message));
    } else if (type >= 0 && type < mAboutRelease.count()) {
        QString message = featuresChangeStr();
        message += generateStartEndHtml(mAboutRelease.at(type).description());
        mLabelInfo->setHtml(message);
    }
}

QString WhatsNewNgWidget::generateVersionHeader(int type) const
{
    if (type != allVersion) {
        const auto release = mAboutRelease.at(type);
        const QDate date = release.date();
        if (date.isValid()) {
            return i18n("<h1><i> Version %1 (Released: %2)</i></h1><hr/><br>", release.version(), QLocale().toString(date, QLocale::ShortFormat));
        } else {
            return i18n("<h1><i> Version %1 (Unreleased yet)</i></h1><hr/><br>", release.version());
        }
    }
    return {};
}

QString WhatsNewNgWidget::featuresChangeStr() const
{
    return QStringLiteral("<b>") + i18n("Some of the new features in this release include:") + QStringLiteral("</b>");
}

QString WhatsNewNgWidget::generateStartEndHtml(const QString &str) const
{
    const QString message = QStringLiteral("<qt>") + str + QStringLiteral("</qt>");
    return message;
}

#include "moc_whatsnewngwidget.cpp"
