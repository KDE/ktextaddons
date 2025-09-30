/*
  SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticontexteditselectortest.h"
using namespace Qt::Literals::StringLiterals;

#include "emojicategorybuttons.h"
#include "emojilistview.h"
#include "emojitonecombobox.h"
#include "emoticontexteditselector.h"
#include <QLineEdit>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(EmoticonTextEditSelectorTest)

EmoticonTextEditSelectorTest::EmoticonTextEditSelectorTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void EmoticonTextEditSelectorTest::shouldHaveDefaultValues()
{
    TextEmoticonsWidgets::EmoticonTextEditSelector w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mCategoryButtons = w.findChild<TextEmoticonsWidgets::EmojiCategoryButtons *>(u"mCategoryButtons"_s);
    QVERIFY(mCategoryButtons);

    auto mEmoticonListView = w.findChild<TextEmoticonsWidgets::EmojiListView *>(u"mEmoticonListView"_s);
    QVERIFY(mEmoticonListView);

    auto mSearchUnicodeLineEdit = w.findChild<QLineEdit *>(u"mSearchUnicodeLineEdit"_s);
    QVERIFY(mSearchUnicodeLineEdit);
    QVERIFY(mSearchUnicodeLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchUnicodeLineEdit->text().isEmpty());
    QVERIFY(!mSearchUnicodeLineEdit->placeholderText().isEmpty());

    auto emoticonTonComboBox = w.findChild<TextEmoticonsWidgets::EmojiToneComboBox *>(u"emoticonToneComboBox"_s);
    QVERIFY(emoticonTonComboBox);

    QVERIFY(!w.customEmojiSupport());
}

#include "moc_emoticontexteditselectortest.cpp"
