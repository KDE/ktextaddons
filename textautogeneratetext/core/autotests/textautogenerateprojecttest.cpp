/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateprojecttest.h"
#include "core/projects/textautogenerateproject.h"
#include <QColor>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateProjectTest)

using namespace Qt::Literals::StringLiterals;
TextAutoGenerateProjectTest::TextAutoGenerateProjectTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateProjectTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateProject project;
    QVERIFY(!project.identifier().isEmpty());
    QVERIFY(project.name().isEmpty());
    QVERIFY(project.iconName().isEmpty());
}

void TextAutoGenerateProjectTest::shouldSerializeDeserialize()
{
    {
        TextAutoGenerateText::TextAutoGenerateProject project;
        project.setIdentifier("project1");
        project.setName(u"name-project1"_s);
        project.setIconName(u"foo"_s);

        const QByteArray ba = TextAutoGenerateText::TextAutoGenerateProject::serialize(project, false);
        const QJsonDocument doc = QJsonDocument::fromJson(ba);
        QCOMPARE(TextAutoGenerateText::TextAutoGenerateProject::deserialize(doc.object()), project);
    }
    {
        // A project without color keeps an invalid color after a round trip.
        TextAutoGenerateText::TextAutoGenerateProject project;
        project.setIdentifier("project2");
        project.setName(u"name-project2"_s);

        const QByteArray ba = TextAutoGenerateText::TextAutoGenerateProject::serialize(project, false);
        const QJsonDocument doc = QJsonDocument::fromJson(ba);
        const TextAutoGenerateText::TextAutoGenerateProject result = TextAutoGenerateText::TextAutoGenerateProject::deserialize(doc.object());
        QVERIFY(result.iconName().isEmpty());
        QCOMPARE(result, project);
    }
}

#include "moc_textautogenerateprojecttest.cpp"
