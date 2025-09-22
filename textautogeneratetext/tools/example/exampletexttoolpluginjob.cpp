/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exampletexttoolpluginjob.h"
#include <QDebug>

ExampleTextToolPluginJob::ExampleTextToolPluginJob(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextToolPluginJob{parent}
{
}

ExampleTextToolPluginJob::~ExampleTextToolPluginJob() = default;

void ExampleTextToolPluginJob::start()
{
    if (!canStart()) {
        qWarning() << " Impossible to start ExampleTextToolPluginJob";
        deleteLater();
        return;
    }
    // TODO
}

#include "moc_exampletexttoolpluginjob.cpp"
