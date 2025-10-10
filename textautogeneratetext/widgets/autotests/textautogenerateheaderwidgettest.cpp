/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateheaderwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/textautogenerateheaderwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
#include <qtestmouse.h>
QTEST_MAIN(TextAutoGenerateHeaderWidgetTest)

TextAutoGenerateHeaderWidgetTest::TextAutoGenerateHeaderWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateHeaderWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
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
}

void TextAutoGenerateHeaderWidgetTest::shouldEmitNewChat()
{
    TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
    auto mNewChat = w.findChild<QToolButton *>(u"mNewChat"_s);

    QSignalSpy addNewChatChanged(&w, &TextAutoGenerateText::TextAutoGenerateHeaderWidget::addNewChat);
    QTest::mouseClick(mNewChat, Qt::LeftButton);
    QCOMPARE(addNewChatChanged.count(), 1);
}

void TextAutoGenerateHeaderWidgetTest::shouldEmitChangeFavoriteRequested()
{
    TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
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
