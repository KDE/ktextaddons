/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelsearchwidgettest.h"
#include "modelsmanager/ollamamodelsearchwidget.h"
#include "modelsmanager/ollamamodelsinfoscategoriescombobox.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
QTEST_MAIN(OllamaModelSearchWidgetTest)
OllamaModelSearchWidgetTest::OllamaModelSearchWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelSearchWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelSearchWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSearchLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mSearchLineEdit"));
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());

    auto mCategoriesComboBox = w.findChild<OllamaModelsInfosCategoriesComboBox *>(QStringLiteral("mCategoriesComboBox"));
    QVERIFY(mCategoriesComboBox);
}

void OllamaModelSearchWidgetTest::shouldEmitSearchText()
{
    OllamaModelSearchWidget w;
    QSignalSpy searchTextSpy(&w, &OllamaModelSearchWidget::searchText);

    auto mSearchLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mSearchLineEdit"));
    mSearchLineEdit->setText(QStringLiteral("foo"));
    QCOMPARE(searchTextSpy.count(), 1);

    searchTextSpy.clear();
    mSearchLineEdit->clear();
    QCOMPARE(searchTextSpy.count(), 1);
}

#include "moc_ollamamodelsearchwidgettest.cpp"
