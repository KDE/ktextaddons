/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemanagetagswidgettest.h"
#include "widgets/tags/textautogeneratemanagetagswidget.h"
#include <QHBoxLayout>
#include <QListView>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateManageTagsWidgetTest)
using namespace Qt::Literals::StringLiterals;
namespace
{
TextAutoGenerateText::TextAutoGenerateTag createTag(const QByteArray &identifier, const QString &name, const QColor &color)
{
    TextAutoGenerateText::TextAutoGenerateTag tag;
    tag.setIdentifier(identifier);
    tag.setName(name);
    tag.setColor(color);
    return tag;
}
}
TextAutoGenerateManageTagsWidgetTest::TextAutoGenerateManageTagsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateManageTagsWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateManageTagsWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto buttonLayout = w.findChild<QVBoxLayout *>(u"buttonLayout"_s);
    QVERIFY(buttonLayout);
    QCOMPARE(buttonLayout->contentsMargins(), QMargins{});

    auto mTagsListView = w.findChild<QListView *>(u"mTagsListView"_s);
    QVERIFY(mTagsListView);
    QVERIFY(mTagsListView->model());
    QCOMPARE(mTagsListView->model()->rowCount(), 0);

    auto mAddButton = w.findChild<QToolButton *>(u"mAddButton"_s);
    QVERIFY(mAddButton);
    QVERIFY(mAddButton->isEnabled());
    QVERIFY(!mAddButton->toolTip().isEmpty());

    auto mModifyButton = w.findChild<QToolButton *>(u"mModifyButton"_s);
    QVERIFY(mModifyButton);
    QVERIFY(!mModifyButton->isEnabled());
    QVERIFY(!mModifyButton->toolTip().isEmpty());

    auto mRemoveButton = w.findChild<QToolButton *>(u"mRemoveButton"_s);
    QVERIFY(mRemoveButton);
    QVERIFY(!mRemoveButton->isEnabled());
    QVERIFY(!mRemoveButton->toolTip().isEmpty());

    QVERIFY(w.tags().isEmpty());
}

void TextAutoGenerateManageTagsWidgetTest::shouldStoreTags()
{
    TextAutoGenerateText::TextAutoGenerateManageTagsWidget w;
    const QList<TextAutoGenerateText::TextAutoGenerateTag> tags{createTag("tag1", u"name-tag1"_s, QColor(Qt::red)),
                                                                createTag("tag2", u"name-tag2"_s, QColor(Qt::blue))};
    w.setTags(tags);

    auto mTagsListView = w.findChild<QListView *>(u"mTagsListView"_s);
    QVERIFY(mTagsListView);
    QCOMPARE(mTagsListView->model()->rowCount(), 2);
    QCOMPARE(w.tags(), tags);
}

void TextAutoGenerateManageTagsWidgetTest::shouldEnableButtonsWhenSelectingTag()
{
    TextAutoGenerateText::TextAutoGenerateManageTagsWidget w;
    w.setTags({createTag("tag1", u"name-tag1"_s, QColor(Qt::red))});

    auto mTagsListView = w.findChild<QListView *>(u"mTagsListView"_s);
    QVERIFY(mTagsListView);
    auto mModifyButton = w.findChild<QToolButton *>(u"mModifyButton"_s);
    QVERIFY(mModifyButton);
    auto mRemoveButton = w.findChild<QToolButton *>(u"mRemoveButton"_s);
    QVERIFY(mRemoveButton);
    QVERIFY(!mModifyButton->isEnabled());
    QVERIFY(!mRemoveButton->isEnabled());

    // WHEN
    mTagsListView->setCurrentIndex(mTagsListView->model()->index(0, 0));

    // THEN
    QVERIFY(mModifyButton->isEnabled());
    QVERIFY(mRemoveButton->isEnabled());

    // WHEN the model is reset, the selection is gone again.
    w.setTags({});

    // THEN
    QVERIFY(!mModifyButton->isEnabled());
    QVERIFY(!mRemoveButton->isEnabled());
}
#include "moc_textautogeneratemanagetagswidgettest.cpp"
