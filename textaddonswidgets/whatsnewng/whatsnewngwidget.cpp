/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewngwidget.h"
#include <KAboutData>
#include <QVBoxLayout>
using namespace TextAddonsWidgets;
WhatsNewNgWidget::WhatsNewNgWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    const KAboutData about = KAboutData::fromAppStreamForApplication();
}

WhatsNewNgWidget::~WhatsNewNgWidget() = default;
#include "moc_whatsnewngwidget.cpp"
