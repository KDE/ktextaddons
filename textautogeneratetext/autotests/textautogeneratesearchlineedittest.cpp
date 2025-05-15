/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchlineedittest.h"
#include "widgets/textautogeneratesearchlineedit.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateSearchLineEditTest)

TextAutoGenerateSearchLineEditTest::TextAutoGenerateSearchLineEditTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchLineEditTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSearchLineEdit w;
    // TODO
}

#include "moc_textautogeneratesearchlineedittest.cpp"
