/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatormodel.h"
#include <KLocalizedString>

TranslatorModel::TranslatorModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TranslatorModel::~TranslatorModel() = default;

void TranslatorModel::insertTranslators(const QVector<Translator> &translators)
{
    if (rowCount() != 0) {
        beginResetModel();
        mTranslators.clear();
        endResetModel();
    }
    if (!translators.isEmpty()) {
        beginInsertRows(QModelIndex(), 0, translators.count() - 1);
        mTranslators = translators;
        endInsertRows();
    }
}

QVariant TranslatorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (static_cast<TranslatorRoles>(section)) {
        case TranslatorRoles::Source:
            return i18n("Source");
        case TranslatorModel::Target:
            return i18n("Target");
        case TranslatorModel::TypeTranslator:
            return i18n("Type");
        case TranslatorModel::Repository:
            return i18n("Repository");
        case TranslatorModel::Version:
            return i18n("Version");
        case TranslatorModel::Available:
            return i18n("Available");
        case TranslatorModel::Identifier:
        case TranslatorModel::CheckSum:
        case TranslatorModel::Url:
            return {};
        }
    }
    return {};
}

int TranslatorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mTranslators.count();
}

QVariant TranslatorModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mTranslators.count()) {
        return {};
    }
    if (role != Qt::DisplayRole) {
        return {};
    }

    const auto translator = mTranslators.at(index.row());
    const int col = index.column();

    switch (static_cast<TranslatorRoles>(col)) {
    case TranslatorModel::Source: {
        return translator.source();
    }
    case TranslatorModel::Target: {
        return translator.target();
    }
    case TranslatorModel::TypeTranslator: {
        return translator.type();
    }
    case TranslatorModel::Repository: {
        return translator.repository();
    }
    case TranslatorModel::Version: {
        return translator.version();
    }
    case TranslatorModel::Available: {
        // TODO return translator.version();
        return {};
    }
    case TranslatorModel::Identifier: {
        // TODO verify it.
        return translator.modelName();
    }
    case TranslatorModel::Url: {
        return translator.url();
    }
    case TranslatorModel::CheckSum: {
        return translator.checkSum();
    }
    }
    return {};
}

void TranslatorModel::clear()
{
    if (rowCount() != 0) {
        beginResetModel();
        mTranslators.clear();
        endResetModel();
    }
}

int TranslatorModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(TranslatorRoles::LastColumn) + 1;
}

#include "moc_translatormodel.cpp"
