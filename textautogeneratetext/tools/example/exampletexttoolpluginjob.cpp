/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exampletexttoolpluginjob.h"
#include <QDebug>

ExampleTextToolPluginJob::ExampleTextToolPluginJob(QObject *parent)
    : QObject{parent}
{
}

ExampleTextToolPluginJob::~ExampleTextToolPluginJob() = default;

const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &ExampleTextToolPluginJob::toolArguments() const
{
    return mToolArguments;
}

void ExampleTextToolPluginJob::setToolArguments(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &newToolArguments)
{
    mToolArguments = newToolArguments;
}

bool ExampleTextToolPluginJob::canStart() const
{
    return !mToolArguments.isEmpty();
}

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
