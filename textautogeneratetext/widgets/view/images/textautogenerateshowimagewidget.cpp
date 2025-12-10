/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateshowimagewidget.h"
#include "core/textautogeneratemanager.h"
#include "widgets/view/images/textautogenerategraphicsview.h"
#include <KIO/ApplicationLauncherJob>
#include <KIO/JobUiDelegate>
#include <KIO/JobUiDelegateFactory>
#include <KLocalizedString>
#include <QApplication>
#include <QClipboard>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QMimeData>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <TextAddonsWidgets/SaveFileUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateShowImageWidget::TextAutoGenerateShowImageWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mImageGraphicsView(new TextAutoGenerateGraphicsView(this))
    , mZoomControls(new QWidget(this))
    , mZoomSpin(new QDoubleSpinBox(this))
    , mSlider(new QSlider(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mImageGraphicsView->setObjectName(u"mImageGraphicsView"_s);
    mainLayout->addWidget(mImageGraphicsView);
    connect(mImageGraphicsView, &TextAutoGenerateGraphicsView::zoomChanged, this, [this](qreal zoom) {
        mSlider->setValue(static_cast<int>(zoom * 100));
        mZoomSpin->setValue(zoom);
    });
    connect(mImageGraphicsView, &TextAutoGenerateGraphicsView::minimumZoomChanged, this, &TextAutoGenerateShowImageWidget::updateRanges);
    connect(mImageGraphicsView, &TextAutoGenerateGraphicsView::maximumZoomChanged, this, &TextAutoGenerateShowImageWidget::updateRanges);

    mZoomControls->setObjectName(u"zoomControls"_s);
    auto zoomLayout = new QHBoxLayout;
    zoomLayout->setObjectName(u"zoomLayout"_s);
    mZoomControls->setLayout(zoomLayout);
    mainLayout->addWidget(mZoomControls);

    auto label = new QLabel(i18nc("@label:textbox", "Zoom:"), this);
    label->setObjectName(u"zoomLabel"_s);
    label->setTextFormat(Qt::PlainText);
    zoomLayout->addWidget(label);

    mZoomSpin->setObjectName(u"mZoomSpin"_s);

    mZoomSpin->setValue(1);
    mZoomSpin->setDecimals(1);
    mZoomSpin->setSingleStep(0.1);
    zoomLayout->addWidget(mZoomSpin);

    mSlider->setObjectName(u"mSlider"_s);
    mSlider->setOrientation(Qt::Horizontal);
    zoomLayout->addWidget(mSlider);
    mSlider->setValue(mZoomSpin->value() * 100.0);

    auto resetButton = new QPushButton(i18nc("@action:button", "100%"), this);
    resetButton->setObjectName(u"resetButton"_s);
    zoomLayout->addWidget(resetButton);
    connect(resetButton, &QPushButton::clicked, this, [this] {
        mImageGraphicsView->setZoom(1.0);
    });

    auto fitToViewButton = new QPushButton(i18nc("@action:button", "Fit to View"), this);
    fitToViewButton->setObjectName(u"fitToViewButton"_s);
    zoomLayout->addWidget(fitToViewButton);
    connect(fitToViewButton, &QPushButton::clicked, mImageGraphicsView, &TextAutoGenerateGraphicsView::fitToView);

    connect(mZoomSpin, &QDoubleSpinBox::valueChanged, this, [this](double value) {
        mImageGraphicsView->setZoom(static_cast<qreal>(value));
    });
    connect(mSlider, &QSlider::valueChanged, this, [this](int value) {
        mImageGraphicsView->setZoom(static_cast<qreal>(value) / 100);
    });

    updateRanges();
}

TextAutoGenerateShowImageWidget::~TextAutoGenerateShowImageWidget() = default;

void TextAutoGenerateShowImageWidget::updateRanges()
{
    const auto min = mImageGraphicsView->minimumZoom();
    const auto max = mImageGraphicsView->maximumZoom();
    mZoomSpin->setRange(min, max);
    mSlider->setRange(min * 100.0, max * 100.0);
}

void TextAutoGenerateShowImageWidget::saveAs()
{
    // TODO verify it
    TextAddonsWidgets::SaveFileUtils::saveFile(this, mManager->generateAttachmentTemporaryFile(), i18n("Save Image"));
}

void TextAutoGenerateShowImageWidget::copyImage()
{
    auto data = new QMimeData();
    data->setImageData(mImageGraphicsView->pixmap().toImage());
    data->setData(u"x-kde-force-image-copy"_s, QByteArray());
    QApplication::clipboard()->setMimeData(data, QClipboard::Clipboard);
}

void TextAutoGenerateShowImageWidget::openWith(const KService::Ptr &service)
{
    // TODO
    const QString imagePath = mManager->generateAttachmentTemporaryFile();
    // If service is null, ApplicationLauncherJob will invoke the open-with dialog
    auto job = new KIO::ApplicationLauncherJob(service);
    job->setUrls({QUrl::fromLocalFile(imagePath)});
    job->setUiDelegate(KIO::createDefaultJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, this));
    job->start();
}

void TextAutoGenerateShowImageWidget::copyLocation()
{
    // TODO
    const QString imagePath = mManager->generateAttachmentTemporaryFile();
    QApplication::clipboard()->setText(imagePath);
}

#include "moc_textautogenerateshowimagewidget.cpp"
