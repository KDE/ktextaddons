/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateshowimagewidgettest.h"
#include "widgets/view/images/textautogenerategraphicsview.h"
#include "widgets/view/images/textautogenerateshowimagewidget.h"
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateShowImageWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateShowImageWidgetTest::TextAutoGenerateShowImageWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateShowImageWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateShowImageWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto graphicsView = w.findChild<TextAutoGenerateText::TextAutoGenerateGraphicsView *>(u"mImageGraphicsView"_s);
    QVERIFY(graphicsView);

    auto zoomLayout = w.findChild<QHBoxLayout *>(u"zoomLayout"_s);
    QVERIFY(zoomLayout);

    auto zoomLabel = w.findChild<QLabel *>(u"zoomLabel"_s);
    QVERIFY(zoomLabel);
    QVERIFY(!zoomLabel->text().isEmpty());

    auto mZoomSpin = w.findChild<QDoubleSpinBox *>(u"mZoomSpin"_s);
    QVERIFY(mZoomSpin);
    QCOMPARE(mZoomSpin->value(), 1.0);
    QCOMPARE(mZoomSpin->singleStep(), 0.1);

    auto mSlider = w.findChild<QSlider *>(u"mSlider"_s);
    QVERIFY(mSlider);
    QCOMPARE(mSlider->orientation(), Qt::Horizontal);
    // TODO QCOMPARE(mSlider->value(), 100);

    mSlider->setValue(200);
    QCOMPARE(mSlider->value(), 200);
    QCOMPARE(mZoomSpin->value(), 2);
    QCOMPARE(graphicsView->zoom(), (qreal)2.0);

    mZoomSpin->setValue(3);
    QCOMPARE(mZoomSpin->value(), 3);
    QCOMPARE(mSlider->value(), 300);
    QCOMPARE(graphicsView->zoom(), (qreal)3.0);

    auto resetButton = w.findChild<QPushButton *>(u"resetButton"_s);
    QVERIFY(resetButton);
    QVERIFY(!resetButton->text().isEmpty());
    resetButton->click();
    QCOMPARE(graphicsView->zoom(), (qreal)1.0);
    QCOMPARE(mZoomSpin->value(), 1.0);
    QCOMPARE(mSlider->value(), 100);

    auto fitToViewButton = w.findChild<QPushButton *>(u"fitToViewButton"_s);
    QVERIFY(fitToViewButton);
    QVERIFY(!fitToViewButton->text().isEmpty());
}

#include "moc_textautogenerateshowimagewidgettest.cpp"
