/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginproperty.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTextToolPluginProperty::TextAutoGenerateTextToolPluginProperty() = default;

TextAutoGenerateTextToolPluginProperty::~TextAutoGenerateTextToolPluginProperty() = default;

KLazyLocalizedString TextAutoGenerateTextToolPluginProperty::description() const
{
    return mDescription;
}

void TextAutoGenerateTextToolPluginProperty::setDescription(const KLazyLocalizedString &newDescription)
{
    mDescription = newDescription;
}

QString TextAutoGenerateTextToolPluginProperty::name() const
{
    return mName;
}

void TextAutoGenerateTextToolPluginProperty::setName(const QString &newName)
{
    mName = newName;
}

QStringList TextAutoGenerateTextToolPluginProperty::typeElements() const
{
    return mTypeElements;
}

void TextAutoGenerateTextToolPluginProperty::setTypeElements(const QStringList &newEnumElements)
{
    mTypeElements = newEnumElements;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty &t)
{
    d.space() << "typeElements:" << t.typeElements();
    d.space() << "description:" << t.description().untranslatedText();
    d.space() << "name:" << t.name();
    return d;
}

void TextAutoGenerateTextToolPluginProperty::parse(const QJsonObject &obj)
{
#if 0
    const QJsonObject function = obj["function"_L1].toObject();
    mDescription = function["description"_L1].toString();
    mName = function["name"_L1].toString();

    const QJsonObject parameters = function["parameters"_L1].toObject();
    const QJsonObject properties = parameters["properties"_L1].toObject();
    const QStringList keys = properties.keys();
    for (const QString &k : keys) {
        KAITodoToolProperty property;
        property.parse(properties[k].toObject(), k);
        if (property.isValid()) {
            mProperties.append(property);
        }
    }
    // qDebug() << " parse tool " << *this;
#endif
}
