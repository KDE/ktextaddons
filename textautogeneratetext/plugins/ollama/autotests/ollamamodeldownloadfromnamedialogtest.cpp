/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadfromnamedialogtest.h"

#include "modelsmanager/ollamamodeldownloadfromnamedialog.h"
#include "modelsmanager/ollamamodeldownloadfromnamewidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaModelDownloadFromNameDialogTest)

using namespace Qt::Literals::StringLiterals;
OllamaModelDownloadFromNameDialogTest::OllamaModelDownloadFromNameDialogTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelDownloadFromNameDialogTest::shouldHaveDefaultValues()
{
    OllamaModelDownloadFromNameDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mOllamaModelDownloadFromNameWidget = w.findChild<OllamaModelDownloadFromNameWidget *>(u"mOllamaModelDownloadFromNameWidget"_s);
    QVERIFY(mOllamaModelDownloadFromNameWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"box"_s);
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), {QDialogButtonBox::Ok | QDialogButtonBox::Cancel});
}

#include "moc_ollamamodeldownloadfromnamedialogtest.cpp"
