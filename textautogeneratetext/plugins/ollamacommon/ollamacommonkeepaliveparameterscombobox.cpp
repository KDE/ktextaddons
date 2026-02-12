/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonkeepaliveparameterscombobox.h"
#include <KLocalizedString>
OllamaCommonKeepAliveParametersComboBox::OllamaCommonKeepAliveParametersComboBox(QWidget *parent)
    : QComboBox(parent)
{
    fill();
}

OllamaCommonKeepAliveParametersComboBox::~OllamaCommonKeepAliveParametersComboBox() = default;

void OllamaCommonKeepAliveParametersComboBox::fill()
{
}

OllamaCommonKeepAliveParametersWidget::KeepAliveType OllamaCommonKeepAliveParametersComboBox::keepAliveType() const
{
    return {};
}

void OllamaCommonKeepAliveParametersComboBox::setKeepAliveType(OllamaCommonKeepAliveParametersWidget::KeepAliveType type)
{
    // TODO
}

#include "moc_ollamacommonkeepaliveparameterscombobox.cpp"
