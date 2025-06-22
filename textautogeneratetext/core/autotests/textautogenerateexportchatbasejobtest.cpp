/*
 * SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateexportchatbasejobtest.h"
#include <QTest>
#include <TextAutoGenerateText/TextAutoGenerateExportChatBaseJob>
QTEST_GUILESS_MAIN(TextAutoGenerateExportChatBaseJobTest)

TextAutoGenerateExportChatBaseJobTest::TextAutoGenerateExportChatBaseJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateExportChatBaseJobTest::shouldVerifyExportChatInfo()
{
    TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo info;
    QVERIFY(info.chatTitle.isEmpty());
    QVERIFY(info.filename.isEmpty());
}

#include "moc_textautogenerateexportchatbasejobtest.cpp"
