/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textreplacewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/textfindreplacewidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTest>

QTEST_MAIN(TextReplaceWidgetTest)
TextReplaceWidgetTest::TextReplaceWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextReplaceWidgetTest::shouldHaveDefaultValues()
{
    TextCustomEditor::TextReplaceWidget w;
    QVERIFY(w.replaceLineEdit());
    auto mReplace = w.findChild<QLineEdit *>(u"mReplace"_s);
    QVERIFY(mReplace);
    QVERIFY(mReplace->isClearButtonEnabled());
    QVERIFY(mReplace->text().isEmpty());

    auto mReplaceBtn = w.findChild<QPushButton *>(u"mReplaceBtn"_s);
    QVERIFY(mReplaceBtn);
    QVERIFY(!mReplaceBtn->text().isEmpty());

    auto mReplaceAllBtn = w.findChild<QPushButton *>(u"mReplaceAllBtn"_s);
    QVERIFY(mReplaceAllBtn);
    QVERIFY(!mReplaceAllBtn->text().isEmpty());
}

#include "moc_textreplacewidgettest.cpp"
