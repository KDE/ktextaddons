/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadprogresswidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>

OllamaModelDownloadProgressWidget::OllamaModelDownloadProgressWidget(QWidget *parent)
    : QWidget{parent}
{
}

OllamaModelDownloadProgressWidget::~OllamaModelDownloadProgressWidget() = default;

#include "moc_ollamamodeldownloadprogresswidget.cpp"
