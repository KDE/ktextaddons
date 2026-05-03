/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "selecttypecomboboxtest.h"
#include "common/selecttypecombobox.h"
#include <QTest>

QTEST_MAIN(SelectTypeComboBoxTest)

SelectTypeComboBoxTest::SelectTypeComboBoxTest(QObject *parent)
    : QObject{parent}
{
}

void SelectTypeComboBoxTest::shouldHaveDefaultValues()
{
    TextAutoGenerateTextMcpProtocolWidgets::SelectTypeComboBox w;
    // TODO
}
