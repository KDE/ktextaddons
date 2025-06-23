/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "translatorconfigurelistswidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "translator/widgets/translatorconfigurecombowidget.h"
#include "translator/widgets/translatorconfigurelanguagelistwidget.h"
#include "translator/widgets/translatorconfigurelistswidget.h"
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(TranslatorConfigureListsWidgetTest)
TranslatorConfigureListsWidgetTest::TranslatorConfigureListsWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TranslatorConfigureListsWidgetTest::shouldHaveDefaultValues()
{
    TextTranslator::TranslatorConfigureListsWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mEngineConfigureComboWidget = w.findChild<TextTranslator::TranslatorConfigureComboWidget *>(u"mEngineConfigureComboWidget"_s);
    QVERIFY(mEngineConfigureComboWidget);

    auto mFromLanguageWidget = w.findChild<TextTranslator::TranslatorConfigureLanguageListWidget *>(u"mFromLanguageWidget"_s);
    QVERIFY(mFromLanguageWidget);

    auto mToLanguageWidget = w.findChild<TextTranslator::TranslatorConfigureLanguageListWidget *>(u"mToLanguageWidget"_s);
    QVERIFY(mToLanguageWidget);
}

#include "moc_translatorconfigurelistswidgettest.cpp"
