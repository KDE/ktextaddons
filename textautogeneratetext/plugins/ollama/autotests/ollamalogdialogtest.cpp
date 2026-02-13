/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamalogdialogtest.h"
#include "ollamalogdialog.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaLogDialogTest)
using namespace Qt::Literals::StringLiterals;
OllamaLogDialogTest::OllamaLogDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void OllamaLogDialogTest::shouldHaveDefaultValue()
{
    const OllamaLogDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), {QDialogButtonBox::Close});
}
#include "moc_ollamalogdialogtest.cpp"
