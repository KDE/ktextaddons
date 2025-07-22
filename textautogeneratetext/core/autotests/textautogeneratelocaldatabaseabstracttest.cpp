/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocaldatabaseabstracttest.h"

#include "core/localdatabase/textautogeneratelocaldatabaseabstract.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateLocalDatabaseAbstractTest)

class TestLocalDatabaseBase : public TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract
{
public:
    explicit TestLocalDatabaseBase(const QString &basePath, TextAutoGenerateLocalDatabaseAbstract::DatabaseType type)
        : TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract(basePath, type)
    {
    }
    ~TestLocalDatabaseBase() override = default;
    [[nodiscard]] QString currentDatabaseName() const
    {
        return databaseName();
    }
};

TextAutoGenerateLocalDatabaseAbstractTest::TextAutoGenerateLocalDatabaseAbstractTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalDatabaseAbstractTest::shouldHaveDefaultValues()
{
    {
        TestLocalDatabaseBase w(u"foo/bla/"_s, TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract::DatabaseType::Chats);
        QCOMPARE(w.currentDatabaseName(), u"chats"_s);
    }
    {
        TestLocalDatabaseBase w(u"foo/bla/"_s, TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract::DatabaseType::Messages);
        QCOMPARE(w.currentDatabaseName(), u"messages"_s);
    }
}

#include "moc_textautogeneratelocaldatabaseabstracttest.cpp"
