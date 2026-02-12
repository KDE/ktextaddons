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
    addItem(i18n("Keep Alive Presets"), QVariant::fromValue(OllamaCommonKeepAliveParametersWidget::KeepAliveType::SetTimer));
    addItem(i18n("Keep Alive Forever"), QVariant::fromValue(OllamaCommonKeepAliveParametersWidget::KeepAliveType::KeepAliveForever));
    addItem(i18n("Unload After Use"), QVariant::fromValue(OllamaCommonKeepAliveParametersWidget::KeepAliveType::UnloadAfterUse));
}

OllamaCommonKeepAliveParametersWidget::KeepAliveType OllamaCommonKeepAliveParametersComboBox::keepAliveType() const
{
    return currentData().value<OllamaCommonKeepAliveParametersWidget::KeepAliveType>();
}

void OllamaCommonKeepAliveParametersComboBox::setKeepAliveType(OllamaCommonKeepAliveParametersWidget::KeepAliveType type)
{
    const int index = findData(QVariant::fromValue(type));
    if (index != -1) {
        setCurrentIndex(index);
    }
}

#include "moc_ollamacommonkeepaliveparameterscombobox.cpp"
