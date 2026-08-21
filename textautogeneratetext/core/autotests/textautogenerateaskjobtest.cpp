/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaskjobtest.h"
#include "core/jobs/textautogenerateaskjob.h"
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateAskJobTest)

TextAutoGenerateAskJobTest::TextAutoGenerateAskJobTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateAskJobTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateAskJob w;
    QVERIFY(!w.manager());
    QVERIFY(w.text().isEmpty());
    QVERIFY(!w.canStart());
}

#include "moc_textautogenerateaskjobtest.cpp"
