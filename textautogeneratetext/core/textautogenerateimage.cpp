/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateimage.h"

using namespace TextAutoGenerateText;
TextAutoGenerateImage::TextAutoGenerateImage() = default;

TextAutoGenerateImage::~TextAutoGenerateImage() = default;

QByteArray TextAutoGenerateImage::image() const
{
    return mImage;
}

void TextAutoGenerateImage::setImage(const QByteArray &newImage)
{
    mImage = newImage;
}
