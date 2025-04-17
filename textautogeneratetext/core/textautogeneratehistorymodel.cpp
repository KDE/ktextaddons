/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorymodel.h"

using namespace TextAutogenerateText;
TextAutoGenerateHistoryModel::TextAutoGenerateHistoryModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateHistoryModel::~TextAutoGenerateHistoryModel() = default;

int TextAutoGenerateHistoryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mHistoryInfos.count();
}

QVariant TextAutoGenerateHistoryModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mHistoryInfos.count()) {
        return {};
    }
    const auto &info = mHistoryInfos[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case Subject:
        return info.subject();
    case DateTime:
        return info.dateTime();
    case Model:
        return info.model();
    case Engine:
        return info.engine();
    case ReferenceUuid:
        return info.referenceUuid();
    }
    return {};
}

QList<TextAutoGenerateHistoryInfo> TextAutoGenerateHistoryModel::historyInfos() const
{
    return mHistoryInfos;
}

void TextAutoGenerateHistoryModel::setHistoryInfos(const QList<TextAutoGenerateHistoryInfo> &newHistoryInfos)
{
    beginResetModel();
    mHistoryInfos = newHistoryInfos;
    endResetModel();
}

void TextAutoGenerateHistoryModel::clear()
{
    beginResetModel();
    mHistoryInfos.clear();
    endResetModel();
}

void TextAutoGenerateHistoryModel::addInfo(const TextAutoGenerateHistoryInfo &msg)
{
    beginInsertRows(QModelIndex(), 0, mHistoryInfos.count() - 1);
    mHistoryInfos.append(msg);
    endInsertRows();
}

void TextAutoGenerateHistoryModel::removeInfo(const QByteArray &uuid)
{
    // TODO
}

#include "moc_textautogeneratehistorymodel.cpp"
