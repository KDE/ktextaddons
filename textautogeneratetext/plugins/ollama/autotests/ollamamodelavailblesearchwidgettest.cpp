/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailblesearchwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "modelsmanager/ollamamodelavailablesearchwidget.h"
#include "modelsmanager/ollamamodelsinfoscategoriescombobox.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
QTEST_MAIN(OllamaModelAvailbleSearchWidgetTest)
OllamaModelAvailbleSearchWidgetTest::OllamaModelAvailbleSearchWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelAvailbleSearchWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelAvailableSearchWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());

    auto mCategoriesComboBox = w.findChild<OllamaModelsInfosCategoriesComboBox *>(u"mCategoriesComboBox"_s);
    QVERIFY(mCategoriesComboBox);
}

void OllamaModelAvailbleSearchWidgetTest::shouldEmitSearchText()
{
    OllamaModelAvailableSearchWidget w;
    QSignalSpy searchTextSpy(&w, &OllamaModelAvailableSearchWidget::searchText);

    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    mSearchLineEdit->setText(u"foo"_s);
    QCOMPARE(searchTextSpy.count(), 1);

    searchTextSpy.clear();
    mSearchLineEdit->clear();
    QCOMPARE(searchTextSpy.count(), 1);
}

#include "moc_ollamamodelavailblesearchwidgettest.cpp"
