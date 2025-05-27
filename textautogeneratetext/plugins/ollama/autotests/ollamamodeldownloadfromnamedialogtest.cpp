/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadfromnamedialogtest.h"
#include "modelsmanager/ollamamodeldownloadfromnamedialog.h"
#include "modelsmanager/ollamamodeldownloadfromnamewidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaModelDownloadFromNameDialogTest)

OllamaModelDownloadFromNameDialogTest::OllamaModelDownloadFromNameDialogTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelDownloadFromNameDialogTest::shouldHaveDefaultValues()
{
    OllamaModelDownloadFromNameDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mOllamaModelDownloadFromNameWidget = w.findChild<OllamaModelDownloadFromNameWidget *>(QStringLiteral("mOllamaModelDownloadFromNameWidget"));
    QVERIFY(mOllamaModelDownloadFromNameWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("box"));
    QVERIFY(buttonBox);
}

#include "moc_ollamamodeldownloadfromnamedialogtest.cpp"
