/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanagertest.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextInstancesManagerTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextInstancesManagerTest::TextAutoGenerateTextInstancesManagerTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateTextInstancesManagerTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(nullptr);
    QVERIFY(w.instances().isEmpty());
    QVERIFY(w.currentInstance().isEmpty());
    QVERIFY(w.isEmpty());
    QVERIFY(w.textAutoGenerateTextInstanceModel());
    QVERIFY(w.instanceDisplayNames().isEmpty());
    QVERIFY(!w.textAutoGeneratePlugin());
}

void TextAutoGenerateTextInstancesManagerTest::shouldAddInstances()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo1"_ba);
        w.addInstance(instance);
    }

    QVERIFY(!w.isEmpty());
    QCOMPARE(w.instances().count(), 1);
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        w.addInstance(instance);
    }
    QCOMPARE(w.instances().count(), 2);
}

void TextAutoGenerateTextInstancesManagerTest::shouldRemoveInstances()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo1"_ba);
        w.addInstance(instance);
    }
    QVERIFY(!w.isEmpty());
    QCOMPARE(w.instances().count(), 1);

    w.deleteInstance("foo1"_ba);
    QVERIFY(w.isEmpty());

    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        w.addInstance(instance);
    }
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo3"_ba);
        w.addInstance(instance);
    }
    QCOMPARE(w.instances().count(), 2);
}

#include "moc_textautogeneratetextinstancesmanagertest.cpp"
