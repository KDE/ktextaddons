/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolshowmetadatawidgettest.h"
#include "widgets/configuretoolsplugin/textautogeneratetoolshowmetadatawidget.h"
#include <QTest>
#include <QTextEdit>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateToolShowMetaDataWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateToolShowMetaDataWidgetTest::TextAutoGenerateToolShowMetaDataWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateToolShowMetaDataWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateToolShowMetaDataWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextEdit = w.findChild<QTextEdit *>(u"mTextEdit"_s);
    QVERIFY(mTextEdit);
    QVERIFY(mTextEdit->isReadOnly());
    QVERIFY(mTextEdit->toPlainText().isEmpty());
}

#include "moc_textautogeneratetoolshowmetadatawidgettest.cpp"
