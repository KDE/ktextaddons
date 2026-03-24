/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolsloadingjobtest.h"
#include "core/tools/textautogeneratetexttoolsloadingjob.h"
#include <QJsonObject>
#include <QSignalSpy>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateTextToolsLoadingJobTest)

TextAutoGenerateTextToolsLoadingJobTest::TextAutoGenerateTextToolsLoadingJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolsLoadingJobTest::shouldLoadTools_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<const QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal>>("tools");
}

void TextAutoGenerateTextToolsLoadingJobTest::shouldLoadTools()
{
    QFETCH(QString, name);
    QFETCH(const QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal>, tools);
    const QString originalJsonFile = QLatin1StringView(TEXTAUTOGENERATE_DATA_DIR) + "/json/tools/"_L1 + name + ".json"_L1;

    TextAutoGenerateText::TextAutoGenerateTextToolsLoadingJob job;
    job.setFileName(originalJsonFile);
    const QSignalSpy spy(&job, &TextAutoGenerateText::TextAutoGenerateTextToolsLoadingJob::tools);
    job.start();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal>>(), tools);
}
