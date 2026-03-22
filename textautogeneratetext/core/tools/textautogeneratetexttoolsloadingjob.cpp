/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolsloadingjob.h"
#include "textautogeneratetextcore_debug.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextToolsLoadingJob::TextAutoGenerateTextToolsLoadingJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToolsLoadingJob::~TextAutoGenerateTextToolsLoadingJob() = default;

void TextAutoGenerateTextToolsLoadingJob::start()
{
    if (!canStart()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Filename is empty. It's a bug";
        deleteLater();
        return;
    }
    loadTools();
    deleteLater();
}

void TextAutoGenerateTextToolsLoadingJob::loadTools()
{
    QFile f(u"://tools.json"_s);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << " Impossible to open tools json file";
    }
    const auto content = f.readAll();
    f.close();

    QJsonParseError error;
    const auto doc = QJsonDocument::fromJson(content, &error);
    if (error.error) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " Error duing loading json file " << error.errorString() << " position : " << error.offset;
        return;
    }
    // qDebug() << " doc " << doc;
    parseJsonTools(doc.array());
}

void TextAutoGenerateTextToolsLoadingJob::parseJsonTools(const QJsonArray &array)
{
    QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> lstTool;
    for (const auto &v : array) {
        TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty tool;
        const auto obj = v.toObject();
        /*
        tool.parse(obj);
        if (tool.isValid()) {
            lstTool.insert(tool);
        }
        */
    }
}

bool TextAutoGenerateTextToolsLoadingJob::canStart() const
{
    return !mFileName.isEmpty();
}

QString TextAutoGenerateTextToolsLoadingJob::fileName() const
{
    return mFileName;
}

void TextAutoGenerateTextToolsLoadingJob::setFileName(const QString &newFileName)
{
    mFileName = newFileName;
}

#include "moc_textautogeneratetexttoolsloadingjob.cpp"
