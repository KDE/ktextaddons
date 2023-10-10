/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextmodel.h"
#include "libvoskspeechtotext_debug.h"
#include <KLocalizedString>
#include <QColor>

VoskSpeechToTextModel::VoskSpeechToTextModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

VoskSpeechToTextModel::~VoskSpeechToTextModel() = default;

int VoskSpeechToTextModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mSpeechToTextInfos.count();
}

QVariant VoskSpeechToTextModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (static_cast<VoskRoles>(section)) {
        case VoskRoles::Identifier:
        case VoskRoles::Url:
        case VoskRoles::CheckSum:
            return {};
        case VoskRoles::LangText:
            return i18n("Lang");
        case VoskRoles::Obsolete:
            return i18n("Obsolete");
        case VoskRoles::Size:
            return i18n("Size");
        }
    }
    return {};
}

QVariant VoskSpeechToTextModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mSpeechToTextInfos.count()) {
        return {};
    }
    const auto speechToTextInfo = mSpeechToTextInfos.at(index.row());
    const int col = index.column();
    if (role == Qt::BackgroundRole) {
#if 0
        if (needToUpdateLanguageModel(speechToTextInfo)) {
            if (static_cast<VoskRoles>(col) == VoskRoles::InstalledVersion) {
                return QColor(Qt::red);
            }
        }
#endif
        return {};
    } else if (role == Qt::DisplayRole) {
        switch (static_cast<VoskRoles>(col)) {
        case VoskRoles::InstalledVersion: {
            const QString shortName{speechToTextInfo.identifier()};
            if (isInstalled(shortName)) {
                // TODO return versionInstalled(shortName);
            }
            return {};
        }
        case VoskRoles::AvailableVersion: {
            return speechToTextInfo.version();
        }
        case VoskRoles::Installed: {
            if (isInstalled(speechToTextInfo.identifier())) {
                return i18n("Installed");
            }
            return {};
        }
        case VoskRoles::Identifier: {
            return speechToTextInfo.identifier();
        }
        case VoskRoles::Obsolete: {
            return speechToTextInfo.obsolete();
        }
        case VoskRoles::LangText: {
            return speechToTextInfo.langText();
        }
        case VoskRoles::Size: {
            return speechToTextInfo.size();
        }
        case VoskRoles::Url: {
            return speechToTextInfo.url();
        }
        case VoskRoles::CheckSum: {
            return speechToTextInfo.md5();
        }
            //        case VoskRoles::NeedToUpdateLanguage: {
            //            return needToUpdateLanguageModel(translator);
            //        }
        }
    }
    return {};
}

void VoskSpeechToTextModel::clear()
{
    if (rowCount() != 0) {
        beginResetModel();
        mSpeechToTextInfos.clear();
        endResetModel();
    }
    updateInstalledLanguage();
}

void VoskSpeechToTextModel::updateInstalledLanguage()
{
    mLanguageInstalled = VoskEngineUtils::languageLocallyStored();
    qCDebug(LIBVOSKSPEECHTOTEXT_LOG) << "mLanguageInstalled " << mLanguageInstalled;
}

QVector<VoskSpeechToTextInfo> VoskSpeechToTextModel::speechToTextInfos() const
{
    return mSpeechToTextInfos;
}

void VoskSpeechToTextModel::setSpeechToTextInfos(const QVector<VoskSpeechToTextInfo> &newSpeechToTextInfo)
{
    if (rowCount() != 0) {
        beginResetModel();
        mSpeechToTextInfos.clear();
        endResetModel();
    }
    if (!newSpeechToTextInfo.isEmpty()) {
        beginInsertRows(QModelIndex(), 0, newSpeechToTextInfo.count() - 1);
        mSpeechToTextInfos = newSpeechToTextInfo;
        endInsertRows();
    }
    updateInstalledLanguage();
}

int VoskSpeechToTextModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(VoskRoles::LastColumn) + 1;
}

bool VoskSpeechToTextModel::isInstalled(const QString &shortName) const
{
    for (const auto &lang : std::as_const(mLanguageInstalled)) {
        if (lang.shortName == shortName) {
            return true;
        }
    }
    return false;
}

int VoskSpeechToTextModel::versionInstalled(const QString &shortName) const
{
    for (const auto &lang : std::as_const(mLanguageInstalled)) {
        if (lang.shortName == shortName) {
            return lang.version;
        }
    }
    return false;
}

#include "moc_voskspeechtotextmodel.cpp"
