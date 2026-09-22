/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateselecttagscomboboxtest.h"
#include "widgets/tags/textautogenerateselecttagscombobox.h"
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
QTEST_MAIN(TextAutoGenerateSelectTagsComboBoxTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

namespace
{
[[nodiscard]] QList<TextAutoGenerateTag> generateTags()
{
    TextAutoGenerateTag first;
    first.setIdentifier("id1");
    first.setName(u"tag1"_s);
    first.setColor(Qt::red);

    TextAutoGenerateTag second;
    second.setIdentifier("id2");
    second.setName(u"tag2"_s);
    second.setColor(Qt::blue);

    return {first, second};
}
}

TextAutoGenerateSelectTagsComboBoxTest::TextAutoGenerateSelectTagsComboBoxTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSelectTagsComboBoxTest::shouldHaveDefaultValues()
{
    TextAutoGenerateSelectTagsComboBox w;
    QCOMPARE(w.count(), 0);
    QVERIFY(w.selectedTags().isEmpty());
    // Not editable for the user: the line edit only shows the selection.
    QVERIFY(w.lineEdit()->isReadOnly());
}

void TextAutoGenerateSelectTagsComboBoxTest::shouldFillTags()
{
    TextAutoGenerateSelectTagsComboBox w;
    const QList<TextAutoGenerateTag> tags = generateTags();
    w.setTags(tags);
    QCOMPARE(w.count(), tags.count());
    for (int i = 0; i < w.count(); ++i) {
        QCOMPARE(w.itemText(i), tags.at(i).name());
        QCOMPARE(w.itemData(i).toByteArray(), tags.at(i).identifier());
        QCOMPARE(w.itemData(i, Qt::CheckStateRole).value<Qt::CheckState>(), Qt::Unchecked);
        QVERIFY(!w.itemIcon(i).isNull());
    }
    QVERIFY(w.selectedTags().isEmpty());
}

void TextAutoGenerateSelectTagsComboBoxTest::shouldSelectTags()
{
    TextAutoGenerateSelectTagsComboBox w;
    w.setTags(generateTags());

    QSignalSpy spy(&w, &TextAutoGenerateSelectTagsComboBox::selectedTagsChanged);
    const QList<QByteArray> identifiers{"id2"};
    w.setSelectedTags(identifiers);
    // One signal for the whole selection, not one per item.
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<QList<QByteArray>>(), identifiers);
    QCOMPARE(w.selectedTags(), identifiers);
    // The selection is shown as a tool tip on the line edit, so that the tool tip of the combo box
    // itself stays available to the caller.
    QVERIFY(!w.lineEdit()->toolTip().isEmpty());
    QVERIFY(w.toolTip().isEmpty());

    w.setSelectedTags({});
    QVERIFY(w.lineEdit()->toolTip().isEmpty());
    QCOMPARE(spy.count(), 2);
    QVERIFY(w.selectedTags().isEmpty());

    // An unknown identifier selects nothing.
    w.setSelectedTags({"unknown"});
    QCOMPARE(spy.count(), 3);
    QVERIFY(w.selectedTags().isEmpty());
}

void TextAutoGenerateSelectTagsComboBoxTest::shouldClearSelectionWhenSettingTags()
{
    TextAutoGenerateSelectTagsComboBox w;
    w.setTags(generateTags());
    w.setSelectedTags({"id1"});
    QCOMPARE(w.selectedTags(), QList<QByteArray>{"id1"});

    QSignalSpy spy(&w, &TextAutoGenerateSelectTagsComboBox::selectedTagsChanged);
    w.setTags(generateTags());
    QCOMPARE(spy.count(), 1);
    QVERIFY(spy.at(0).at(0).value<QList<QByteArray>>().isEmpty());
    QVERIFY(w.selectedTags().isEmpty());
}

#include "moc_textautogenerateselecttagscomboboxtest.cpp"
