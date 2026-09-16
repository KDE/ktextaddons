/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallmessagewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextinstallmessagewidget.h"
#include <QAction>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>

QTEST_MAIN(WhisperSpeechToTextInstallMessageWidgetTest)
WhisperSpeechToTextInstallMessageWidgetTest::WhisperSpeechToTextInstallMessageWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void WhisperSpeechToTextInstallMessageWidgetTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextInstallMessageWidget w;
    QCOMPARE(w.messageType(), KMessageWidget::MessageType::Error);
    QVERIFY(w.wordWrap());
    QVERIFY(w.text().isEmpty());

    // KMessageWidget::isCloseButtonVisible() reports the visibility of the
    // button itself, so it only answers once the widget is shown.
    w.show();
    QVERIFY(QTest::qWaitForWindowExposed(&w));
    QVERIFY(w.isCloseButtonVisible());

    auto installAction = w.findChild<QAction *>(u"installAction"_s);
    QVERIFY(installAction);
    QCOMPARE(w.actions().count(), 1);
}

void WhisperSpeechToTextInstallMessageWidgetTest::shouldEmitMissingPackages()
{
    WhisperSpeechToTextInstallMessageWidget w;
    QSignalSpy spy(&w, &WhisperSpeechToTextInstallMessageWidget::installPackages);

    auto installAction = w.findChild<QAction *>(u"installAction"_s);
    QVERIFY(installAction);

    // Nothing assigned yet: the widget still relays, with an empty list.
    installAction->trigger();
    QCOMPARE(spy.count(), 1);
    QVERIFY(spy.at(0).at(0).toStringList().isEmpty());

    const QStringList packages{u"numpy"_s, u"torch"_s};
    w.setMissingPackages(packages);
    installAction->trigger();
    QCOMPARE(spy.count(), 2);
    QCOMPARE(spy.at(1).at(0).toStringList(), packages);
}

#include "moc_whisperspeechtotextinstallmessagewidgettest.cpp"
