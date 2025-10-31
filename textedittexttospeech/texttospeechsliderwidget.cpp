/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechsliderwidget.h"

#include <QFontMetrics>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechSliderWidget::TextToSpeechSliderWidget(const QString &labelInfo, QWidget *parent)
    : QWidget{parent}
    , mLabelInfo(labelInfo)
    , mLabel(new QLabel(this))
    , mSlider(new QSlider(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(u"mainLayout"_s);
    mSlider->setObjectName(u"mSlider"_s);
    mLabel->setObjectName(u"mLabel"_s);
    mSlider->setOrientation(Qt::Horizontal);
    mainLayout->addWidget(mSlider);
    mainLayout->addWidget(mLabel);

    const QFontMetrics f(mLabel->font());
    mLabel->setMinimumWidth(f.horizontalAdvance(u"MMMM"_s));
    connect(mSlider, &QSlider::valueChanged, this, &TextToSpeechSliderWidget::slotValueChanged);
}

TextToSpeechSliderWidget::~TextToSpeechSliderWidget() = default;

void TextToSpeechSliderWidget::setValue(int value)
{
    mSlider->setValue(value);
    slotValueChanged(value);
}

void TextToSpeechSliderWidget::setRange(int min, int max)
{
    mSlider->setRange(min, max);
}

int TextToSpeechSliderWidget::value() const
{
    return mSlider->value();
}

void TextToSpeechSliderWidget::slotValueChanged(int value)
{
    Q_EMIT valueChanged(value);
    mLabel->setText(mLabelInfo.arg(QString::number(value)));
}

#include "moc_texttospeechsliderwidget.cpp"
