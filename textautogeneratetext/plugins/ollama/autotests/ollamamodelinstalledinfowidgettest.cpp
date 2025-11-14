/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfowidgettest.h"
#include "modelsmanager/ollamamodelinstalledinfowidget.h"
#include "modelsmanager/ollamanetworkurlbutton.h"
#include <QLabel>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(OllamaModelInstalledInfoWidgetTest)
using namespace Qt::Literals::StringLiterals;
OllamaModelInstalledInfoWidgetTest::OllamaModelInstalledInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelInstalledInfoWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelInstalledInfoWidget w;
    auto mFamilyNameLabel = w.findChild<QLabel *>(u"mFamilyNameLabel"_s);
    QVERIFY(mFamilyNameLabel);

    auto mQuantizationLevelLabel = w.findChild<QLabel *>(u"mQuantizationLevelLabel"_s);
    QVERIFY(mQuantizationLevelLabel);

    auto mModifiedAtLabel = w.findChild<QLabel *>(u"mModifiedAtLabel"_s);
    QVERIFY(mModifiedAtLabel);

    auto mMainLayout = w.findChild<QVBoxLayout *>(u"mMainLayout"_s);
    QVERIFY(mMainLayout);

    auto mNetworkUrlButton = w.findChild<OllamaNetworkUrlButton *>(u"mNetworkUrlButton"_s);
    QVERIFY(mNetworkUrlButton);
}

#include "moc_ollamamodelinstalledinfowidgettest.cpp"
