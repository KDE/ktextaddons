/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidgettest.h"
#include "modelsmanager/ollamamodelcreatefromexistingmodelwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSignalSpy>
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

    auto cancelButton = w.findChild<QPushButton *>(QStringLiteral("cancelButton"));
    QVERIFY(cancelButton);
    QVERIFY(!cancelButton->text().isEmpty());

    auto createNewModelButton = w.findChild<QPushButton *>(QStringLiteral("createNewModelButton"));
    QVERIFY(createNewModelButton);
    QVERIFY(!createNewModelButton->text().isEmpty());
    QVERIFY(!createNewModelButton->isEnabled());
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldEmitCancelSignal()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);
    auto cancelButton = w.findChild<QPushButton *>(QStringLiteral("cancelButton"));
    QSignalSpy spy(&w, &OllamaModelCreateFromExistingModelWidget::cancelRequested);
    QTest::mouseClick(cancelButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldEmitCreateSignal()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);
    auto createNewModelButton = w.findChild<QPushButton *>(QStringLiteral("createNewModelButton"));
    QSignalSpy spy(&w, &OllamaModelCreateFromExistingModelWidget::createNewModelRequested);
    QTest::mouseClick(createNewModelButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

#include "moc_ollamamodelcreatefromexistingmodelwidgettest.cpp"
