/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "begamotenginedialogtest.h"
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
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mBergamotEngineWidget = w.findChild<BergamotEngineWidget *>(QStringLiteral("mBergamotEngineWidget"));
    QVERIFY(mBergamotEngineWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
}

#include "moc_begamotenginedialogtest.cpp"
