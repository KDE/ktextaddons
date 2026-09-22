/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetagsmodel.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTagsModel::TextAutoGenerateTagsModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateTagsModel::~TextAutoGenerateTagsModel() = default;

int TextAutoGenerateTagsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mTags.count();
}

QVariant TextAutoGenerateTagsModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= mTags.count()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid index:" << row;
        return {};
    }
    const auto &tag = mTags[row];
    switch (role) {
    case Qt::DisplayRole:
    case Name:
        return tag.name();
    case Identifier:
        return tag.identifier();
    case Qt::DecorationRole:
    case Color:
        // An invalid color is returned as an invalid QVariant, so that the view falls back to the
        // palette instead of painting a black swatch. QStyledItemDelegate turns a QColor set on
        // Qt::DecorationRole into a swatch of the view's iconSize, so no delegate is needed.
        if (!tag.color().isValid()) {
            return {};
        }
        return tag.color();
    default:
        break;
    }
    return {};
}

QList<QColor> TextAutoGenerateTagsModel::colors(const QList<QByteArray> &identifiers) const
{
    QList<QColor> lstColors;
    lstColors.reserve(identifiers.count());
    for (const QByteArray &id : identifiers) {
        lstColors.append(colorFromIdentifier(id));
    }
    return lstColors;
}

QColor TextAutoGenerateTagsModel::colorFromIdentifier(const QByteArray &identifier) const
{
    if (const int i = indexFromIdentifier(identifier); i != -1) {
        return mTags.at(i).color();
    }
    return {};
}

QList<TextAutoGenerateTag> TextAutoGenerateTagsModel::tags() const
{
    return mTags;
}

void TextAutoGenerateTagsModel::setTags(const QList<TextAutoGenerateTag> &newTags)
{
    beginResetModel();
    mTags = newTags;
    endResetModel();
}

void TextAutoGenerateTagsModel::addTag(const TextAutoGenerateTag &newTag)
{
    beginInsertRows(QModelIndex(), mTags.count(), mTags.count());
    mTags.append(newTag);
    endInsertRows();
}

void TextAutoGenerateTagsModel::removeTag(const QByteArray &identifier)
{
    if (const int i = indexFromIdentifier(identifier); i != -1) {
        beginRemoveRows(QModelIndex(), i, i);
        mTags.removeAt(i);
        endRemoveRows();
    }
}

void TextAutoGenerateTagsModel::updateTag(const TextAutoGenerateTag &tag)
{
    const int i = indexFromIdentifier(tag.identifier());
    if (i == -1) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Unable to find tag with identifier:" << tag.identifier();
        return;
    }
    mTags[i] = tag;
    const QModelIndex idx = index(i, 0);
    Q_EMIT dataChanged(idx, idx);
}

void TextAutoGenerateTagsModel::clear()
{
    if (mTags.isEmpty()) {
        return;
    }
    beginResetModel();
    mTags.clear();
    endResetModel();
}

int TextAutoGenerateTagsModel::indexFromIdentifier(const QByteArray &identifier) const
{
    if (identifier.isEmpty()) {
        return -1;
    }
    const auto matchesIdentifier = [&](const TextAutoGenerateTag &tag) {
        return tag.identifier() == identifier;
    };
    const auto tagIt = std::find_if(mTags.constBegin(), mTags.constEnd(), matchesIdentifier);
    if (tagIt == mTags.constEnd()) {
        return -1;
    }
    return std::distance(mTags.constBegin(), tagIt);
}

#include "moc_textautogeneratetagsmodel.cpp"
