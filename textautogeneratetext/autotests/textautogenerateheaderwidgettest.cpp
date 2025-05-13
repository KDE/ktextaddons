/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateheaderwidgettest.h"
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
    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mEngineName = w.findChild<QLabel *>(QStringLiteral("mEngineName"));
    QVERIFY(mEngineName);
    QVERIFY(mEngineName->text().isEmpty());

    auto mConfigureEngine = w.findChild<QToolButton *>(QStringLiteral("mConfigureEngine"));
    QVERIFY(mConfigureEngine);
    QVERIFY(mConfigureEngine->autoRaise());
    QVERIFY(!mConfigureEngine->toolTip().isEmpty());

    auto mNewChat = w.findChild<QToolButton *>(QStringLiteral("mNewChat"));
    QVERIFY(mNewChat);
    QVERIFY(mNewChat->autoRaise());
    QVERIFY(!mNewChat->toolTip().isEmpty());

    auto mFavorite = w.findChild<QToolButton *>(QStringLiteral("mFavorite"));
    QVERIFY(mFavorite);
    QVERIFY(mFavorite->autoRaise());
    QVERIFY(mFavorite->isCheckable());
    QVERIFY(!mFavorite->isChecked());
    QVERIFY(!mFavorite->isEnabled());
    QVERIFY(!mFavorite->toolTip().isEmpty());

    auto mSearch = w.findChild<QToolButton *>(QStringLiteral("mSearch"));
    QVERIFY(mSearch);
    QVERIFY(mSearch->autoRaise());
    QVERIFY(!mSearch->toolTip().isEmpty());
}

void TextAutoGenerateHeaderWidgetTest::shouldEmitNewChat()
{
    TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
    auto mNewChat = w.findChild<QToolButton *>(QStringLiteral("mNewChat"));

    QSignalSpy addNewChatChanged(&w, &TextAutoGenerateText::TextAutoGenerateHeaderWidget::addNewChat);
    QTest::mouseClick(mNewChat, Qt::LeftButton);
    QCOMPARE(addNewChatChanged.count(), 1);
}

void TextAutoGenerateHeaderWidgetTest::shouldEmitChangeFavoriteRequested()
{
    TextAutoGenerateText::TextAutoGenerateHeaderWidget w(nullptr);
    auto mFavorite = w.findChild<QToolButton *>(QStringLiteral("mFavorite"));

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
