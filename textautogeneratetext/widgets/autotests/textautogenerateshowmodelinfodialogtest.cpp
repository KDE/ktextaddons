/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateshowmodelinfodialogtest.h"
#include "widgets/common/textautogenerateshowmodelinfodialog.h"
#include "widgets/common/textautogenerateshowmodelinfowidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateShowModelInfoDialogTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateShowModelInfoDialogTest::TextAutoGenerateShowModelInfoDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateShowModelInfoDialogTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateShowModelInfoDialog d(nullptr);
    // TODO in master QVERIFY(!d.windowTitle().isEmpty());
    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTextAutoGenerateShowModelInfoWidget =
        d.findChild<TextAutoGenerateText::TextAutoGenerateShowModelInfoWidget *>(u"mTextAutoGenerateShowModelInfoWidget"_s);
    QVERIFY(mTextAutoGenerateShowModelInfoWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);
}

#include "moc_textautogenerateshowmodelinfodialogtest.cpp"
