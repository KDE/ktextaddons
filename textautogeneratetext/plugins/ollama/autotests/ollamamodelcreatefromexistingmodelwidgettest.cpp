/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidgettest.h"
#include "modelsmanager/ollamamodelcreatefromexistingmodelwidget.h"
#include <QFormLayout>
#include <QTest>
QTEST_MAIN(OllamaModelCreateFromExistingModelWidgetTest)
OllamaModelCreateFromExistingModelWidgetTest::OllamaModelCreateFromExistingModelWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);
    // TODO
}

#include "moc_ollamamodelcreatefromexistingmodelwidgettest.cpp"
