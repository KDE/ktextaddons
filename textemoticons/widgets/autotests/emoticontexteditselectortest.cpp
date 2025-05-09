/*
  SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticontexteditselectortest.h"
#include "emoticoncategorybuttons.h"
#include "emoticonlistview.h"
#include "emoticontexteditselector.h"
#include "emoticontonecombobox.h"
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
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mCategoryButtons = w.findChild<TextEmoticonsWidgets::EmoticonCategoryButtons *>(QStringLiteral("mCategoryButtons"));
    QVERIFY(mCategoryButtons);

    auto mEmoticonListView = w.findChild<TextEmoticonsWidgets::EmoticonListView *>(QStringLiteral("mEmoticonListView"));
    QVERIFY(mEmoticonListView);

    auto mSearchUnicodeLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mSearchUnicodeLineEdit"));
    QVERIFY(mSearchUnicodeLineEdit);
    QVERIFY(mSearchUnicodeLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchUnicodeLineEdit->text().isEmpty());
    QVERIFY(!mSearchUnicodeLineEdit->placeholderText().isEmpty());

    auto emoticonTonComboBox = w.findChild<TextEmoticonsWidgets::EmoticonToneComboBox *>(QStringLiteral("emoticonToneComboBox"));
    QVERIFY(emoticonTonComboBox);

    QVERIFY(!w.customEmojiSupport());
}

#include "moc_emoticontexteditselectortest.cpp"
