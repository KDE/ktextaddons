/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateheaderwidgettest.h"

#include "widgets/textautogenerateheaderwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>
#include <QToolButton>
#include <qtestmouse.h>
QTEST_MAIN(TextAutoGenerateHeaderWidgetTest)

using namespace Qt::Literals::StringLiterals;
TextAutoGenerateHeaderWidgetTest::TextAutoGenerateHeaderWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateHeaderWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mEngineName = w.findChild<QLabel *>(u"mEngineName"_s);
    QVERIFY(mEngineName);
    QVERIFY(mEngineName->text().isEmpty());

    auto mNewChat = w.findChild<QToolButton *>(u"mNewChat"_s);
    QVERIFY(mNewChat);
    QVERIFY(mNewChat->autoRaise());
    QVERIFY(!mNewChat->toolTip().isEmpty());

    auto mFavorite = w.findChild<QToolButton *>(u"mFavorite"_s);
    QVERIFY(mFavorite);
    QVERIFY(mFavorite->autoRaise());
    QVERIFY(mFavorite->isCheckable());
    QVERIFY(!mFavorite->isChecked());
    QVERIFY(!mFavorite->isEnabled());
    QVERIFY(!mFavorite->toolTip().isEmpty());

    auto mSearch = w.findChild<QToolButton *>(u"mSearch"_s);
    QVERIFY(mSearch);
    QVERIFY(mSearch->autoRaise());
    QVERIFY(mSearch->isCheckable());
    QVERIFY(!mSearch->isChecked());
    QVERIFY(!mSearch->toolTip().isEmpty());

    auto mSaveQuickAskButton = w.findChild<QToolButton *>(u"mSaveQuickAskButton"_s);
    QVERIFY(mSaveQuickAskButton);
    QVERIFY(mSaveQuickAskButton->autoRaise());
    QVERIFY(!mSaveQuickAskButton->toolTip().isEmpty());

    auto mNewEphemeralChat = w.findChild<QToolButton *>(u"mNewEphemeralChat"_s);
    QVERIFY(mNewEphemeralChat);
    QVERIFY(mNewEphemeralChat->autoRaise());
    QVERIFY(!mNewEphemeralChat->toolTip().isEmpty());
}

void TextAutoGenerateHeaderWidgetTest::shouldEmitNewEphemeralChat()
{
    const TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
    auto mNewEphemeralChat = w.findChild<QToolButton *>(u"mNewEphemeralChat"_s);

    const QSignalSpy addNewEphemeralChatChanged(&w, &TextAutoGenerateText::TextAutoGenerateHeaderWidget::addNewEphemeralChat);
    QTest::mouseClick(mNewEphemeralChat, Qt::LeftButton);
    QCOMPARE(addNewEphemeralChatChanged.count(), 1);
}

void TextAutoGenerateHeaderWidgetTest::shouldEmitNewChat()
{
    const TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
    auto mNewChat = w.findChild<QToolButton *>(u"mNewChat"_s);

    const QSignalSpy addNewChatChanged(&w, &TextAutoGenerateText::TextAutoGenerateHeaderWidget::addNewChat);
    QTest::mouseClick(mNewChat, Qt::LeftButton);
    QCOMPARE(addNewChatChanged.count(), 1);
}

void TextAutoGenerateHeaderWidgetTest::shouldEmitSaveInDatabase()
{
    const TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
    auto mSaveQuickAskButton = w.findChild<QToolButton *>(u"mSaveQuickAskButton"_s);

    const QSignalSpy saveInDatabaseChanged(&w, &TextAutoGenerateText::TextAutoGenerateHeaderWidget::saveInDataseRequested);
    QTest::mouseClick(mSaveQuickAskButton, Qt::LeftButton);
    QCOMPARE(saveInDatabaseChanged.count(), 1);
}

void TextAutoGenerateHeaderWidgetTest::shouldEmitChangeFavoriteRequested()
{
    const TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
    auto mFavorite = w.findChild<QToolButton *>(u"mFavorite"_s);

    // Force enable for testing
    mFavorite->setEnabled(true);

    QSignalSpy changeFavoriteRequested(&w, &TextAutoGenerateText::TextAutoGenerateHeaderWidget::changeFavoriteRequested);
    QTest::mouseClick(mFavorite, Qt::LeftButton);
    QCOMPARE(changeFavoriteRequested.count(), 1);
    QVERIFY(changeFavoriteRequested.at(0).at(0).toBool());

    changeFavoriteRequested.clear();
    QTest::mouseClick(mFavorite, Qt::LeftButton);
    QCOMPARE(changeFavoriteRequested.count(), 1);
    QVERIFY(!changeFavoriteRequested.at(0).at(0).toBool());

    changeFavoriteRequested.clear();
    mFavorite->setChecked(true);
    QTest::mouseClick(mFavorite, Qt::LeftButton);
    QCOMPARE(changeFavoriteRequested.count(), 1);
    QVERIFY(!changeFavoriteRequested.at(0).at(0).toBool());
}

#include "moc_textautogenerateheaderwidgettest.cpp"
