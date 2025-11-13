/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolplugin.h"
#include <QJsonArray>

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

QString TextAutoGenerateTextToolPlugin::iconName() const
{
    return {};
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &t)
{
    d.space() << "content" << t.content;
    d.space() << "messageUuid" << t.messageUuid;
    d.space() << "chatId" << t.chatId;
    d.space() << "toolIdentifier" << t.toolIdentifier;
    return d;
}

#include "moc_textautogeneratetexttoolplugin.cpp"
