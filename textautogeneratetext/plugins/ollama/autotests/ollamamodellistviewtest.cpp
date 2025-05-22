/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodellistviewtest.h"
#include "modelsmanager/ollamamodellistview.h"
#include <QTest>
QTEST_MAIN(OllamaModelListViewTest)

OllamaModelListViewTest::OllamaModelListViewTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelListViewTest::shouldHaveDefaultValues()
{
    OllamaModelListView view;
    // TODO
}

#include "moc_ollamamodellistviewtest.cpp"
