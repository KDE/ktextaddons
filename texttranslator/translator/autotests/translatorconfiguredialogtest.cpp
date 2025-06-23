/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfiguredialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "translator/widgets/translatorconfiguredialog.h"
#include "translator/widgets/translatorconfigurewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TranslatorConfigureDialogTest)
TranslatorConfigureDialogTest::TranslatorConfigureDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TranslatorConfigureDialogTest::shouldHaveDefaultValues()
{
    TextTranslator::TranslatorConfigureDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTranslatorConfigureWidget = w.findChild<TextTranslator::TranslatorConfigureWidget *>(u"mTranslatorConfigureWidget"_s);
    QVERIFY(mTranslatorConfigureWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

#include "moc_translatorconfiguredialogtest.cpp"
