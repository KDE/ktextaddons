/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfo.h"
using namespace Qt::Literals::StringLiterals;
GenericNetworkModelAvailableInfo::GenericNetworkModelAvailableInfo() = default;

GenericNetworkModelAvailableInfo::~GenericNetworkModelAvailableInfo() = default;

void GenericNetworkModelAvailableInfo::parseInfo(const QJsonObject &obj)
{
    mToolsSupported = obj["tools_supported"_L1].toBool();
    mDescription = obj["description"_L1].toString();
    mName = obj["name"_L1].toString();
    // TODO
}

QString GenericNetworkModelAvailableInfo::description() const
{
    return mDescription;
}

void GenericNetworkModelAvailableInfo::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}

bool GenericNetworkModelAvailableInfo::operator==(const GenericNetworkModelAvailableInfo &other) const
{
    return mDescription == other.description() && mName == other.name() && mToolsSupported == other.toolsSupported();
}

QString GenericNetworkModelAvailableInfo::name() const
{
    return mName;
}

void GenericNetworkModelAvailableInfo::setName(const QString &newName)
{
    mName = newName;
}

bool GenericNetworkModelAvailableInfo::toolsSupported() const
{
    return mToolsSupported;
}

void GenericNetworkModelAvailableInfo::setToolsSupported(bool newToolsSupported)
{
    mToolsSupported = newToolsSupported;
}

QDebug operator<<(QDebug d, const GenericNetworkModelAvailableInfo &t)
{
    d.space() << "name:" << t.name();
    d.space() << "description:" << t.description();
    d.space() << "toolsSupported:" << t.toolsSupported();
    return d;
}
