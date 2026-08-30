/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewngwidget.h"
#include "whatsnew/whatsnewcomboboxwidget.h"
#include "whatsnewng/whatsnewngutils.h"
#include <KAboutData>
#include <KLocalizedString>
#include <QDate>
#include <QDebug>
#include <QLocale>
#include <QTextBrowser>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;

using namespace TextAddonsWidgets;
WhatsNewNgWidget::WhatsNewNgWidget(QWidget *parent)
    : QWidget{parent}
    , mLabelInfo(new QTextBrowser(this))
    , mWhatsNewComboBoxWidget(new WhatsNewComboBoxWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mWhatsNewComboBoxWidget->setObjectName(u"mWhatsNewComboBoxWidget"_s);
    mainLayout->addWidget(mWhatsNewComboBoxWidget);
    connect(mWhatsNewComboBoxWidget, &WhatsNewComboBoxWidget::versionChanged, this, &WhatsNewNgWidget::slotVersionChanged);

    mLabelInfo->setObjectName(u"mLabelInfo"_s);
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
    mWhatsNewComboBoxWidget->addVersion(i18n("All Versions"), TextAddonsWidgets::WhatsNewNgUtils::allVersion());
    for (int i = 0, total = mAboutRelease.count(); i < total; ++i) {
        const auto &info = mAboutRelease.at(i);
        mWhatsNewComboBoxWidget->addVersion(info.version(), i);
    }
}

void WhatsNewNgWidget::slotVersionChanged(int type)
{
    const QString changeLog = TextAddonsWidgets::WhatsNewNgUtils::generateChangelog(mAboutRelease, type);
    if (changeLog.isEmpty()) {
        mLabelInfo->clear();
        return;
    }
    mLabelInfo->setHtml(changeLog);
}

#include "moc_whatsnewngwidget.cpp"
