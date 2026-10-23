/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpregistryservermodeltest.h"
#include "models/mcpregistryservermodel.h"
#include <QSignalSpy>
#include <QTest>
QTEST_GUILESS_MAIN(McpRegistryServerModelTest)

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpRegistryServerModelTest::McpRegistryServerModelTest(QObject *parent)
    : QObject{parent}
{
}

void McpRegistryServerModelTest::shouldHaveDefaultValues()
{
    const McpRegistryServerModel m;
    QCOMPARE(m.rowCount(), 0);
    QVERIFY(!m.serverInfo(0).isValid());
}

void McpRegistryServerModelTest::shouldAppendServers()
{
    McpRegistryServerModel m;
    McpRegistryServerInfo a;
    a.setName(u"io.github.foo/a"_s);
    a.setDescription(u"A"_s);
    McpRegistryServerInfo b;
    b.setName(u"io.github.foo/b"_s);
    b.setTitle(u"B title"_s);

    m.setServers({a});
    QCOMPARE(m.rowCount(), 1);

    QSignalSpy rowsInserted(&m, &QAbstractItemModel::rowsInserted);
    m.appendServers({b});
    QCOMPARE(rowsInserted.count(), 1);
    QCOMPARE(m.rowCount(), 2);
    QCOMPARE(m.index(0).data(Qt::DisplayRole).toString(), u"io.github.foo/a"_s);
    QCOMPARE(m.index(0).data(McpRegistryServerModel::Description).toString(), u"A"_s);
    QCOMPARE(m.index(1).data(Qt::DisplayRole).toString(), u"B title"_s);
    QCOMPARE(m.serverInfo(1).name(), u"io.github.foo/b"_s);

    m.appendServers({});
    QCOMPARE(rowsInserted.count(), 1);

    m.clear();
    QCOMPARE(m.rowCount(), 0);
}

void McpRegistryServerModelTest::shouldReturnFirstIconUrl()
{
    McpRegistryServerModel m;
    McpRegistryServerInfo a;
    a.setName(u"io.github.foo/a"_s);
    a.setIcons({{u"https://foo.example.com/first.png"_s, u"image/png"_s}, {u"https://foo.example.com/second.svg"_s, u"image/svg+xml"_s}});
    McpRegistryServerInfo b;
    b.setName(u"io.github.foo/b"_s);

    m.setServers({a, b});
    QCOMPARE(m.index(0).data(McpRegistryServerModel::IconUrl).toString(), u"https://foo.example.com/first.png"_s);
    QVERIFY(m.index(1).data(McpRegistryServerModel::IconUrl).toString().isEmpty());
}
#include "moc_mcpregistryservermodeltest.cpp"
