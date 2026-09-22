/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistheadingsproxymodel.h"

#include "core/models/textautogenerateprojectsmodel.h"
#include "core/textautogenerateprojectsmanager.h"

#include <QApplication>
#include <QDataStream>
#include <QFont>
#include <QIODevice>
#include <QMimeData>
#include <QPalette>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
//! The chats dropped on a project, as a list of chat identifiers.
const char s_chatsMimeType[] = "application/x-textautogeneratetext-chatids";
}
TextAutoGenerateHistoryListHeadingsProxyModel::TextAutoGenerateHistoryListHeadingsProxyModel(QObject *parent)
    : QAbstractProxyModel{parent}
{
    rebuildSections();
}

TextAutoGenerateHistoryListHeadingsProxyModel::~TextAutoGenerateHistoryListHeadingsProxyModel() = default;

bool TextAutoGenerateHistoryListHeadingsProxyModel::isValidSectionRow(int row) const
{
    return row >= 0 && row < int(mSections.size());
}

TextAutoGenerateProjectsModel *TextAutoGenerateHistoryListHeadingsProxyModel::projectsModel() const
{
    const auto *chatsModel = qobject_cast<const TextAutoGenerateChatsModel *>(sourceModel());
    if (!chatsModel) {
        return nullptr;
    }
    auto *projectsManager = chatsModel->textAutoGenerateProjectsManager();
    return projectsManager ? projectsManager->textAutoGenerateProjectsModel() : nullptr;
}

QVariant TextAutoGenerateHistoryListHeadingsProxyModel::data(const QModelIndex &index, int role) const
{
    switch (type(index)) {
    case IndexType::Root:
        return {};
    case IndexType::Section: {
        if (!isValidSectionRow(index.row())) {
            return {};
        }
        const auto &section = mSections.at(index.row());
        switch (role) {
        case Qt::ItemDataRole::DisplayRole:
            if (!section.projectId.isEmpty()) {
                return mProjectsModel ? mProjectsModel->nameFromIdentifier(section.projectId) : QString{};
            }
            return TextAutoGenerateChatsModel::sectionName(section.kind);
        case TextAutoGenerateChatsModel::Project:
            // Empty for a date section, so that a caller can tell both apart.
            return section.projectId;
        case Qt::BackgroundRole:
            return QApplication::palette().brush(QPalette::Window);
        case Qt::FontRole: {
            auto font = qvariant_cast<QFont>(QAbstractProxyModel::data(index, Qt::FontRole));
            font.setBold(true);
            return font;
        }
        default:
            return {};
        }
    }
    case IndexType::History:
        return sourceModel()->data(mapToSource(index), role);
    }
    Q_UNREACHABLE();
    return {};
}

QModelIndex TextAutoGenerateHistoryListHeadingsProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (column != 0 || row < 0) {
        return {};
    }

    switch (type(parent)) {
    case IndexType::Root: {
        if (!isValidSectionRow(row)) {
            return {};
        }
        return createIndex(row, column, sectionMarker);
    }
    case IndexType::Section: {
        if (!isValidSectionRow(parent.row())) {
            return {};
        }
        const auto &section = mSections.at(parent.row());
        if (row >= int(section.chats.size())) {
            return {};
        }
        return createIndex(row, column, parent.row());
    }
    case IndexType::History:
        return {};
    }
    Q_UNREACHABLE();
    return {};
}

QModelIndex TextAutoGenerateHistoryListHeadingsProxyModel::parent(const QModelIndex &child) const
{
    switch (type(child)) {
    case IndexType::Root:
    case IndexType::Section:
        return {};
    case IndexType::History:
        return createIndex(int(child.internalId()), 0, sectionMarker);
    }
    Q_UNREACHABLE();
    return {};
}

int TextAutoGenerateHistoryListHeadingsProxyModel::rowCount(const QModelIndex &parent) const
{
    switch (type(parent)) {
    case IndexType::Root:
        return int(mSections.size());
    case IndexType::Section:
        if (!isValidSectionRow(parent.row())) {
            return 0;
        }
        return int(mSections.at(parent.row()).chats.size());
    case IndexType::History:
        return 0;
    }
    Q_UNREACHABLE();
    return {};
}

int TextAutoGenerateHistoryListHeadingsProxyModel::columnCount(const QModelIndex &parent) const
{
    switch (type(parent)) {
    case IndexType::Root:
    case IndexType::Section:
        return 1;
    case IndexType::History:
        return 0;
    }
    Q_UNREACHABLE();
    return {};
}

Qt::ItemFlags TextAutoGenerateHistoryListHeadingsProxyModel::flags(const QModelIndex &proxyIndex) const
{
    switch (type(proxyIndex)) {
    case IndexType::Root:
        return {};
    case IndexType::Section: {
        Qt::ItemFlags flags = Qt::ItemFlag::ItemIsEnabled;
        // Only a project can be dropped on: a date section is computed from the chat itself, so
        // dropping a chat there couldn't change anything but its project, which would be obscure.
        if (isValidSectionRow(proxyIndex.row()) && !mSections.at(proxyIndex.row()).projectId.isEmpty()) {
            flags |= Qt::ItemFlag::ItemIsDropEnabled;
        }
        return flags;
    }
    case IndexType::History:
        return QAbstractProxyModel::flags(proxyIndex) | Qt::ItemFlag::ItemIsDragEnabled;
    }
    Q_UNREACHABLE();
    return {};
}

QStringList TextAutoGenerateHistoryListHeadingsProxyModel::mimeTypes() const
{
    return {QString::fromLatin1(s_chatsMimeType)};
}

QMimeData *TextAutoGenerateHistoryListHeadingsProxyModel::mimeData(const QModelIndexList &indexes) const
{
    QList<QByteArray> chatIds;
    for (const QModelIndex &index : indexes) {
        if (type(index) != IndexType::History) {
            continue;
        }
        if (const QByteArray chatId = index.data(TextAutoGenerateChatsModel::Identifier).toByteArray(); !chatId.isEmpty()) {
            chatIds.append(chatId);
        }
    }
    if (chatIds.isEmpty()) {
        return nullptr;
    }
    QByteArray encoded;
    QDataStream stream(&encoded, QIODevice::WriteOnly);
    stream << chatIds;

    auto mimeData = new QMimeData;
    mimeData->setData(QString::fromLatin1(s_chatsMimeType), encoded);
    return mimeData;
}

Qt::DropActions TextAutoGenerateHistoryListHeadingsProxyModel::supportedDragActions() const
{
    // QAbstractProxyModel forwards this to the source model, which would offer the default
    // Qt::CopyAction: the view would then start a copy drag that dropMimeData() refuses, as
    // QAbstractItemView only drops when the drag action is one of the supported drop actions.
    return Qt::MoveAction;
}

Qt::DropActions TextAutoGenerateHistoryListHeadingsProxyModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

bool TextAutoGenerateHistoryListHeadingsProxyModel::removeRows([[maybe_unused]] int row, [[maybe_unused]] int count, [[maybe_unused]] const QModelIndex &parent)
{
    // After a move drop, QAbstractItemView removes the dragged rows from the model. Moving a chat to
    // a project only changes the chat, so the chats must stay where they are.
    return false;
}

QByteArray TextAutoGenerateHistoryListHeadingsProxyModel::dropProjectId(const QModelIndex &parent) const
{
    if (type(parent) != IndexType::Section || !isValidSectionRow(parent.row())) {
        return {};
    }
    return mSections.at(parent.row()).projectId;
}

bool TextAutoGenerateHistoryListHeadingsProxyModel::canDropMimeData(const QMimeData *data,
                                                                    [[maybe_unused]] Qt::DropAction action,
                                                                    [[maybe_unused]] int row,
                                                                    [[maybe_unused]] int column,
                                                                    const QModelIndex &parent) const
{
    if (!data || !data->hasFormat(QString::fromLatin1(s_chatsMimeType))) {
        return false;
    }
    return !dropProjectId(parent).isEmpty();
}

bool TextAutoGenerateHistoryListHeadingsProxyModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!canDropMimeData(data, action, row, column, parent)) {
        return false;
    }
    const QByteArray projectId = dropProjectId(parent);

    QByteArray encoded = data->data(QString::fromLatin1(s_chatsMimeType));
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    QList<QByteArray> chatIds;
    stream >> chatIds;
    if (chatIds.isEmpty()) {
        return false;
    }
    for (const QByteArray &chatId : std::as_const(chatIds)) {
        Q_EMIT moveChatToProjectRequested(chatId, projectId);
    }
    return true;
}

bool TextAutoGenerateHistoryListHeadingsProxyModel::hasChildren(const QModelIndex &index) const
{
    // Don't use the QAbstractProxyModel override which fails on non-proxied indices
    return QAbstractItemModel::hasChildren(index); // NOLINT(bugprone-parent-virtual-call)
}

void TextAutoGenerateHistoryListHeadingsProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    beginResetModel();

    if (auto *oldModel = this->sourceModel()) {
        disconnect(oldModel, nullptr, this, nullptr);
    }
    if (mProjectsModel) {
        disconnect(mProjectsModel, nullptr, this, nullptr);
    }
    mProjectsModel = nullptr;

    QAbstractProxyModel::setSourceModel(sourceModel);

    if (!sourceModel) {
        rebuildSections();
        endResetModel();
        return;
    }

    connect(sourceModel, &QAbstractItemModel::rowsInserted, this, &TextAutoGenerateHistoryListHeadingsProxyModel::onRowsInserted);

    connect(sourceModel, &QAbstractItemModel::rowsAboutToBeRemoved, this, &TextAutoGenerateHistoryListHeadingsProxyModel::onRowsAboutToBeRemoved);

    connect(sourceModel, &QAbstractItemModel::rowsAboutToBeMoved, this, [this] {
        Q_EMIT layoutAboutToBeChanged();
    });
    connect(sourceModel, &QAbstractItemModel::rowsMoved, this, &TextAutoGenerateHistoryListHeadingsProxyModel::rebuildSections);
    connect(sourceModel, &QAbstractItemModel::rowsMoved, this, [this] {
        Q_EMIT layoutChanged();
    });

    connect(sourceModel, &QAbstractItemModel::dataChanged, this, &TextAutoGenerateHistoryListHeadingsProxyModel::onDataChanged);

    connect(sourceModel, &QAbstractItemModel::modelAboutToBeReset, this, &TextAutoGenerateHistoryListHeadingsProxyModel::beginResetModel);
    connect(sourceModel, &QAbstractItemModel::modelReset, this, &TextAutoGenerateHistoryListHeadingsProxyModel::rebuildSections);
    connect(sourceModel, &QAbstractItemModel::modelReset, this, &TextAutoGenerateHistoryListHeadingsProxyModel::endResetModel);

    connect(sourceModel, &QAbstractItemModel::layoutAboutToBeChanged, this, &TextAutoGenerateHistoryListHeadingsProxyModel::layoutAboutToBeChanged);
    connect(sourceModel, &QAbstractItemModel::layoutChanged, this, &TextAutoGenerateHistoryListHeadingsProxyModel::rebuildSections);
    connect(sourceModel, &QAbstractItemModel::layoutChanged, this, &TextAutoGenerateHistoryListHeadingsProxyModel::layoutChanged);

    mProjectsModel = projectsModel();
    if (mProjectsModel) {
        // A project is a root row of this model, so adding or removing one changes the sections
        // themselves: rebuilding everything is simpler than moving the chats around by hand, and
        // projects don't change often.
        connect(mProjectsModel, &QAbstractItemModel::rowsInserted, this, &TextAutoGenerateHistoryListHeadingsProxyModel::resetSections);
        connect(mProjectsModel, &QAbstractItemModel::rowsRemoved, this, &TextAutoGenerateHistoryListHeadingsProxyModel::resetSections);
        connect(mProjectsModel, &QAbstractItemModel::modelReset, this, &TextAutoGenerateHistoryListHeadingsProxyModel::resetSections);
        connect(mProjectsModel, &QAbstractItemModel::layoutChanged, this, &TextAutoGenerateHistoryListHeadingsProxyModel::resetSections);
        // Renaming a project only changes the name shown in its heading.
        connect(mProjectsModel, &QAbstractItemModel::dataChanged, this, &TextAutoGenerateHistoryListHeadingsProxyModel::onProjectsDataChanged);
    }

    rebuildSections();

    endResetModel();
}

QModelIndex TextAutoGenerateHistoryListHeadingsProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!sourceModel()) {
        return {};
    }

    switch (type(proxyIndex)) {
    case IndexType::Root:
    case IndexType::Section:
        return {};
    case IndexType::History: {
        const auto sectionId = int(proxyIndex.internalId());
        if (!isValidSectionRow(sectionId)) {
            return {};
        }
        const auto &section = mSections.at(sectionId);
        if (proxyIndex.row() < 0 || proxyIndex.row() >= int(section.chats.size())) {
            return {};
        }
        return section.chats.at(proxyIndex.row());
    }
    }
    Q_UNREACHABLE();
    return {};
}

QModelIndex TextAutoGenerateHistoryListHeadingsProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if (!sourceModel()) {
        return {};
    }

    if (!sourceIndex.isValid()) {
        return {};
    }

    for (auto sectionId = size_t(0), iMax = mSections.size(); sectionId < iMax; ++sectionId) {
        const auto &chats = mSections.at(sectionId).chats;

        if (const auto it = std::lower_bound(chats.cbegin(), chats.cend(), sourceIndex); it != chats.cend() && *it == sourceIndex) {
            return createIndex(int(it - chats.cbegin()), 0, sectionId);
        }
    }

    return {};
}

int TextAutoGenerateHistoryListHeadingsProxyModel::sectionId(const QModelIndex &sourceIndex) const
{
    // A chat which belongs to a project is only listed in that project, and not in a date section.
    if (const QByteArray projectId = sourceIndex.data(TextAutoGenerateChatsModel::Project).toByteArray(); !projectId.isEmpty()) {
        const auto sameProject = [&projectId](const Section &section) {
            return section.projectId == projectId;
        };
        if (const auto it = std::find_if(mSections.cbegin(), mSections.cend(), sameProject); it != mSections.cend()) {
            return int(it - mSections.cbegin());
        }
        // Unknown project: fall back to the date sections.
    }
    const auto kind = sourceIndex.data(TextAutoGenerateChatsModel::Section).value<TextAutoGenerateChat::SectionHistory>();
    return int(mSections.size() - sectionCount) + int(kind);
}

void TextAutoGenerateHistoryListHeadingsProxyModel::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    for (auto row = first; row <= last; ++row) {
        const QPersistentModelIndex persistentIndex = sourceModel()->index(row, 0, parent);
        const auto newSectionId = sectionId(persistentIndex);
        auto &newSection = mSections.at(newSectionId).chats;

        const auto newLocation = std::lower_bound(newSection.cbegin(), newSection.cend(), persistentIndex);
        const auto newLocationRow = int(newLocation - newSection.cbegin());

        beginInsertRows(createIndex(newSectionId, 0, sectionMarker), newLocationRow, newLocationRow);

        newSection.insert(newLocation, persistentIndex);

        endInsertRows();
    }
}

void TextAutoGenerateHistoryListHeadingsProxyModel::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    for (auto row = first; row <= last; ++row) {
        const auto newIndex = sourceModel()->index(row, 0, parent);

        const auto ourOldIndex = mapFromSource(newIndex);
        const auto oldSectionId = ourOldIndex.internalId();
        auto &oldSection = mSections.at(oldSectionId).chats;

        beginRemoveRows(ourOldIndex.parent(), ourOldIndex.row(), ourOldIndex.row());

        oldSection.erase(oldSection.begin() + ourOldIndex.row());

        endRemoveRows();
    }
}

void TextAutoGenerateHistoryListHeadingsProxyModel::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles)
{
    for (auto row = topLeft.row(), last = bottomRight.row(); row <= last; ++row) {
        const auto sourceIndex = topLeft.siblingAtRow(row);
        const auto proxyIndex = mapFromSource(sourceIndex);
        Q_EMIT dataChanged(proxyIndex, proxyIndex, roles);
    }

    if (!roles.empty()
        && (!roles.contains(TextAutoGenerateChatsModel::Section) && !roles.contains(TextAutoGenerateChatsModel::Favorite)
            && !roles.contains(TextAutoGenerateChatsModel::DateTime) && !roles.contains(TextAutoGenerateChatsModel::Project))) {
        return;
    }
    for (auto row = topLeft.row(), last = bottomRight.row(); row <= last; ++row) {
        const auto sourceIndex = topLeft.siblingAtRow(row);
        const auto ourOldIndex = mapFromSource(sourceIndex);

        const auto oldSectionId = int(ourOldIndex.internalId());
        const auto newSectionId = sectionId(sourceIndex);

        if (oldSectionId == newSectionId) {
            continue;
        }

        auto &oldSection = mSections.at(oldSectionId).chats;
        auto &newSection = mSections.at(newSectionId).chats;

        const auto newLocation = std::lower_bound(newSection.cbegin(), newSection.cend(), sourceIndex);
        const auto newLocationRow = int(newLocation - newSection.cbegin());

        beginMoveRows(ourOldIndex.parent(), ourOldIndex.row(), ourOldIndex.row(), createIndex(newSectionId, 0, sectionMarker), newLocationRow);

        auto persistantIndex = oldSection[ourOldIndex.row()];
        oldSection.erase(oldSection.begin() + ourOldIndex.row());
        newSection.insert(newLocation, persistantIndex);

        endMoveRows();
    }
}

void TextAutoGenerateHistoryListHeadingsProxyModel::onProjectsDataChanged(const QModelIndex &topLeft,
                                                                          const QModelIndex &bottomRight,
                                                                          [[maybe_unused]] const QList<int> &roles)
{
    // The project sections are the first rows of this model, in the order of the projects model.
    const QModelIndex first = index(topLeft.row(), 0, {});
    const QModelIndex last = index(bottomRight.row(), 0, {});
    if (first.isValid() && last.isValid()) {
        Q_EMIT dataChanged(first, last);
    }
}

void TextAutoGenerateHistoryListHeadingsProxyModel::resetSections()
{
    beginResetModel();
    rebuildSections();
    endResetModel();
}

void TextAutoGenerateHistoryListHeadingsProxyModel::rebuildSections()
{
    mSections.clear();

    if (mProjectsModel) {
        const int projectCount = mProjectsModel->rowCount();
        mSections.reserve(projectCount + sectionCount);
        for (int row = 0; row < projectCount; ++row) {
            Section section;
            section.projectId = mProjectsModel->index(row, 0).data(TextAutoGenerateProjectsModel::Identifier).toByteArray();
            mSections.push_back(std::move(section));
        }
    }
    for (uint i = 0; i < sectionCount; ++i) {
        Section section;
        section.kind = TextAutoGenerateChat::SectionHistory(i);
        mSections.push_back(std::move(section));
    }

    if (!sourceModel()) {
        return;
    }

    for (auto row = 0, until = sourceModel()->rowCount(); row < until; ++row) {
        const QPersistentModelIndex newIndex = sourceModel()->index(row, 0);
        mSections.at(sectionId(newIndex)).chats.push_back(newIndex);
    }

    for (auto &section : mSections) {
        std::sort(section.chats.begin(), section.chats.end());
    }
}

auto TextAutoGenerateHistoryListHeadingsProxyModel::type(const QModelIndex &index) const -> IndexType
{
    if (!index.isValid()) {
        return IndexType::Root;
    }

    if (index.internalId() == sectionMarker) {
        return IndexType::Section;
    }

    return IndexType::History;
}

#include "moc_textautogeneratehistorylistheadingsproxymodel.cpp"
