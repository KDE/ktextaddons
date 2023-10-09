/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "voskenginedialogtest.h"
#include "voskenginedialog.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(VoskEngineDialogTest)
VoskEngineDialogTest::VoskEngineDialogTest(QObject *parent)
    : QObject{parent}
{
}

void VoskEngineDialogTest::shouldHaveDefaultValues()
{
    VoskEngineDialog w;
    // TODO
}
