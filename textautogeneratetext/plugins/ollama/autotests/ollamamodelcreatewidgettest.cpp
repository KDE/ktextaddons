/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatewidgettest.h"
#include "modelsmanager/ollamamodelcreatewidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaModelCreateWidgetTest)

OllamaModelCreateWidgetTest::OllamaModelCreateWidgetTest(QObject *parent)
    : QObject{parent}
{
}

OllamaModelCreateWidgetTest::~OllamaModelCreateWidgetTest()
{
    OllamaModelCreateWidget w(nullptr);
    // TODO
}

#include "moc_ollamamodelcreatewidgettest.cpp"
