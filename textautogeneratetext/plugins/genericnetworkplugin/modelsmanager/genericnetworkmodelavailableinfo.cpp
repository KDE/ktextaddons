/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfo.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;

namespace
{
// Mistral uses a boolean, Anthropic uses an object {"supported": bool}
[[nodiscard]] bool isSupported(const QJsonValue &value)
{
    if (value.isObject()) {
        return value["supported"_L1].toBool(false);
    }
    return value.toBool(false);
}
}

GenericNetworkModelAvailableInfo::GenericNetworkModelAvailableInfo() = default;

GenericNetworkModelAvailableInfo::~GenericNetworkModelAvailableInfo() = default;

void GenericNetworkModelAvailableInfo::parseInfo(const QJsonObject &obj)
{
    // qDebug() << " obj " << obj;
    if (obj["tools_supported"_L1].toBool()) {
        mCapabilities |= Capability::Tools;
    }
    mDescription = obj["description"_L1].toString();
    mModelName = obj["name"_L1].toString();
    if (mModelName.isEmpty()) {
        // Anthropic
        mModelName = obj["display_name"_L1].toString();
    }
    mModelSize = obj["model_size"_L1].toString();
    mIdentifier = obj["id"_L1].toString();
    mOwnedBy = obj["owned_by"_L1].toString();
    if (obj.contains("capabilities"_L1)) {
        parseCapabilities(obj["capabilities"_L1].toObject());
    }
}

void GenericNetworkModelAvailableInfo::parseCapabilities(const QJsonObject &obj)
{
    if (isSupported(obj["audio"_L1])) {
        mCapabilities |= Capability::Audio;
    }
    if (isSupported(obj["ocr"_L1])) {
        mCapabilities |= Capability::Ocr;
    }
    if (isSupported(obj["vision"_L1]) || isSupported(obj["image_input"_L1])) {
        mCapabilities |= Capability::Vision;
    }
    if (isSupported(obj["function_calling"_L1])) {
        mCapabilities |= Capability::Tools;
    }
    if (isSupported(obj["thinking"_L1])) {
        mCapabilities |= Capability::Thinking;
    }
    // TODO add more
    // Mistral:
    // {"audio":false,"classification":false,"completion_chat":false,"completion_fim":false,"fine_tuning":false,"function_calling":false,"moderation":false,"ocr":false,"vision":false}
    // Anthropic: {"image_input":{"supported":true},"thinking":{"supported":true,...},...}
}

QString GenericNetworkModelAvailableInfo::description() const
{
    return mDescription;
}

void GenericNetworkModelAvailableInfo::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}

bool GenericNetworkModelAvailableInfo::operator==(const GenericNetworkModelAvailableInfo &other) const = default;

QString GenericNetworkModelAvailableInfo::modelName() const
{
    return mModelName;
}

void GenericNetworkModelAvailableInfo::setModelName(const QString &newName)
{
    mModelName = newName;
}

QString GenericNetworkModelAvailableInfo::modelSize() const
{
    return mModelSize;
}

void GenericNetworkModelAvailableInfo::setModelSize(const QString &newModelSize)
{
    mModelSize = newModelSize;
}

QString GenericNetworkModelAvailableInfo::identifier() const
{
    return mIdentifier;
}

void GenericNetworkModelAvailableInfo::setIdentifier(const QString &newIdentifier)
{
    mIdentifier = newIdentifier;
}

QString GenericNetworkModelAvailableInfo::ownedBy() const
{
    return mOwnedBy;
}

void GenericNetworkModelAvailableInfo::setOwnedBy(const QString &newOwnedBy)
{
    mOwnedBy = newOwnedBy;
}

GenericNetworkModelAvailableInfo::Capabilities GenericNetworkModelAvailableInfo::capabilities() const
{
    return mCapabilities;
}

void GenericNetworkModelAvailableInfo::setCapabilities(Capabilities newCapabilities)
{
    mCapabilities = newCapabilities;
}

QDebug operator<<(QDebug d, const GenericNetworkModelAvailableInfo &t)
{
    d.space() << "name:" << t.modelName();
    d.space() << "description:" << t.description();
    d.space() << "modelSize:" << t.modelSize();
    d.space() << "identifier:" << t.identifier();
    d.space() << "ownedBy:" << t.ownedBy();
    d.space() << "capabilities:" << t.capabilities();
    return d;
}

#include "moc_genericnetworkmodelavailableinfo.cpp"
