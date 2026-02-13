/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonsettingstest.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaCommonSettingsTest)

OllamaCommonSettingsTest::OllamaCommonSettingsTest(QObject *parent)
    : QObject{parent}
{
}

#include "moc_ollamacommonsettingstest.cpp"
