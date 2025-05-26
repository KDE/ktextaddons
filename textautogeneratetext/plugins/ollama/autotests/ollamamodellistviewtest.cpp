/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodellistviewtest.h"
#include "modelsmanager/ollamamodelavailablelistview.h"
#include <QTest>
QTEST_MAIN(OllamaModelListViewTest)

OllamaModelListViewTest::OllamaModelListViewTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelListViewTest::shouldHaveDefaultValues()
{
    OllamaModelAvailableListView view;
    // TODO
}

#include "moc_ollamamodellistviewtest.cpp"
