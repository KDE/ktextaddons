/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "voskenginedialogtest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mVoskEngineWidget = w.findChild<VoskEngineLanguageWidget *>(u"mVoskEngineWidget"_s);
    QVERIFY(mVoskEngineWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

#include "moc_voskenginedialogtest.cpp"
