/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineconfiguredialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../libretranslateengineconfiguredialog.h"
#include "../libretranslateengineconfigurewidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(LibreTranslateEngineConfigureDialogTest)
LibreTranslateEngineConfigureDialogTest::LibreTranslateEngineConfigureDialogTest(QObject *parent)
    : QObject{parent}
{
}

void LibreTranslateEngineConfigureDialogTest::shouldHaveDefaultValues()
{
    LibreTranslateEngineConfigureDialog d;
    QVERIFY(!d.windowTitle().isEmpty());
    auto mConfigureWidget = d.findChild<LibreTranslateEngineConfigureWidget *>(u"mConfigureWidget"_s);
    QVERIFY(mConfigureWidget);

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto buttonBox = d.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

#include "moc_libretranslateengineconfiguredialogtest.cpp"
