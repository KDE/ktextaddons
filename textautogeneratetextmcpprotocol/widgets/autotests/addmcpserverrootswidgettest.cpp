/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpserverrootswidgettest.h"
#include "client/addmcpserverrootswidget.h"
#include <KEditListWidget>
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(AddMcpServerRootsWidgetTest)

AddMcpServerRootsWidgetTest::AddMcpServerRootsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpServerRootsWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpServerRootsWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mDirectoryLineEdit = w.findChild<QLineEdit *>(u"mDirectoryLineEdit"_s);
    QVERIFY(mDirectoryLineEdit);
    QVERIFY(mDirectoryLineEdit->isClearButtonEnabled());
    QVERIFY(mDirectoryLineEdit->text().isEmpty());

    auto selectDirectoryButton = w.findChild<QToolButton *>(u"selectDirectoryButton"_s);
    QVERIFY(selectDirectoryButton);
    QVERIFY(!selectDirectoryButton->toolTip().isEmpty());

    auto mEditListWidget = w.findChild<KEditListWidget *>(u"mEditListWidget"_s);
    QVERIFY(mEditListWidget);
    QVERIFY(mEditListWidget->items().isEmpty());
    QVERIFY(w.roots().isEmpty());
}

void AddMcpServerRootsWidgetTest::shouldSetRoots()
{
    TextAutoGenerateTextMcpProtocolWidgets::AddMcpServerRootsWidget w;
    const QStringList roots{u"/home/user/project"_s, u"/tmp"_s};
    w.setRoots(roots);
    QCOMPARE(w.roots(), roots);
    w.setRoots({});
    QVERIFY(w.roots().isEmpty());
}

#include "moc_addmcpserverrootswidgettest.cpp"
