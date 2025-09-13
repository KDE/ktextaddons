/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolplugin.h"
#include <qjsonarray.h>
#include <qjsonobject.h>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextToolPlugin::TextAutoGenerateTextToolPlugin(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToolPlugin::~TextAutoGenerateTextToolPlugin() = default;

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
    QJsonObject obj;
    obj["name"_L1] = QString::fromLatin1(mToolNameId);
    // obj["description"_L1] = QString::fromLatin1(mToolNameId);

    QJsonObject parameters;
    parameters["type"_L1] = u"object"_s;
    QJsonObject properties;
    QJsonArray required;
    QStringList lst;
    for (const TextAutoGenerateTextToolPluginProperty &property : std::as_const(mProperties)) {
        QJsonObject prop;
        prop["type"_L1] = u"string"_s;
        prop["description"_L1] = QString::fromLatin1(property.description().untranslatedText());
        properties[QString::fromLatin1(property.name().untranslatedText())] = prop;
        lst.append(QString::fromLatin1(property.name().untranslatedText()));
    }
    required = QJsonArray::fromStringList(lst);
    parameters["required"_L1] = required;
    parameters["properties"_L1] = properties;
    obj["parameters"_L1] = parameters;
    return obj;
}

#include "moc_textautogeneratetexttoolplugin.cpp"
