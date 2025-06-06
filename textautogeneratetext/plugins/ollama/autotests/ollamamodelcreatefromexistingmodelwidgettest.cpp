/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidgettest.h"
#include "modelsmanager/ollamamodelcreatecombobox.h"
#include "modelsmanager/ollamamodelcreatefromexistingmodelwidget.h"
#include <QDialogButtonBox>
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

    auto mOllamaModelCreateComboBox = w.findChild<OllamaModelCreateComboBox *>(QStringLiteral("mOllamaModelCreateComboBox"));
    QVERIFY(mOllamaModelCreateComboBox);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), {QDialogButtonBox::Ok | QDialogButtonBox::Cancel});

    auto createNewModelButton = buttonBox->button(QDialogButtonBox::Ok);
    QVERIFY(!createNewModelButton->isEnabled());
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldEmitCancelSignal()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);
    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    auto cancelButton = buttonBox->button(QDialogButtonBox::Cancel);
    QSignalSpy spy(&w, &OllamaModelCreateFromExistingModelWidget::cancelRequested);
    QTest::mouseClick(cancelButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldEmitCreateSignal()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);
    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    auto createNewModelButton = buttonBox->button(QDialogButtonBox::Ok);

    auto mOllamaModelCreateComboBox = w.findChild<OllamaModelCreateComboBox *>(QStringLiteral("mOllamaModelCreateComboBox"));
    mOllamaModelCreateComboBox->addItem(QStringLiteral("foo"), QStringLiteral("foo"));

    // Make sure that createButton is Enabled
    auto mModelName = w.findChild<QLineEdit *>(QStringLiteral("mModelName"));
    mModelName->setText(QStringLiteral("fff"));

    QSignalSpy spy(&w, &OllamaModelCreateFromExistingModelWidget::createNewModelDone);
    QTest::mouseClick(createNewModelButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldChangeCreateButtonEnableState()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);
    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    auto createNewModelButton = buttonBox->button(QDialogButtonBox::Ok);
    auto mModelName = w.findChild<QLineEdit *>(QStringLiteral("mModelName"));

    auto mOllamaModelCreateComboBox = w.findChild<OllamaModelCreateComboBox *>(QStringLiteral("mOllamaModelCreateComboBox"));
    mOllamaModelCreateComboBox->addItem(QStringLiteral("foo"), QStringLiteral("foo"));

    QVERIFY(!createNewModelButton->isEnabled());

    mModelName->setText(QStringLiteral("fff"));
    QVERIFY(createNewModelButton->isEnabled());

    mModelName->setText(QStringLiteral("222"));
    QVERIFY(createNewModelButton->isEnabled());

    mModelName->setText({});
    QVERIFY(!createNewModelButton->isEnabled());

    mModelName->setText(QStringLiteral("test"));
    QVERIFY(createNewModelButton->isEnabled());

    mModelName->setText(QStringLiteral(" "));
    QVERIFY(!createNewModelButton->isEnabled());
}

#include "moc_ollamamodelcreatefromexistingmodelwidgettest.cpp"
