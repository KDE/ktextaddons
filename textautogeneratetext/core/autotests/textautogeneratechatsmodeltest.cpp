/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsmodeltest.h"
#include "core/models/textautogeneratechatsmodel.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateChatsModelTest)

TextAutoGenerateChatsModelTest::TextAutoGenerateChatsModelTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateChatsModelTest::shouldHaveDefaultValues()
{
    // TODO
}
#include "moc_textautogeneratechatsmodeltest.cpp"
