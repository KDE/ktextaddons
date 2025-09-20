/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatefromexistingmodelwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "modelsmanager/ollamamodelcreatecombobox.h"
#include "modelsmanager/ollamamodelcreatefromexistingmodelwidget.h"
#include <QDialogButtonBox>
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

    auto mModelName = w.findChild<QLineEdit *>(u"mModelName"_s);
    QVERIFY(mModelName);
    QVERIFY(mModelName->text().isEmpty());
    auto mTagName = w.findChild<QLineEdit *>(u"mTagName"_s);
    QVERIFY(mTagName);
    QVERIFY(mTagName->text().isEmpty());
    auto mPromptPlainTextEdit = w.findChild<QPlainTextEdit *>(u"mPromptPlainTextEdit"_s);
    QVERIFY(mPromptPlainTextEdit);
    QVERIFY(mPromptPlainTextEdit->toPlainText().isEmpty());

    auto mOllamaModelCreateComboBox = w.findChild<OllamaModelCreateComboBox *>(u"mOllamaModelCreateComboBox"_s);
    QVERIFY(mOllamaModelCreateComboBox);

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), {QDialogButtonBox::Ok | QDialogButtonBox::Cancel});

    auto createNewModelButton = buttonBox->button(QDialogButtonBox::Ok);
    QVERIFY(!createNewModelButton->isEnabled());
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldEmitCancelSignal()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);
    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    auto cancelButton = buttonBox->button(QDialogButtonBox::Cancel);
    QSignalSpy spy(&w, &OllamaModelCreateFromExistingModelWidget::cancelRequested);
    QTest::mouseClick(cancelButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldEmitCreateSignal()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);
    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    auto createNewModelButton = buttonBox->button(QDialogButtonBox::Ok);

    auto mOllamaModelCreateComboBox = w.findChild<OllamaModelCreateComboBox *>(u"mOllamaModelCreateComboBox"_s);
    mOllamaModelCreateComboBox->addItem(u"foo"_s, u"foo"_s);

    // Make sure that createButton is Enabled
    auto mModelName = w.findChild<QLineEdit *>(u"mModelName"_s);
    mModelName->setText(u"fff"_s);

    QSignalSpy spy(&w, &OllamaModelCreateFromExistingModelWidget::createNewModelDone);
    QTest::mouseClick(createNewModelButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

void OllamaModelCreateFromExistingModelWidgetTest::shouldChangeCreateButtonEnableState()
{
    OllamaModelCreateFromExistingModelWidget w(nullptr);
    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    auto createNewModelButton = buttonBox->button(QDialogButtonBox::Ok);
    auto mModelName = w.findChild<QLineEdit *>(u"mModelName"_s);

    auto mOllamaModelCreateComboBox = w.findChild<OllamaModelCreateComboBox *>(u"mOllamaModelCreateComboBox"_s);
    mOllamaModelCreateComboBox->addItem(u"foo"_s, u"foo"_s);

    QVERIFY(!createNewModelButton->isEnabled());

    mModelName->setText(u"fff"_s);
    QVERIFY(createNewModelButton->isEnabled());

    mModelName->setText(u"222"_s);
    QVERIFY(createNewModelButton->isEnabled());

    mModelName->setText({});
    QVERIFY(!createNewModelButton->isEnabled());

    mModelName->setText(u"test"_s);
    QVERIFY(createNewModelButton->isEnabled());

    mModelName->setText(u" "_s);
    QVERIFY(!createNewModelButton->isEnabled());
}

#include "moc_ollamamodelcreatefromexistingmodelwidgettest.cpp"
