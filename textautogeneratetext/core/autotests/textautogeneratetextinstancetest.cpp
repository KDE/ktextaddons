/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancetest.h"
#include "core/textautogeneratetextinstance.h"
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextInstanceTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextInstanceTest::TextAutoGenerateTextInstanceTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateTextInstanceTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextInstance w;
    QVERIFY(w.pluginName().isEmpty());
    QVERIFY(w.instanceUuid().isEmpty());
    QVERIFY(w.pluginIdentifier().isEmpty());
    QVERIFY(w.currentModel().isEmpty());
    QVERIFY(!w.isValid());
    QVERIFY(w.enabled());
}

void TextAutoGenerateTextInstanceTest::shouldInstanceWillBeValid()
{
    TextAutoGenerateText::TextAutoGenerateTextInstance w;
    w.setPluginIdentifier(u"ide"_s);
    QVERIFY(!w.isValid());

    w.setInstanceUuid("inst_uuid"_ba);
    QVERIFY(!w.isValid());

    w.setPluginName(u"plugin_n"_s);
    QVERIFY(w.isValid());
}

#include "moc_textautogeneratetextinstancetest.cpp"
