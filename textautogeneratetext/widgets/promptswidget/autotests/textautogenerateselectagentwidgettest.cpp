/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateselectagentwidgettest.h"
#include "core/models/textautogeneratetextagentmodel.h"
#include "widgets/promptswidget/textautogenerateselectagentlistwidget.h"
#include "widgets/promptswidget/textautogenerateselectagentwidget.h"
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateSelectAgentWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectAgentWidgetTest::TextAutoGenerateSelectAgentWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSelectAgentWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateSelectAgentWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mListWidget = w.findChild<TextAutoGenerateText::TextAutoGenerateSelectAgentListWidget *>(u"mListWidget"_s);
    QVERIFY(mListWidget);

    auto mAgentModel = w.findChild<TextAutoGenerateText::TextAutoGenerateTextAgentModel *>(u"mAgentModel"_s);
    QVERIFY(mAgentModel);
    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());

    auto mFilterProxyModel = w.findChild<QSortFilterProxyModel *>(u"mFilterProxyModel"_s);
    QVERIFY(mFilterProxyModel);
    QCOMPARE(mFilterProxyModel->sourceModel(), mAgentModel);
    QCOMPARE(mListWidget->model(), mFilterProxyModel);
    QVERIFY(w.agents().isEmpty());
}

#include "moc_textautogenerateselectagentwidgettest.cpp"
