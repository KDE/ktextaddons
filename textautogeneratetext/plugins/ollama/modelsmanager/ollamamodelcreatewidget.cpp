/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelcreatewidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>

OllamaModelCreateWidget::OllamaModelCreateWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mManager(manager)
{
}

OllamaModelCreateWidget::~OllamaModelCreateWidget() = default;

#include "moc_ollamamodelcreatewidget.cpp"
