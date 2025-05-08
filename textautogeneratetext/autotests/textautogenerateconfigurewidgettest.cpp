/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateconfigurewidgettest.h"
#include "widgets/textautogenerateconfigurewidget.h"
#include <QTest>
QTEST_MAIN(TextAutogenerateConfigureWidgetTest)

TextAutogenerateConfigureWidgetTest::TextAutogenerateConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutogenerateConfigureWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutogenerateConfigureWidget w;
    // TODO
}

#include "moc_textautogenerateconfigurewidgettest.cpp"
