/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextpromptmodeltest.h"
#include "core/models/textautogeneratetextpromptmodel.h"
#include <QSignalSpy>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextPromptModelTest)
using namespace Qt::Literals::StringLiterals;

static TextAutoGenerateText::TextAutoGeneratePrompt createPrompt(const QByteArray &identifier, const QString &name)
{
    TextAutoGenerateText::TextAutoGeneratePrompt prompt;
    prompt.setIdentifier(identifier);
    prompt.setName(name);
    return prompt;
}

TextAutoGenerateTextPromptModelTest::TextAutoGenerateTextPromptModelTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextPromptModelTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextPromptModel model;
    QVERIFY(model.prompt().isEmpty());
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateTextPromptModelTest::shouldSetPrompt()
{
    TextAutoGenerateText::TextAutoGenerateTextPromptModel model;
    const QSignalSpy resetSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextPromptModel::modelReset);
    model.setPrompt({createPrompt("foo"_ba, u"bla"_s), createPrompt("foo1"_ba, u"bla1"_s)});
    QCOMPARE(resetSpy.count(), 1);
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.prompt().at(1).identifier(), "foo1"_ba);

    model.setPrompt({});
    QCOMPARE(resetSpy.count(), 2);
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateTextPromptModelTest::shouldAddPrompt()
{
    TextAutoGenerateText::TextAutoGenerateTextPromptModel model;
    TextAutoGenerateText::TextAutoGeneratePrompt prompt = createPrompt("foo"_ba, u"bla"_s);
    prompt.setDescription(u"description"_s);
    prompt.setText(u"text"_s);
    prompt.setEnabled(false);
    prompt.setCategory(TextAutoGenerateText::TextAutoGeneratePrompt::Category::Code);

    const QSignalSpy rowsInsertedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextPromptModel::rowsInserted);
    model.addPrompt(prompt);
    QCOMPARE(rowsInsertedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 1);

    const QModelIndex idx = model.index(0, 0);
    QCOMPARE(idx.data(Qt::DisplayRole).toString(), u"bla"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextPromptModel::Name).toString(), u"bla"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextPromptModel::Description).toString(), u"description"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextPromptModel::PromptText).toString(), u"text"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextPromptModel::Enabled).toBool(), false);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextPromptModel::Identifier).toByteArray(), "foo"_ba);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextPromptModel::Category).value<TextAutoGenerateText::TextAutoGeneratePrompt::Category>(),
             TextAutoGenerateText::TextAutoGeneratePrompt::Category::Code);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextPromptModel::Prompt).value<TextAutoGenerateText::TextAutoGeneratePrompt>(), prompt);

    model.addPrompt(createPrompt("foo1"_ba, u"bla1"_s));
    QCOMPARE(rowsInsertedSpy.count(), 2);
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.prompt().at(1).identifier(), "foo1"_ba);
}

void TextAutoGenerateTextPromptModelTest::shouldRemovePrompt()
{
    TextAutoGenerateText::TextAutoGenerateTextPromptModel model;
    model.setPrompt({createPrompt("foo"_ba, u"bla"_s), createPrompt("foo1"_ba, u"bla1"_s)});
    QCOMPARE(model.rowCount(), 2);

    const QSignalSpy rowsRemovedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextPromptModel::rowsRemoved);
    // Unknown identifier => nothing removed
    model.removePrompt("unknown"_ba);
    QCOMPARE(model.rowCount(), 2);

    // Empty identifier => nothing removed
    model.removePrompt({});
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(rowsRemovedSpy.count(), 0);

    model.removePrompt("foo"_ba);
    QCOMPARE(rowsRemovedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.prompt().at(0).identifier(), "foo1"_ba);
}

void TextAutoGenerateTextPromptModelTest::shouldUpdatePrompt()
{
    TextAutoGenerateText::TextAutoGenerateTextPromptModel model;
    model.setPrompt({createPrompt("foo"_ba, u"bla"_s), createPrompt("foo1"_ba, u"bla1"_s)});

    const QSignalSpy dataChangedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextPromptModel::dataChanged);
    TextAutoGenerateText::TextAutoGeneratePrompt updated = createPrompt("foo1"_ba, u"newname"_s);
    updated.setEnabled(false);
    model.updatePrompt(updated);
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toModelIndex(), model.index(1, 0));
    QCOMPARE(dataChangedSpy.at(0).at(1).toModelIndex(), model.index(1, 0));
    QCOMPARE(model.prompt().at(1).name(), u"newname"_s);
    QVERIFY(!model.prompt().at(1).enabled());
    // Other prompt untouched
    QCOMPARE(model.prompt().at(0).name(), u"bla"_s);

    // Unknown identifier => nothing changed
    model.updatePrompt(createPrompt("unknown"_ba, u"foobla"_s));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 2);
}

#include "moc_textautogeneratetextpromptmodeltest.cpp"
