/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <KService>
#include <QWidget>
class QDoubleSpinBox;
class QSlider;
namespace TextAutoGenerateText
{
class TextAutoGenerateGraphicsView;
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateShowImageWidget : public QWidget
{
    Q_OBJECT
public:
    struct ImageInfo {
        QPixmap pixmap;
    };

    explicit TextAutoGenerateShowImageWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateShowImageWidget() override;

    void copyImage();
    void saveAs();

    void openWith(const KService::Ptr &service);
    void copyLocation();

    void setImageInfo(const TextAutoGenerateShowImageWidget::ImageInfo &info);

    void setImage(const QString &path);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateRanges();
    TextAutoGenerateGraphicsView *const mImageGraphicsView;
    QWidget *const mZoomControls;
    QDoubleSpinBox *const mZoomSpin;
    QSlider *const mSlider;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
