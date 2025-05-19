/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratemenutextmanager.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QRegularExpression>
using namespace TextAutoGenerateText;
TextAutoGenerateMenuTextManager::TextAutoGenerateMenuTextManager(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateMenuTextManager::~TextAutoGenerateMenuTextManager() = default;

QList<TextAutoGenerateMenuTextInfo> TextAutoGenerateMenuTextManager::textInfos() const
{
    return mTextInfos;
}

void TextAutoGenerateMenuTextManager::setTextInfos(const QList<TextAutoGenerateMenuTextInfo> &newTextInfos)
{
    mTextInfos = newTextInfos;
}

void TextAutoGenerateMenuTextManager::load()
{
    QList<TextAutoGenerateMenuTextInfo> infos;
    KSharedConfig::Ptr config;
    const QStringList keyGroups = keyRecorderList(config);

    for (const QString &groupName : keyGroups) {
        KConfigGroup group = config->group(groupName);
        TextAutoGenerateMenuTextInfo info;
        info.setRequestText(group.readEntry(QStringLiteral("RequestedText")));
        info.setEnabled(group.readEntry(QStringLiteral("Enabled"), true));
        infos.append(std::move(info));
    }
    setTextInfos(infos);
}

void TextAutoGenerateMenuTextManager::save()
{
    KSharedConfig::Ptr config;
    const QStringList filterGroups = keyRecorderList(config);

    for (const QString &group : filterGroups) {
        config->deleteGroup(group);
    }
    for (int i = 0, total = mTextInfos.count(); i < total; ++i) {
        const QString groupName = QStringLiteral("AskIA #%1").arg(i);
        KConfigGroup group = config->group(groupName);
        const TextAutoGenerateMenuTextInfo &info = mTextInfos.at(i);
        group.writeEntry(QStringLiteral("RequestedText"), info.requestText());
        group.writeEntry(QStringLiteral("Enabled"), info.enabled());
    }
    config->sync();
}

QStringList TextAutoGenerateMenuTextManager::keyRecorderList(KSharedConfig::Ptr &config) const
{
    config = KSharedConfig::openConfig();
    const QStringList keyGroups = config->groupList().filter(QRegularExpression(QStringLiteral("AskIA #\\d+")));
    return keyGroups;
}

#include "moc_textautogeneratemenutextmanager.cpp"
