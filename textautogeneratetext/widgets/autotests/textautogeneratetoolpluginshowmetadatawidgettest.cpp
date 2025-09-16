/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolpluginshowmetadatawidgettest.h"
#include "widgets/configuretoolsplugin/textautogeneratetoolpluginshowmetadatawidget.h"
#include <QTest>
#include <QTextEdit>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateToolPluginShowMetaDataWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateToolPluginShowMetaDataWidgetTest::TextAutoGenerateToolPluginShowMetaDataWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateToolPluginShowMetaDataWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateToolPluginShowMetaDataWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextEdit = w.findChild<QTextEdit *>(u"mTextEdit"_s);
    QVERIFY(mTextEdit);
    QVERIFY(mTextEdit->isReadOnly());
    QVERIFY(mTextEdit->toPlainText().isEmpty());
}

#include "moc_textautogeneratetoolpluginshowmetadatawidgettest.cpp"
