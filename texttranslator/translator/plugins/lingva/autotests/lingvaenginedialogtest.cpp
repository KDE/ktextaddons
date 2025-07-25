/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lingvaenginedialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../lingvaenginedialog.h"
#include "../lingvaenginewidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(LingvaEngineDialogTest)
LingvaEngineDialogTest::LingvaEngineDialogTest(QObject *parent)
    : QObject{parent}
{
}

void LingvaEngineDialogTest::shouldHaveDefaultValues()
{
    LingvaEngineDialog d;
    QVERIFY(!d.windowTitle().isEmpty());
    auto mConfigureWidget = d.findChild<LingvaEngineWidget *>(u"mConfigureWidget"_s);
    QVERIFY(mConfigureWidget);

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto buttonBox = d.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

#include "moc_lingvaenginedialogtest.cpp"
