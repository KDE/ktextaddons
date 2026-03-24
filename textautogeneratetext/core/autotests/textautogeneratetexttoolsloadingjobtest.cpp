/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolsloadingjobtest.h"
#include "core/tools/textautogeneratetexttoolsloadingjob.h"
#include <QJsonObject>
#include <QSignalSpy>
#include <QTest>
#include <TextAutoGenerateText/TextAutoGenerateTextToolInternalProperty>
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

    {
        QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> tools;
        {
            TextAutoGenerateText::TextAutoGenerateTextToolInternal tool;
            tool.setToolNameId("calendar_plugin"_ba);
            tool.setDescription(u"bla bla"_s);
            QStringList lst;
            lst << QStringLiteral("calendarinfo") << QStringLiteral("username");
            tool.setRequired(lst);
            QList<TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty> properties;
            {
                TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty property;
                property.setDescription(u"calendar info"_s);
                property.setName(u"calendarinfo"_s);
                property.setTypeElements({u"email"_s});
                properties.append(property);
            }
            {
                TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty property;
                property.setDescription(u"Name of user"_s);
                property.setName(u"username"_s);
                properties.append(property);
            }
            tool.setProperties(properties);
            tools.append(tool);
        }

        QTest::addRow("tools1") << u"tools1"_s << tools;
    }
    {
        QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> tools;
        {
            TextAutoGenerateText::TextAutoGenerateTextToolInternal tool;
            tool.setToolNameId("calendar_plugin"_ba);
            tool.setDescription(u"bla bla"_s);
            QStringList lst;
            lst << QStringLiteral("calendarinfo") << QStringLiteral("username");
            tool.setRequired(lst);
            QList<TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty> properties;
            {
                TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty property;
                property.setDescription(u"calendar info"_s);
                property.setName(u"calendarinfo"_s);
                property.setTypeElements({u"email"_s});
                properties.append(property);
            }
            {
                TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty property;
                property.setDescription(u"Name of user"_s);
                property.setName(u"username"_s);
                properties.append(property);
            }
            tool.setProperties(properties);
            tools.append(tool);
        }
        {
            TextAutoGenerateText::TextAutoGenerateTextToolInternal tool;
            tool.setToolNameId("example_tool"_ba);
            tool.setDescription(u"example"_s);
            QStringList lst;
            lst << QStringLiteral("city");
            tool.setRequired(lst);
            QList<TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty> properties;
            {
                TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty property;
                property.setDescription(u"The name of the city"_s);
                property.setName(u"city"_s);
                properties.append(property);
            }
            tool.setProperties(properties);
            tools.append(tool);
        }

        QTest::addRow("tools2") << u"tools2"_s << tools;
    }
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

#include "moc_textautogeneratetexttoolsloadingjobtest.cpp"
