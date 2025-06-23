/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "begamotenginedialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "begamotenginedialog.h"
#include "bergamotenginewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(BegamotEngineDialogTest)
BegamotEngineDialogTest::BegamotEngineDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void BegamotEngineDialogTest::shouldHaveDefaultValues()
{
    BegamotEngineDialog w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mBergamotEngineWidget = w.findChild<BergamotEngineWidget *>(u"mBergamotEngineWidget"_s);
    QVERIFY(mBergamotEngineWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

#include "moc_begamotenginedialogtest.cpp"
