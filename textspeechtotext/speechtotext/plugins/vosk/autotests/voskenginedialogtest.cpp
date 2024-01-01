/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "voskenginedialogtest.h"
#include "voskenginedialog.h"
#include "voskenginelanguagewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(VoskEngineDialogTest)
VoskEngineDialogTest::VoskEngineDialogTest(QObject *parent)
    : QObject{parent}
{
}

void VoskEngineDialogTest::shouldHaveDefaultValues()
{
    VoskEngineDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mVoskEngineWidget = w.findChild<VoskEngineLanguageWidget *>(QStringLiteral("mVoskEngineWidget"));
    QVERIFY(mVoskEngineWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
}

#include "moc_voskenginedialogtest.cpp"
