/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolplugin.h"
#include "textautogeneratetexttoolpluginjob.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextToolPlugin::TextAutoGenerateTextToolPlugin(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToolPlugin::~TextAutoGenerateTextToolPlugin() = default;

QJsonObject TextAutoGenerateTextToolPlugin::metadata()
{
    if (mMetaData.empty()) {
        mMetaData = generateMetadata();
    }
    return mMetaData;
}

bool TextAutoGenerateTextToolPlugin::enabled() const
{
    return mEnabled;
}

void TextAutoGenerateTextToolPlugin::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

QByteArray TextAutoGenerateTextToolPlugin::toolNameId() const
{
    return mToolNameId;
}

void TextAutoGenerateTextToolPlugin::setToolNameId(const QByteArray &newToolName)
{
    mToolNameId = newToolName;
}

void TextAutoGenerateTextToolPlugin::showConfigureDialog([[maybe_unused]] QWidget *parent)
{
}

bool TextAutoGenerateTextToolPlugin::isValid() const
{
    return !mToolNameId.isEmpty();
}

QList<TextAutoGenerateTextToolPluginProperty> TextAutoGenerateTextToolPlugin::properties() const
{
    return mProperties;
}

void TextAutoGenerateTextToolPlugin::setProperties(const QList<TextAutoGenerateTextToolPluginProperty> &newProperties)
{
    mProperties = newProperties;
}

QJsonObject TextAutoGenerateTextToolPlugin::generateMetadata() const
{
    QJsonObject toolObj;
    toolObj["type"_L1] = u"function"_s;

    QJsonObject functionObj;
    functionObj["name"_L1] = QString::fromLatin1(mToolNameId);
    functionObj["description"_L1] = description();

    QJsonObject parameters;
    parameters["type"_L1] = u"object"_s;
    QJsonObject propertiesObj;
    QJsonArray required;
    QStringList lst;
    for (const TextAutoGenerateTextToolPluginProperty &property : std::as_const(mProperties)) {
        QJsonObject prop;
        prop["type"_L1] = u"string"_s;
        prop["description"_L1] = QString::fromLatin1(property.description().untranslatedText());
        const QStringList enumTypes = property.typeElements();
        if (!enumTypes.isEmpty()) {
            prop["enum"_L1] = QJsonArray::fromStringList(enumTypes);
        }
        propertiesObj[property.name()] = prop;
        lst.append(property.name());
    }
    required = QJsonArray::fromStringList(lst);
    parameters["required"_L1] = required;
    parameters["properties"_L1] = propertiesObj;
    functionObj["parameters"_L1] = parameters;

    toolObj["function"_L1] = functionObj;

    return toolObj;
}

void TextAutoGenerateTextToolPlugin::initializeJob(TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *job,
                                                   const QByteArray &chatId,
                                                   const QByteArray &uuid,
                                                   const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo &info)
{
    job->setToolArguments(info.toolCallArgument);
    job->setChatId(chatId);
    job->setMessageUuid(uuid);
    job->setToolIdentifier(info.toolName);
    job->setProperties(mProperties);
    connect(job,
            &TextAutoGenerateText::TextAutoGenerateTextToolPluginJob::finished,
            this,
            [this](const QString &str, const QByteArray &messageUuid, const QByteArray &chatId, const QByteArray &toolIdentifier) {
                Q_EMIT finished(str, messageUuid, chatId, toolIdentifier);
                Q_EMIT toolInProgress({});
                // qDebug() << " CurrentDateTimeToolPluginJob::finished: " << str;
            });
    connect(job,
            &TextAutoGenerateText::TextAutoGenerateTextToolPluginJob::toolInProgress,
            this,
            &TextAutoGenerateText::TextAutoGenerateTextToolPlugin::toolInProgress);
}
#include "moc_textautogeneratetexttoolplugin.cpp"
