/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "loaddialogsizeutilstest.h"
#include <KConfigGroup>
#include <KPageDialog>
#include <KSharedConfig>
#include <QDialog>
#include <QElapsedTimer>
#include <QLabel>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTest>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(LoadDialogSizeUtilsTest)

namespace
{
const QSize defaultSize(400, 300);

bool hasStoredSize(QLatin1StringView group)
{
    return KSharedConfig::openStateConfig()->hasGroup(group);
}

void removeStoredSize(QLatin1StringView group)
{
    KSharedConfig::openStateConfig()->deleteGroup(group);
    KSharedConfig::openStateConfig()->sync();
}

// A resize issued right after the window appeared can be dropped by the compositor,
// and Qt never retries it, so ask again until the platform window really took the new
// size. Without this the size stored when the dialog goes away is still the old one.
void resizeAndWait(QWidget *w, QSize size)
{
    QElapsedTimer timer;
    timer.start();
    while (timer.elapsed() < 5000 && (w->size() != size || w->windowHandle()->size() != size)) {
        w->resize(size);
        QTest::qWait(20);
    }
    QCOMPARE(w->size(), size);
    QCOMPARE(w->windowHandle()->size(), size);
}

// Reopens a managed dialog on the same group and returns the size it got back.
QSize reopenedSize(QLatin1StringView group)
{
    QDialog dialog;
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
    dialog.show();
    if (!QTest::qWaitForWindowExposed(&dialog)) {
        return {};
    }
    return dialog.size();
}
}

LoadDialogSizeUtilsTest::LoadDialogSizeUtilsTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void LoadDialogSizeUtilsTest::shouldNotStoreSizeWhenDialogNeverShown()
{
    const auto group = QLatin1StringView("UtilsNeverShown");
    removeStoredSize(group);
    // A dialog which was never shown has no size worth storing, and saying so is not a bug.
    QTest::failOnWarning(QRegularExpression(u"windowHandle not defined"_s));
    {
        QDialog dialog;
        TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
    }
    QVERIFY(!hasStoredSize(group));
}

void LoadDialogSizeUtilsTest::shouldNotStoreSizeWhenWindowCreatedButNeverShown()
{
    const auto group = QLatin1StringView("UtilsCreatedNeverShown");
    removeStoredSize(group);
    {
        QDialog dialog;
        TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
        // Forces the platform window to exist without ever showing the dialog:
        // the size was never restored, so it must not be stored either.
        QVERIFY(dialog.winId() != 0);
        QVERIFY(dialog.windowHandle());
    }
    QVERIFY(!hasStoredSize(group));
}

void LoadDialogSizeUtilsTest::shouldUseDefaultSizeWhenNoStoredSize()
{
    const auto group = QLatin1StringView("UtilsDefaultSize");
    removeStoredSize(group);
    QDialog dialog;
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
    dialog.show();
    QVERIFY(QTest::qWaitForWindowExposed(&dialog));
    QCOMPARE(dialog.windowHandle()->size(), defaultSize);
    QCOMPARE(dialog.size(), defaultSize);
}

void LoadDialogSizeUtilsTest::shouldStoreSizeWhenDestroyedWhileVisible()
{
    const auto group = QLatin1StringView("UtilsStillVisible");
    removeStoredSize(group);
    const QSize newSize(521, 411);
    {
        QDialog dialog;
        TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
        dialog.show();
        QVERIFY(QTest::qWaitForWindowExposed(&dialog));
        resizeAndWait(&dialog, newSize);
    }
    QVERIFY(hasStoredSize(group));
    QCOMPARE(reopenedSize(group), newSize);
}

void LoadDialogSizeUtilsTest::shouldStoreSizeWhenAccepted()
{
    const auto group = QLatin1StringView("UtilsAccepted");
    removeStoredSize(group);
    const QSize newSize(533, 422);
    {
        QDialog dialog;
        TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
        dialog.show();
        QVERIFY(QTest::qWaitForWindowExposed(&dialog));
        resizeAndWait(&dialog, newSize);
        dialog.accept();
    }
    QCOMPARE(reopenedSize(group), newSize);
}

void LoadDialogSizeUtilsTest::shouldStoreSizeWhenClosed()
{
    const auto group = QLatin1StringView("UtilsClosed");
    removeStoredSize(group);
    const QSize newSize(544, 433);
    {
        QDialog dialog;
        TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
        dialog.show();
        QVERIFY(QTest::qWaitForWindowExposed(&dialog));
        resizeAndWait(&dialog, newSize);
        dialog.close();
    }
    QCOMPARE(reopenedSize(group), newSize);
}

void LoadDialogSizeUtilsTest::shouldNotReloadSizeOnSecondShow()
{
    const auto group = QLatin1StringView("UtilsSecondShow");
    removeStoredSize(group);
    QDialog dialog;
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
    dialog.show();
    QVERIFY(QTest::qWaitForWindowExposed(&dialog));
    const QSize newSize(511, 422);
    resizeAndWait(&dialog, newSize);
    dialog.hide();
    dialog.show();
    QVERIFY(QTest::qWaitForWindowExposed(&dialog));
    // Showing the dialog again must not reset the size the user chose.
    QCOMPARE(dialog.size(), newSize);
}

void LoadDialogSizeUtilsTest::shouldManageKPageDialog()
{
    const auto group = QLatin1StringView("UtilsKPageDialog");
    removeStoredSize(group);
    const QSize newSize(611, 466);
    {
        KPageDialog dialog;
        dialog.addPage(new QLabel(u"page"_s), u"Page"_s);
        TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
        dialog.show();
        QVERIFY(QTest::qWaitForWindowExposed(&dialog));
        QCOMPARE(dialog.size(), defaultSize);
        resizeAndWait(&dialog, newSize);
    }
    KPageDialog dialog;
    dialog.addPage(new QLabel(u"page"_s), u"Page"_s);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&dialog, group, defaultSize);
    dialog.show();
    QVERIFY(QTest::qWaitForWindowExposed(&dialog));
    QCOMPARE(dialog.size(), newSize);
}

void LoadDialogSizeUtilsTest::shouldPositionAsQDialog()
{
    const auto group = QLatin1StringView("UtilsPosition");
    removeStoredSize(group);
    QWidget parent;
    parent.resize(1000, 800);
    parent.show();
    QVERIFY(QTest::qWaitForWindowExposed(&parent));

    const QSize size(200, 150);
    QDialog managed(&parent);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(&managed, group, size);
    managed.show();
    QVERIFY(QTest::qWaitForWindowExposed(&managed));

    QDialog plain(&parent);
    plain.resize(size);
    plain.show();
    QVERIFY(QTest::qWaitForWindowExposed(&plain));

    // The event filter must not swallow the show event, otherwise the dialog
    // loses the positioning done by QDialog::adjustPosition().
    QCOMPARE(managed.pos(), plain.pos());
}

#include "moc_loaddialogsizeutilstest.cpp"
