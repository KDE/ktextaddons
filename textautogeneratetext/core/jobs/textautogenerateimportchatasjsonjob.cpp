/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateimportchatasjsonjob.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateImportChatAsJsonJob::TextAutoGenerateImportChatAsJsonJob(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateImportChatBaseJob{parent}
{
}

TextAutoGenerateImportChatAsJsonJob::~TextAutoGenerateImportChatAsJsonJob() = default;

void TextAutoGenerateImportChatAsJsonJob::importChat()
{
    QFile f(mInfo.filename);
    if (f.open(QFile::ReadOnly)) {
        const auto content = f.readAll();
        f.close();

        QJsonParseError error;
        const auto doc = QJsonDocument::fromJson(content, &error);
        const QJsonObject obj = doc.object();
        const QString title = obj[u"title"_s].toString();

        QList<TextAutoGenerateText::TextAutoGenerateMessage> msgs;
        const QJsonArray array = obj[u"messages"_s].toArray();
        for (const auto &val : array) {
            const TextAutoGenerateMessage msg = TextAutoGenerateText::TextAutoGenerateMessage::deserialize(val.toObject());
            if (msg.isValid()) {
                msgs.append(msg);
                // TODO verify error
            }
        }
        Q_EMIT importDone(title, msgs);
    }
    deleteLater();
}
