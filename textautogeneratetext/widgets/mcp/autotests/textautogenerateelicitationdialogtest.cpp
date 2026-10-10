/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateelicitationdialogtest.h"
#include "widgets/mcp/textautogenerateelicitationdialog.h"
#include "widgets/mcp/textautogenerateelicitationwidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateElicitationDialogTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateElicitationDialogTest::TextAutoGenerateElicitationDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateElicitationDialogTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateElicitationDialog d;
    QVERIFY(!d.windowTitle().isEmpty());

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTextAutoGenerateElicitationWidget = d.findChild<TextAutoGenerateText::TextAutoGenerateElicitationWidget *>(u"mTextAutoGenerateElicitationWidget"_s);
    QVERIFY(mTextAutoGenerateElicitationWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);
}
#include "moc_textautogenerateelicitationdialogtest.cpp"
