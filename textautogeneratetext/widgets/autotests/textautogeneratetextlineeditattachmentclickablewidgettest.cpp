/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditattachmentclickablewidgettest.h"
#include "widgets/common/textautogeneratetextlineeditattachmentclickablewidget.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateTextLineEditAttachmentClickableWidgetTest)

TextAutoGenerateTextLineEditAttachmentClickableWidgetTest::TextAutoGenerateTextLineEditAttachmentClickableWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextLineEditAttachmentClickableWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextLineEditAttachmentClickableWidget w;
    // TODO
}

#include "moc_textautogeneratetextlineeditattachmentclickablewidgettest.cpp"
