/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextmodel.h"
#include "libvoskspeechtotext_debug.h"
#include <KLocalizedString>

VoskSpeechToTextModel::VoskSpeechToTextModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

VoskSpeechToTextModel::~VoskSpeechToTextModel() = default;

int VoskSpeechToTextModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mSpeechToTextInfo.count();
}

QVariant VoskSpeechToTextModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (static_cast<VoskRoles>(section)) {
        case VoskRoles::Lang:
        case VoskRoles::Url:
            return {};
        case VoskRoles::LangText:
            return i18n("Lang");
        }
    }
    return {};
}

QVariant VoskSpeechToTextModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mSpeechToTextInfo.count()) {
        return {};
    }

    // TODO
    return {};
}

void VoskSpeechToTextModel::clear()
{
    if (rowCount() != 0) {
        beginResetModel();
        mSpeechToTextInfo.clear();
        endResetModel();
    }
    updateInstalledLanguage();
}

void VoskSpeechToTextModel::updateInstalledLanguage()
{
    // mLanguageInstalled = BergamotEngineUtils::languageLocallyStored();
    // qCDebug(LIBVOSKSPEECHTOTEXT_LOG) << "mLanguageInstalled " << mLanguageInstalled;
}

QVector<VoskSpeechToTextInfo> VoskSpeechToTextModel::speechToTextInfo() const
{
    return mSpeechToTextInfo;
}

void VoskSpeechToTextModel::setSpeechToTextInfo(const QVector<VoskSpeechToTextInfo> &newSpeechToTextInfo)
{
    if (rowCount() != 0) {
        beginResetModel();
        mSpeechToTextInfo.clear();
        endResetModel();
    }
    if (!mSpeechToTextInfo.isEmpty()) {
        beginInsertRows(QModelIndex(), 0, newSpeechToTextInfo.count() - 1);
        mSpeechToTextInfo = newSpeechToTextInfo;
        endInsertRows();
    }
    updateInstalledLanguage();
}

int VoskSpeechToTextModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(VoskRoles::LastColumn) + 1;
}

#include "moc_voskspeechtotextmodel.cpp"
