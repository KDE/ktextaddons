/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpregistryserverdialogtest.h"
#include "client/addmcpregistryserverdialog.h"
#include "client/addmcpregistryserverwidget.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerInfo>
QTEST_MAIN(AddMcpRegistryServerDialogTest)

using namespace Qt::Literals::StringLiterals;
AddMcpRegistryServerDialogTest::AddMcpRegistryServerDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void AddMcpRegistryServerDialogTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpRegistryServerDialog d;
    QVERIFY(!d.windowTitle().isEmpty());
    QVERIFY(!d.serverInfo().isValid());

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mAddMcpRegistryServerWidget = d.findChild<TextAutoGenerateTextMcpProtocolWidgets::AddMcpRegistryServerWidget *>(u"mAddMcpRegistryServerWidget"_s);
    QVERIFY(mAddMcpRegistryServerWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);
    QCOMPARE(button->standardButtons(), QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    QVERIFY(!button->button(QDialogButtonBox::Ok)->isEnabled());
}
#include "moc_addmcpregistryserverdialogtest.cpp"
