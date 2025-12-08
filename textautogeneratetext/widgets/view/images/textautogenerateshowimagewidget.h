/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QDoubleSpinBox;
class QSlider;
namespace TextAutoGenerateText
{
class TextAutoGenerateGraphicsView;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateShowImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateShowImageWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateShowImageWidget() override;

    void copyImage();
    void saveAs();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateRanges();
    TextAutoGenerateGraphicsView *const mImageGraphicsView;
    QWidget *const mZoomControls;
    QDoubleSpinBox *const mZoomSpin;
    QSlider *const mSlider;
};
}
