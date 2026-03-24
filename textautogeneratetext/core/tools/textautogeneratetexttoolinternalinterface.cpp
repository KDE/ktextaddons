/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolinternalinterface.h"
#include "core/tools/textautogeneratetexttoolsloadingjob.h"
using namespace TextAutoGenerateText;
TextAutoGenerateTextToolInternalInterface::TextAutoGenerateTextToolInternalInterface(QObject *parent)
    : QObject(parent)
{
}

TextAutoGenerateTextToolInternalInterface::~TextAutoGenerateTextToolInternalInterface() = default;

void TextAutoGenerateTextToolInternalInterface::loadInternalTools(const QString &filename)
{
    auto job = new TextAutoGenerateTextToolsLoadingJob(this);
    job->setFileName(filename);
    connect(job, &TextAutoGenerateTextToolsLoadingJob::tools, this, &TextAutoGenerateTextToolInternalInterface::slotToolsLoaded);
    job->start();
}

void TextAutoGenerateTextToolInternalInterface::slotToolsLoaded(const QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> &tools)
{
    mTools = tools;
}

QList<TextAutoGenerateTextToolInternal> TextAutoGenerateTextToolInternalInterface::tools() const
{
    return mTools;
}

void TextAutoGenerateTextToolInternalInterface::setTools(const QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> &newTools)
{
    mTools = newTools;
}

#include "moc_textautogeneratetexttoolinternalinterface.cpp"
