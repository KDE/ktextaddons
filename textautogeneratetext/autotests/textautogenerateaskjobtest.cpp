/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaskjobtest.h"
#include "core/textautogenerateaskjob.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateAskJobTest)

TextAutoGenerateAskJobTest::TextAutoGenerateAskJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAskJobTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateAskJob w;
    // TODO
}

#include "moc_textautogenerateaskjobtest.cpp"
