/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateconfigurewidgettest.h"
#include "widgets/textautogenerateconfigurewidget.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateConfigureWidgetTest)

TextAutoGenerateConfigureWidgetTest::TextAutoGenerateConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateConfigureWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateConfigureWidget w(nullptr);
    // TODO
}

#include "moc_textautogenerateconfigurewidgettest.cpp"
