/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateimage.h"
#include "textautogeneratetextcore_memory_debug.h"
using namespace TextAutoGenerateText;
TextAutoGenerateImage::TextAutoGenerateImage()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateImage created " << this;
}

TextAutoGenerateImage::~TextAutoGenerateImage()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateImage deleted " << this;
}

TextAutoGenerateImage::TextAutoGenerateImage(const TextAutoGenerateImage &other)
    : QSharedData(other)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAnswerInfo created " << this;
    mImage = other.mImage;
}

QByteArray TextAutoGenerateImage::image() const
{
    return mImage;
}

void TextAutoGenerateImage::setImage(const QByteArray &newImage)
{
    mImage = newImage;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateImage &t)
{
    d.space() << "mImage:" << t.image();
    return d;
}

bool TextAutoGenerateImage::operator==(const TextAutoGenerateImage &other) const
{
    return mImage == other.mImage;
}
