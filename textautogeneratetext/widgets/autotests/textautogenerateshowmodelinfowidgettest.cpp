/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateshowmodelinfowidgettest.h"
#include "widgets/common/textautogenerateshowmodelinfowidget.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateShowModelInfoWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateShowModelInfoWidgetTest::TextAutoGenerateShowModelInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateShowModelInfoWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateShowModelInfoWidget w;
    // TODO
}

#include "moc_textautogenerateshowmodelinfowidgettest.cpp"
