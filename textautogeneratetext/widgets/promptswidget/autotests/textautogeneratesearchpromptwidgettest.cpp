/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchpromptwidgettest.h"
#include "widgets/promptswidget/textautogeneratesearchpromptwidget.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateSearchPromptWidgetTest)

TextAutoGenerateSearchPromptWidgetTest::TextAutoGenerateSearchPromptWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchPromptWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateSearchPromptWidget w;
    // TODO
}
