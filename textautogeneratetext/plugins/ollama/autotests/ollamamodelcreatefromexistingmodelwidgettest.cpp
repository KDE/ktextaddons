/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidgettest.h"
#include "modelsmanager/ollamamodelcreatefromexistingmodelwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QTest>
QTEST_MAIN(OllamaModelCreateFromExistingModelWidgetTest)
OllamaModelCreateFromExistingModelWidgetTest::OllamaModelCreateFromExistingModelWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);

    auto mModelName = w.findChild<QLineEdit *>(QStringLiteral("mModelName"));
    QVERIFY(mModelName);
    QVERIFY(mModelName->text().isEmpty());
    auto mTagName = w.findChild<QLineEdit *>(QStringLiteral("mTagName"));
    QVERIFY(mTagName);
    QVERIFY(mTagName->text().isEmpty());
    auto mPromptPlainTextEdit = w.findChild<QPlainTextEdit *>(QStringLiteral("mPromptPlainTextEdit"));
    QVERIFY(mPromptPlainTextEdit);
    QVERIFY(mPromptPlainTextEdit->toPlainText().isEmpty());
}

#include "moc_ollamamodelcreatefromexistingmodelwidgettest.cpp"
