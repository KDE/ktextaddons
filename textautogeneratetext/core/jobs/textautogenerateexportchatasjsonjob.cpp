/*
 * SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateexportchatasjsonjob.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
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
    if (!data.open(QFile::WriteOnly)) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Failed to open file for writing:" << mInfo.filename << "error:" << data.errorString();
        Q_EMIT exportFailed(i18n("Failed to open file for writing: %1", mInfo.filename));
    } else {
        QTextStream out(&data);
        out << QJsonDocument(obj).toJson();
        out.flush();
        if ((out.status() != QTextStream::Ok) || (data.error() != QFile::NoError)) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Failed to write to file:" << mInfo.filename;
            Q_EMIT exportFailed(i18n("Failed to write to file: %1", mInfo.filename));
        } else {
            Q_EMIT exportDone(mInfo.filename);
        }
        data.close();
    }
    deleteLater();
}

QString TextAutoGenerateExportChatAsJsonJob::filter() const
{
    return u"%1 (*.json)"_s.arg(i18n("Json File"));
}

#include "moc_textautogenerateexportchatasjsonjob.cpp"
