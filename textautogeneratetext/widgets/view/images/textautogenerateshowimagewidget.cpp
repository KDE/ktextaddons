/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateshowimagewidget.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateShowImageWidget::TextAutoGenerateShowImageWidget(QWidget *parent)
    : QWidget{parent}
{
}

TextAutoGenerateShowImageWidget::~TextAutoGenerateShowImageWidget() = default;

#include "moc_textautogenerateshowimagewidget.cpp"
