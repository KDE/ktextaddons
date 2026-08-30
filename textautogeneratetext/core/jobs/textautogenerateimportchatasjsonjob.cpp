/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogenerateimportchatasjsonjob.h"
#include "core/textautogeneratetextutils.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
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
        if (error.error != QJsonParseError::NoError) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Failed to parse JSON file" << mInfo.filename << "error:" << error.errorString() << "at offset"
                                                     << error.offset;
        } else {
            const QJsonObject obj = doc.object();
            const QString title = obj[u"title"_s].toString();

            QMap<QByteArray, QByteArray> convertUuid;
            QList<TextAutoGenerateText::TextAutoGenerateMessage> msgs;
            const QJsonArray array = obj[u"messages"_s].toArray();
            msgs.reserve(qsizetype(array.size()));
            for (const auto &val : array) {
                if (const TextAutoGenerateMessage msg = TextAutoGenerateText::TextAutoGenerateMessage::deserialize(val.toObject()); msg.isValid()) {
                    convertUuid.insert(msg.uuid(), TextAutoGenerateTextUtils::generateUUid());
                    msgs.append(msg);
                }
            }
            // Convert
            for (auto &msg : msgs) {
                if (convertUuid.contains(msg.uuid())) {
                    msg.setUuid(convertUuid.value(msg.uuid()));
                }
                if (convertUuid.contains(msg.answerUuid())) {
                    msg.setAnswerUuid(convertUuid.value(msg.answerUuid()));
                }
            }
            Q_EMIT importDone(title, msgs);
        }
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Failed to open file for reading:" << mInfo.filename << "error:" << f.errorString();
        Q_EMIT importFailed(i18n("Failed to open file for reading: %1", mInfo.filename));
    }
    deleteLater();
}

QString TextAutoGenerateImportChatAsJsonJob::fileFilter()
{
    return u"%1 (*.json)"_s.arg(i18n("Json File"));
}

#include "moc_textautogenerateimportchatasjsonjob.cpp"
