/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratemenutextmanager.h"

#include <KConfigGroup>
#include <QRegularExpression>
using namespace Qt::Literals::StringLiterals;
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
    if (mTextInfos != newTextInfos) {
        mTextInfos = newTextInfos;
        Q_EMIT textInfoChanged();
    }
}

void TextAutoGenerateMenuTextManager::load()
{
    QList<TextAutoGenerateMenuTextInfo> infos;
    KSharedConfig::Ptr config;
    const QStringList keyGroups = keyRecorderList(config);

    for (const QString &groupName : keyGroups) {
        const KConfigGroup group = config->group(groupName);
        TextAutoGenerateMenuTextInfo info;
        info.setRequestText(group.readEntry(u"RequestedText"_s));
        info.setEnabled(group.readEntry(u"Enabled"_s, true));
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
        const QString groupName = u"AskIA #%1"_s.arg(i);
        KConfigGroup group = config->group(groupName);
        const TextAutoGenerateMenuTextInfo &info = mTextInfos.at(i);
        group.writeEntry(u"RequestedText"_s, info.requestText());
        group.writeEntry(u"Enabled"_s, info.enabled());
    }
    config->sync();
}

QStringList TextAutoGenerateMenuTextManager::keyRecorderList(KSharedConfig::Ptr &config) const
{
    config = KSharedConfig::openConfig();
    const QStringList keyGroups = config->groupList().filter(QRegularExpression(u"AskIA #\\d+"_s));
    return keyGroups;
}

#include "moc_textautogeneratemenutextmanager.cpp"
