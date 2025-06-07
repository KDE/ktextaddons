/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskwidgettest.h"
#include "widgets/quickask/textautogeneratequickaskwidget.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateQuickAskWidgetTest)
TextAutoGenerateQuickAskWidgetTest::TextAutoGenerateQuickAskWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateQuickAskWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateQuickAskWidget w(nullptr);
    // TODO
}
