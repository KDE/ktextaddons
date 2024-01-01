/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextmodel.h"
#include "libvoskspeechtotext_debug.h"
#include <KIO/Global>
#include <KLocalizedString>
#include <QColor>
#include <QDir>

VoskSpeechToTextModel::VoskSpeechToTextModel(QObject *parent)
    : QAbstractListModel{parent}
{
    updateInstalledLanguage();
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
        case VoskRoles::SizeByte:
        case VoskRoles::Url:
        case VoskRoles::Name:
        case VoskRoles::NeedToUpdateLanguage:
        case VoskRoles::CheckSum:
            return {};
        case VoskRoles::LangText:
            return i18n("Language");
        case VoskRoles::Installed:
            return i18n("Installed");
        case VoskRoles::InstalledVersion:
            return i18n("Installed Version");
        case VoskRoles::AvailableVersion:
            return i18n("Available Version");
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
        if (needToUpdateLanguageModel(speechToTextInfo)) {
            if (static_cast<VoskRoles>(col) == VoskRoles::InstalledVersion) {
                return QColor(Qt::red);
            }
        }
        return {};
    } else if (role == Qt::DisplayRole) {
        switch (static_cast<VoskRoles>(col)) {
        case VoskRoles::InstalledVersion: {
            const QString name{speechToTextInfo.name()};
            if (isInstalled(name)) {
                return versionInstalled(name);
            }
            return {};
        }
        case VoskRoles::AvailableVersion: {
            return speechToTextInfo.version();
        }
        case VoskRoles::NeedToUpdateLanguage: {
            return needToUpdateLanguageModel(speechToTextInfo);
        }
        case VoskRoles::Installed: {
            if (isInstalled(speechToTextInfo.name())) {
                return i18n("Installed");
            }
            return {};
        }
        case VoskRoles::Identifier: {
            return speechToTextInfo.identifier();
        }
        case VoskRoles::LangText: {
            return speechToTextInfo.langText();
        }
        case VoskRoles::Size: {
            return KIO::convertSize(speechToTextInfo.size());
        }
        case VoskRoles::SizeByte: {
            return speechToTextInfo.size();
        }
        case VoskRoles::Url: {
            return speechToTextInfo.url();
        }
        case VoskRoles::CheckSum: {
            return speechToTextInfo.md5();
        }
        case VoskRoles::Name: {
            return speechToTextInfo.name();
        }
        }
    }
    return {};
}

bool VoskSpeechToTextModel::needToUpdateLanguageModel(const VoskSpeechToTextInfo &language) const
{
    const QString shortName{language.identifier()};
    if (isInstalled(shortName)) {
        if (versionInstalled(shortName) != language.version()) {
            return true;
        }
    }
    return false;
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

void VoskSpeechToTextModel::removeLanguage(const QString &name)
{
    auto index = std::find_if(mLanguageInstalled.begin(), mLanguageInstalled.end(), [name](const VoskEngineUtils::LanguageInstalled &installed) {
        return (name == installed.name);
    });
    if (index != mLanguageInstalled.end()) {
        const QString absoluteLanguageModelPath = (*index).absoluteLanguageModelPath;
        if (!QDir(absoluteLanguageModelPath).removeRecursively()) {
            qCDebug(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to delete " << absoluteLanguageModelPath;
            return;
        }
        mLanguageInstalled.removeAll(*index);
        beginResetModel();
        endResetModel();
    }
    updateInstalledLanguage();
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

bool VoskSpeechToTextModel::isInstalled(const QString &name) const
{
    for (const auto &lang : std::as_const(mLanguageInstalled)) {
        if (lang.name == name) {
            return true;
        }
    }
    return false;
}

QString VoskSpeechToTextModel::versionInstalled(const QString &shortName) const
{
    for (const auto &lang : std::as_const(mLanguageInstalled)) {
        if (lang.name == shortName) {
            return lang.versionStr;
        }
    }
    return {};
}

#include "moc_voskspeechtotextmodel.cpp"
