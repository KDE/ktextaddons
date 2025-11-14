/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exampletexttoolpluginjob.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
ExampleTextToolPluginJob::ExampleTextToolPluginJob(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextToolPluginJob{parent}
{
}

ExampleTextToolPluginJob::~ExampleTextToolPluginJob() = default;

void ExampleTextToolPluginJob::start()
{
    qDebug() << " void ExampleTextToolPluginJob::start() ";
    if (!canStart()) {
        qWarning() << " Impossible to start ExampleTextToolPluginJob" << *this;
        deleteLater();
        return;
    }
    // TODO Need to implement job
    QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo> attachmentInfo;
    {
        const TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo attInfo{
            .mimeType = "text-plain"_ba,
            .content = "foo bla kde"_ba,
            .name = u"test-file1"_s,
            .attachmentType = TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::File,
        };
        attachmentInfo.append(attInfo);
    }
    const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo info{
        .content = u"Temperature is 35°"_s,
        .messageUuid = mMessageUuid,
        .chatId = mChatId,
        .toolIdentifier = mToolIdentifier,
        .attachementInfoList = attachmentInfo,
    };
    qDebug() << " TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo " << info;
    Q_EMIT finished(info);
    deleteLater();
}

#include "moc_exampletexttoolpluginjob.cpp"
