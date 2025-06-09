/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanagertest.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateTextInstancesManagerTest)

TextAutoGenerateTextInstancesManagerTest::TextAutoGenerateTextInstancesManagerTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextInstancesManagerTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w;
    QVERIFY(w.instances().isEmpty());
    // TODO
}

#include "moc_textautogeneratetextinstancesmanagertest.cpp"
