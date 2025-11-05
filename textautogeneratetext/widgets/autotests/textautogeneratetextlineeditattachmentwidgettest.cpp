/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditattachmentwidgettest.h"
#include "widgets/common/textautogeneratetextlineeditattachmentwidget.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(TextAutoGenerateTextLineEditAttachmentWidgetTest)
TextAutoGenerateTextLineEditAttachmentWidgetTest::TextAutoGenerateTextLineEditAttachmentWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextLineEditAttachmentWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextLineEditAttachmentWidget w;
    // TODO
}

#include "moc_textautogeneratetextlineeditattachmentwidgettest.cpp"
