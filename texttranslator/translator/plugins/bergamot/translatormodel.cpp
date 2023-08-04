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
    const auto translator = mTranslators.at(index.row());
    switch (role) {
    case TranslatorModel::Source: {
        return translator.source();
    }
    case TranslatorModel::Target: {
        return translator.target();
    }
    case TranslatorModel::TypeTranslator: {
        return translator.type();
    }
    case Qt::DisplayRole:
    case TranslatorModel::Repository: {
        return translator.repository();
    }
    case TranslatorModel::Version: {
        return translator.version();
    }
    case TranslatorModel::Available: {
        // TODO return translator.version();
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
