/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskdialogtest.h"
#include "widgets/quickask/textautogeneratequickaskdialog.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(TextAutoGenerateQuickAskDialogTest)

TextAutoGenerateQuickAskDialogTest::TextAutoGenerateQuickAskDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateQuickAskDialogTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateQuickAskDialog d(nullptr);
    // TODO
}

#include "moc_textautogeneratequickaskdialogtest.cpp"
