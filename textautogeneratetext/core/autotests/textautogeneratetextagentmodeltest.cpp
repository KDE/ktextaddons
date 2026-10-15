/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextagentmodeltest.h"
#include "core/models/textautogeneratetextagentmodel.h"
#include <QSignalSpy>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextAgentModelTest)
using namespace Qt::Literals::StringLiterals;

static TextAutoGenerateText::TextAutoGenerateAgent createAgent(const QByteArray &identifier, const QString &name)
{
    TextAutoGenerateText::TextAutoGenerateAgent item;
    item.setIdentifier(identifier);
    item.setName(name);
    return item;
}

TextAutoGenerateTextAgentModelTest::TextAutoGenerateTextAgentModelTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextAgentModelTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextAgentModel model;
    QVERIFY(model.agents().isEmpty());
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateTextAgentModelTest::shouldSetAgents()
{
    TextAutoGenerateText::TextAutoGenerateTextAgentModel model;
    const QSignalSpy resetSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextAgentModel::modelReset);
    model.setAgents({createAgent("foo"_ba, u"bla"_s), createAgent("foo1"_ba, u"bla1"_s)});
    QCOMPARE(resetSpy.count(), 1);
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.agents().at(1).identifier(), "foo1"_ba);

    model.setAgents({});
    QCOMPARE(resetSpy.count(), 2);
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateTextAgentModelTest::shouldAddAgent()
{
    TextAutoGenerateText::TextAutoGenerateTextAgentModel model;
    TextAutoGenerateText::TextAutoGenerateAgent item = createAgent("foo"_ba, u"bla"_s);
    item.setDescription(u"description"_s);

    const QSignalSpy rowsInsertedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextAgentModel::rowsInserted);
    model.addAgent(item);
    QCOMPARE(rowsInsertedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 1);

    const QModelIndex idx = model.index(0, 0);
    QCOMPARE(idx.data(Qt::DisplayRole).toString(), u"bla"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextAgentModel::Name).toString(), u"bla"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextAgentModel::Description).toString(), u"description"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextAgentModel::Identifier).toByteArray(), "foo"_ba);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTextAgentModel::Agent).value<TextAutoGenerateText::TextAutoGenerateAgent>(), item);

    model.addAgent(createAgent("foo1"_ba, u"bla1"_s));
    QCOMPARE(rowsInsertedSpy.count(), 2);
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.agents().at(1).identifier(), "foo1"_ba);
}

void TextAutoGenerateTextAgentModelTest::shouldRemoveAgent()
{
    TextAutoGenerateText::TextAutoGenerateTextAgentModel model;
    model.setAgents({createAgent("foo"_ba, u"bla"_s), createAgent("foo1"_ba, u"bla1"_s)});
    QCOMPARE(model.rowCount(), 2);

    const QSignalSpy rowsRemovedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextAgentModel::rowsRemoved);
    // Unknown identifier => nothing removed
    model.removeAgent("unknown"_ba);
    QCOMPARE(model.rowCount(), 2);

    // Empty identifier => nothing removed
    model.removeAgent({});
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(rowsRemovedSpy.count(), 0);

    model.removeAgent("foo"_ba);
    QCOMPARE(rowsRemovedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.agents().at(0).identifier(), "foo1"_ba);
}

void TextAutoGenerateTextAgentModelTest::shouldUpdateAgent()
{
    TextAutoGenerateText::TextAutoGenerateTextAgentModel model;
    model.setAgents({createAgent("foo"_ba, u"bla"_s), createAgent("foo1"_ba, u"bla1"_s)});

    const QSignalSpy dataChangedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTextAgentModel::dataChanged);
    model.updateAgent(createAgent("foo1"_ba, u"newname"_s));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toModelIndex(), model.index(1, 0));
    QCOMPARE(dataChangedSpy.at(0).at(1).toModelIndex(), model.index(1, 0));
    QCOMPARE(model.agents().at(1).name(), u"newname"_s);
    // Other agent untouched
    QCOMPARE(model.agents().at(0).name(), u"bla"_s);

    // Unknown identifier => nothing changed
    model.updateAgent(createAgent("unknown"_ba, u"foobla"_s));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 2);
}

#include "moc_textautogeneratetextagentmodeltest.cpp"
