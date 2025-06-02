/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancemanagertest.h"
#include "core/textautogeneratetextinstancemanager.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateTextInstanceManagerTest)

TextAutoGenerateTextInstanceManagerTest::TextAutoGenerateTextInstanceManagerTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextInstanceManagerTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextInstanceManager w;
    QVERIFY(w.instances().isEmpty());
    // TODO
}

#include "moc_textautogeneratetextinstancemanagertest.cpp"
