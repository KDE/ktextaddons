/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateshowimagewidgettest.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateShowImageWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateShowImageWidgetTest::TextAutoGenerateShowImageWidgetTest(QObject *parent)
    : QObject{parent}
{
}

#include "moc_textautogenerateshowimagewidgettest.cpp"
