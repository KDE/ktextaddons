/*
 * SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateexportchatasjsonjob.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateExportChatAsJsonJob::TextAutoGenerateExportChatAsJsonJob(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateExportChatBaseJob{parent}
{
}

TextAutoGenerateExportChatAsJsonJob::~TextAutoGenerateExportChatAsJsonJob() = default;

void TextAutoGenerateExportChatAsJsonJob::exportChat()
{
    QJsonObject obj;
    QJsonArray messages;
    for (const auto &message : std::as_const(mInfo.listMessages)) {
        const QByteArray ba = TextAutoGenerateText::TextAutoGenerateMessage::serialize(message, false);
        const QJsonDocument d = QJsonDocument::fromJson(ba);
        messages.append(d.object());
        // qDebug() << " ba " << ba;
    }
    obj[u"messages"_s] = messages;
    obj[u"title"_s] = mInfo.chatTitle;
    // qDebug() << " obj" << QJsonDocument(obj).toJson();
    QFile data(mInfo.filename);
    if (data.open(QFile::WriteOnly)) {
        QTextStream out(&data);
        out << QJsonDocument(obj).toJson();
    }
    deleteLater();
}

#include "moc_textautogenerateexportchatasjsonjob.cpp"
