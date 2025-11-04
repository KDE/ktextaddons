/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateattachmentutils.h"
#include "textautogeneratetextcore_debug.h"
#include <QFile>
#include <QString>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
QByteArray TextAutoGenerateAttachmentUtils::generateBase64(const QString &fileName)
{
    if (fileName.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "FileName is empty. It's a bug";
        return {};
    }

    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly)) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to open file:" << fileName;
        return {};
    }
    const QByteArray ba = f.readAll();

    // return u"data:image/%1;base64,%2"_s.arg(u"PNG"_s, QString::fromLatin1(ba.toBase64()));

    // TODO add info
    return ba;
}

QByteArray TextAutoGenerateAttachmentUtils::generateUniqueId(const QByteArray &messageId, int index)
{
    return messageId + QByteArray("_") + QByteArray::number(index);
}
