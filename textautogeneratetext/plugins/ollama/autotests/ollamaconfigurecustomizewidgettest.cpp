/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaconfigurecustomizewidgettest.h"
#include "ollamaconfigurecustomizewidget.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QTest>

QTEST_MAIN(OllamaConfigureCustomizeWidgetTest)
using namespace Qt::Literals::StringLiterals;

OllamaConfigureCustomizeWidgetTest::OllamaConfigureCustomizeWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaConfigureCustomizeWidgetTest::shouldHaveDefaultValues()
{
    const OllamaConfigureCustomizeWidget w;

    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mVulkanSupportLineEdit = w.findChild<QLineEdit *>(u"mVulkanSupportLineEdit"_s);
    QVERIFY(mVulkanSupportLineEdit);
    QVERIFY(mVulkanSupportLineEdit->text().isEmpty());

    auto mCudaVisibleDeviceLineEdit = w.findChild<QLineEdit *>(u"mCudaVisibleDeviceLineEdit"_s);
    QVERIFY(mCudaVisibleDeviceLineEdit);
    QVERIFY(mCudaVisibleDeviceLineEdit->text().isEmpty());

    auto mRocrVisibleDeviceLineEdit = w.findChild<QLineEdit *>(u"mRocrVisibleDeviceLineEdit"_s);
    QVERIFY(mRocrVisibleDeviceLineEdit);
    QVERIFY(mRocrVisibleDeviceLineEdit->text().isEmpty());

    auto mOverrideGfxVersionLineEdit = w.findChild<QLineEdit *>(u"mOverrideGfxVersionLineEdit"_s);
    QVERIFY(mOverrideGfxVersionLineEdit);
    QVERIFY(mOverrideGfxVersionLineEdit->text().isEmpty());
}

#include "moc_ollamaconfigurecustomizewidgettest.cpp"
