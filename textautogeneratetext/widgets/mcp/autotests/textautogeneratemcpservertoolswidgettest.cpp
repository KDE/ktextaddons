/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemcpservertoolswidgettest.h"
#include "widgets/mcp/textautogeneratemcpservertoolswidget.h"
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateMcpServerToolsWidgetTest)
using namespace Qt::Literals::StringLiterals;
namespace
{
TextAutoGenerateTextMcpProtocolCore::McpServer createServer()
{
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"foo"_s);
    server.createUniqueIdentifier();
    server.setFilterTools(true);
    server.setAllowedTools({u"read_file"_s, u"list_directory"_s});
    return server;
}
}

TextAutoGenerateMcpServerToolsWidgetTest::TextAutoGenerateMcpServerToolsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateMcpServerToolsWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateMcpServerToolsWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mFilterToolsCheckBox = w.findChild<QCheckBox *>(u"mFilterToolsCheckBox"_s);
    QVERIFY(mFilterToolsCheckBox);
    QVERIFY(!mFilterToolsCheckBox->isChecked());
    QVERIFY(!mFilterToolsCheckBox->text().isEmpty());

    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());
    QVERIFY(!mSearchLineEdit->isEnabled());

    auto mToolsListWidget = w.findChild<QListWidget *>(u"mToolsListWidget"_s);
    QVERIFY(mToolsListWidget);
    QCOMPARE(mToolsListWidget->count(), 0);
    QVERIFY(!mToolsListWidget->isEnabled());

    QVERIFY(w.findChild<QPushButton *>(u"selectAllButton"_s));
    QVERIFY(w.findChild<QPushButton *>(u"unselectAllButton"_s));

    auto mStatusLabel = w.findChild<QLabel *>(u"mStatusLabel"_s);
    QVERIFY(mStatusLabel);
    QVERIFY(mStatusLabel->wordWrap());

    QVERIFY(!w.server().filterTools());
    QVERIFY(w.server().allowedTools().isEmpty());
}

void TextAutoGenerateMcpServerToolsWidgetTest::shouldShowAllowedTools()
{
    TextAutoGenerateText::TextAutoGenerateMcpServerToolsWidget w(nullptr);
    const auto server = createServer();
    w.setServer(server);

    auto mFilterToolsCheckBox = w.findChild<QCheckBox *>(u"mFilterToolsCheckBox"_s);
    QVERIFY(mFilterToolsCheckBox->isChecked());
    auto mToolsListWidget = w.findChild<QListWidget *>(u"mToolsListWidget"_s);
    QVERIFY(mToolsListWidget->isEnabled());
    // Without manager list of tools is unknown: only allowed tools are shown
    QCOMPARE(mToolsListWidget->count(), 2);
    QCOMPARE(mToolsListWidget->item(0)->checkState(), Qt::Checked);
    QCOMPARE(mToolsListWidget->item(1)->checkState(), Qt::Checked);
    auto mStatusLabel = w.findChild<QLabel *>(u"mStatusLabel"_s);
    QVERIFY(!mStatusLabel->text().isEmpty());

    QCOMPARE(w.server(), server);
}

void TextAutoGenerateMcpServerToolsWidgetTest::shouldChangeAllowedTools()
{
    TextAutoGenerateText::TextAutoGenerateMcpServerToolsWidget w(nullptr);
    w.setServer(createServer());

    auto mToolsListWidget = w.findChild<QListWidget *>(u"mToolsListWidget"_s);
    mToolsListWidget->item(0)->setCheckState(Qt::Unchecked);
    QCOMPARE(w.server().allowedTools(), QStringList{u"list_directory"_s});

    auto unselectAllButton = w.findChild<QPushButton *>(u"unselectAllButton"_s);
    unselectAllButton->click();
    QVERIFY(w.server().allowedTools().isEmpty());

    auto selectAllButton = w.findChild<QPushButton *>(u"selectAllButton"_s);
    selectAllButton->click();
    QCOMPARE(w.server().allowedTools().count(), 2);

    auto mFilterToolsCheckBox = w.findChild<QCheckBox *>(u"mFilterToolsCheckBox"_s);
    mFilterToolsCheckBox->setChecked(false);
    QVERIFY(!w.server().filterTools());
    QVERIFY(!mToolsListWidget->isEnabled());
}

void TextAutoGenerateMcpServerToolsWidgetTest::shouldFilterListOfTools()
{
    TextAutoGenerateText::TextAutoGenerateMcpServerToolsWidget w(nullptr);
    w.setServer(createServer());

    auto mToolsListWidget = w.findChild<QListWidget *>(u"mToolsListWidget"_s);
    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    mSearchLineEdit->setText(u"READ"_s);
    QVERIFY(!mToolsListWidget->item(0)->isHidden());
    QVERIFY(mToolsListWidget->item(1)->isHidden());

    // Only visible tools are unselected
    auto unselectAllButton = w.findChild<QPushButton *>(u"unselectAllButton"_s);
    unselectAllButton->click();
    QCOMPARE(w.server().allowedTools(), QStringList{u"list_directory"_s});

    mSearchLineEdit->clear();
    QVERIFY(!mToolsListWidget->item(1)->isHidden());
}

#include "moc_textautogeneratemcpservertoolswidgettest.cpp"
