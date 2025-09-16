/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolpluginshowmetadatadialogtest.h"
#include "widgets/configuretoolsplugin/textautogeneratetoolpluginshowmetadatadialog.h"
#include "widgets/configuretoolsplugin/textautogeneratetoolpluginshowmetadatawidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateToolPluginShowMetaDataDialogTest)

using namespace Qt::Literals::StringLiterals;
TextAutoGenerateToolPluginShowMetaDataDialogTest::TextAutoGenerateToolPluginShowMetaDataDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateToolPluginShowMetaDataDialogTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateToolPluginShowMetaDataDialog w(nullptr);
    QVERIFY(!w.windowTitle().isEmpty());

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTextAutoGenerateToolPluginShowMetaDataWidget =
        w.findChild<TextAutoGenerateText::TextAutoGenerateToolPluginShowMetaDataWidget *>(u"mTextAutoGenerateToolPluginShowMetaDataWidget"_s);
    QVERIFY(mTextAutoGenerateToolPluginShowMetaDataWidget);

    auto button = w.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);
    QCOMPARE(button->standardButtons(), {QDialogButtonBox::Close});
}

#include "moc_textautogeneratetoolpluginshowmetadatadialogtest.cpp"
