/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorywidgettest.h"
#include "widgets/tags/textautogenerateselecttagscombobox.h"
#include "widgets/textautogeneratehistorywidget.h"
#include "widgets/view/textautogeneratehistorylistview.h"
#include <QLineEdit>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateHistoryWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateHistoryWidgetTest::TextAutoGenerateHistoryWidgetTest(QWidget *parent)
    : QWidget{parent}
{
}

void TextAutoGenerateHistoryWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateHistoryWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTextAutoGenerateHistoryListView = w.findChild<TextAutoGenerateText::TextAutoGenerateHistoryListView *>("mTextAutoGenerateHistoryListView"_L1);
    QVERIFY(mTextAutoGenerateHistoryListView);

    auto mSearchLineEdit = w.findChild<QLineEdit *>("mSearchLineEdit"_L1);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());

    auto mSelectTagsComboBox = w.findChild<TextAutoGenerateText::TextAutoGenerateSelectTagsComboBox *>("mSelectTagsComboBox"_L1);
    QVERIFY(mSelectTagsComboBox);
    QVERIFY(!mSelectTagsComboBox->toolTip().isEmpty());
    // Without a manager there is no tag to filter with: the combo box is hidden.
    QVERIFY(mSelectTagsComboBox->isHidden());
    QVERIFY(mSelectTagsComboBox->selectedTags().isEmpty());
}

#include "moc_textautogeneratehistorywidgettest.cpp"
