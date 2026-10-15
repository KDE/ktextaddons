/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextskillmodeltest.h"
#include "core/models/textautogeneratetextskillmodel.h"
#include <QSignalSpy>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextSkillModelTest)
using namespace Qt::Literals::StringLiterals;

static TextAutoGenerateText::TextAutoGenerateSkill createSkill(const QByteArray &identifier, const QString &name)
{
    TextAutoGenerateText::TextAutoGenerateSkill item;
    item.setIdentifier(identifier);
    item.setName(name);
    return item;
}

TextAutoGenerateTextSkillModelTest::TextAutoGenerateTextSkillModelTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextSkillModelTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextSkillModel model;
    QVERIFY(model.skills().isEmpty());
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateTextSkillModelTest::shouldSetSkills()
{
    TextAutoGenerateText::TextAutoGenerateTextSkillModel model;
    const QSignalSpy resetSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextSkillModel::modelReset);
    model.setSkills({createSkill("foo"_ba, u"bla"_s), createSkill("foo1"_ba, u"bla1"_s)});
    QCOMPARE(resetSpy.count(), 1);
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.skills().at(1).identifier(), "foo1"_ba);

    model.setSkills({});
    QCOMPARE(resetSpy.count(), 2);
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateTextSkillModelTest::shouldAddSkill()
{
    TextAutoGenerateText::TextAutoGenerateTextSkillModel model;
    TextAutoGenerateText::TextAutoGenerateSkill item = createSkill("foo"_ba, u"bla"_s);
    item.setDescription(u"description"_s);
    item.setInstructions(u"instructions"_s);

    const QSignalSpy rowsInsertedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextSkillModel::rowsInserted);
    model.addSkill(item);
    QCOMPARE(rowsInsertedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 1);

    const QModelIndex idx = model.index(0, 0);
    QCOMPARE(idx.data(Qt::DisplayRole).toString(), u"bla"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextSkillModel::Name).toString(), u"bla"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextSkillModel::Description).toString(), u"description"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextSkillModel::Instructions).toString(), u"instructions"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextSkillModel::Identifier).toByteArray(), "foo"_ba);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextSkillModel::Skill).value<TextAutoGenerateText::TextAutoGenerateSkill>(), item);

    model.addSkill(createSkill("foo1"_ba, u"bla1"_s));
    QCOMPARE(rowsInsertedSpy.count(), 2);
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.skills().at(1).identifier(), "foo1"_ba);
}

void TextAutoGenerateTextSkillModelTest::shouldRemoveSkill()
{
    TextAutoGenerateText::TextAutoGenerateTextSkillModel model;
    model.setSkills({createSkill("foo"_ba, u"bla"_s), createSkill("foo1"_ba, u"bla1"_s)});
    QCOMPARE(model.rowCount(), 2);

    const QSignalSpy rowsRemovedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextSkillModel::rowsRemoved);
    // Unknown identifier => nothing removed
    model.removeSkill("unknown"_ba);
    QCOMPARE(model.rowCount(), 2);

    // Empty identifier => nothing removed
    model.removeSkill({});
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(rowsRemovedSpy.count(), 0);

    model.removeSkill("foo"_ba);
    QCOMPARE(rowsRemovedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.skills().at(0).identifier(), "foo1"_ba);
}

void TextAutoGenerateTextSkillModelTest::shouldUpdateSkill()
{
    TextAutoGenerateText::TextAutoGenerateTextSkillModel model;
    model.setSkills({createSkill("foo"_ba, u"bla"_s), createSkill("foo1"_ba, u"bla1"_s)});

    const QSignalSpy dataChangedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextSkillModel::dataChanged);
    model.updateSkill(createSkill("foo1"_ba, u"newname"_s));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toModelIndex(), model.index(1, 0));
    QCOMPARE(dataChangedSpy.at(0).at(1).toModelIndex(), model.index(1, 0));
    QCOMPARE(model.skills().at(1).name(), u"newname"_s);
    // Other skill untouched
    QCOMPARE(model.skills().at(0).name(), u"bla"_s);

    // Unknown identifier => nothing changed
    model.updateSkill(createSkill("unknown"_ba, u"foobla"_s));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 2);
}

#include "moc_textautogeneratetextskillmodeltest.cpp"
