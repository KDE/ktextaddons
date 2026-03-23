/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolinternal.h"
#include "textautogeneratetexttoolinternalproperty.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextToolInternal::TextAutoGenerateTextToolInternal() = default;

TextAutoGenerateTextToolInternal::~TextAutoGenerateTextToolInternal() = default;

QList<TextAutoGenerateTextToolInternalProperty> TextAutoGenerateTextToolInternal::properties() const
{
    return mProperties;
}

void TextAutoGenerateTextToolInternal::setProperties(const QList<TextAutoGenerateTextToolInternalProperty> &newProperties)
{
    mProperties = newProperties;
}

QStringList TextAutoGenerateTextToolInternal::required() const
{
    return mRequired;
}

void TextAutoGenerateTextToolInternal::setRequired(const QStringList &newRequired)
{
    mRequired = newRequired;
}

QByteArray TextAutoGenerateTextToolInternal::toolNameId() const
{
    return mToolNameId;
}

void TextAutoGenerateTextToolInternal::setToolNameId(const QByteArray &newToolNameId)
{
    mToolNameId = newToolNameId;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternal &t)
{
    d.space() << "properties:" << t.properties();
    d.space() << "required:" << t.required();
    d.space() << "toolNameId:" << t.toolNameId();
    return d;
}

QJsonObject TextAutoGenerateTextToolInternal::generateMetadata() const
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
    for (const TextAutoGenerateTextToolInternalProperty &property : std::as_const(mProperties)) {
        QJsonObject prop;
        prop["type"_L1] = u"string"_s;
        prop["description"_L1] = property.description();
        const QStringList enumTypes = property.typeElements();
        if (!enumTypes.isEmpty()) {
            prop["enum"_L1] = QJsonArray::fromStringList(enumTypes);
        }
        const QString propertyName = property.name();
        propertiesObj[propertyName] = prop;
        lst.append(propertyName);
    }
    if (mRequired.isEmpty()) {
        required = QJsonArray::fromStringList(lst);
    } else {
        required = QJsonArray::fromStringList(mRequired);
    }
    parameters["required"_L1] = required;
    parameters["properties"_L1] = propertiesObj;
    functionObj["parameters"_L1] = parameters;

    toolObj["function"_L1] = functionObj;

    return toolObj;
}

QString TextAutoGenerateTextToolInternal::description() const
{
    return mDescription;
}

void TextAutoGenerateTextToolInternal::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}
