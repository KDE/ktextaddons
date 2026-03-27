/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolinternalinterface.h"
#include "core/tools/textautogeneratetexttoolsloadingjob.h"
#include <QJsonObject>
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

bool TextAutoGenerateTextToolInternalInterface::contains(const QByteArray &toolName) const
{
    for (const auto &t : mTools) {
        if (t.toolNameId() == toolName) {
            return true;
        }
    }
    return false;
}

TextAutoGenerateTextToolInternal TextAutoGenerateTextToolInternalInterface::toolInternal(const QByteArray &toolName) const
{
    for (const auto &t : mTools) {
        if (t.toolNameId() == toolName) {
            return t;
        }
    }
    return {};
}

bool TextAutoGenerateTextToolInternalInterface::hasTools() const
{
    return !mTools.isEmpty();
}

QList<QJsonObject> TextAutoGenerateTextToolInternalInterface::toolInternalMetaData() const
{
    QList<QJsonObject> lstMetaData;
    lstMetaData.reserve(mTools.count());
    for (const auto &t : mTools) {
        lstMetaData.append(t.generateMetadata());
    }
    return lstMetaData;
}

#include "moc_textautogeneratetexttoolinternalinterface.cpp"
