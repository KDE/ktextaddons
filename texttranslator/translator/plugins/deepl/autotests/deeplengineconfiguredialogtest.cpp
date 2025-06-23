/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineconfiguredialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../deeplengineconfiguredialog.h"
#include "../deeplengineconfigurewidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(DeeplEngineConfigureDialogTest)
DeeplEngineConfigureDialogTest::DeeplEngineConfigureDialogTest(QObject *parent)
    : QObject{parent}
{
}

void DeeplEngineConfigureDialogTest::shouldHaveDefaultValues()
{
    DeeplEngineConfigureDialog d;
    QVERIFY(!d.windowTitle().isEmpty());
    auto mConfigureWidget = d.findChild<DeeplEngineConfigureWidget *>(u"mConfigureWidget"_s);
    QVERIFY(mConfigureWidget);

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto buttonBox = d.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

#include "moc_deeplengineconfiguredialogtest.cpp"
