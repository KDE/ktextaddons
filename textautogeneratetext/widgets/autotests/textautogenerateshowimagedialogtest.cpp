/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateshowimagedialogtest.h"
#include "widgets/view/images/textautogenerateshowimagedialog.h"
#include "widgets/view/images/textautogenerateshowimagewidget.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(TextAutoGenerateShowImageDialogTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateShowImageDialogTest::TextAutoGenerateShowImageDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateShowImageDialogTest::shouldHaveDefaultValues()
{
    // TODO
    const TextAutoGenerateText::TextAutoGenerateShowImageDialog d(nullptr);
}

#include "moc_textautogenerateshowimagedialogtest.cpp"
