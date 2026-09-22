/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemanagetagsdialogtest.h"
#include "widgets/tags/textautogeneratemanagetagsdialog.h"
#include "widgets/tags/textautogeneratemanagetagswidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateManageTagsDialogTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateManageTagsDialogTest::TextAutoGenerateManageTagsDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateManageTagsDialogTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateManageTagsDialog d;
    QVERIFY(!d.windowTitle().isEmpty());

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mManageTagsWidget = d.findChild<TextAutoGenerateText::TextAutoGenerateManageTagsWidget *>(u"mManageTagsWidget"_s);
    QVERIFY(mManageTagsWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);

    QVERIFY(d.tags().isEmpty());
}

void TextAutoGenerateManageTagsDialogTest::shouldStoreTags()
{
    TextAutoGenerateText::TextAutoGenerateManageTagsDialog d;
    TextAutoGenerateText::TextAutoGenerateTag tag;
    tag.setIdentifier("tag1");
    tag.setName(u"name-tag1"_s);
    tag.setColor(QColor(Qt::red));
    const QList<TextAutoGenerateText::TextAutoGenerateTag> tags{tag};
    d.setTags(tags);
    QCOMPARE(d.tags(), tags);
}
#include "moc_textautogeneratemanagetagsdialogtest.cpp"
