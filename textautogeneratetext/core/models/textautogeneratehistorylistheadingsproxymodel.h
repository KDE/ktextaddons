/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "core/models/textautogeneratechatsmodel.h"
#include "textautogeneratetext_private_export.h"
#include <QAbstractProxyModel>
#include <QPointer>
#include <TextAutoGenerateText/TextAutoGenerateChat>
#include <limits>
#include <vector>
namespace TextAutoGenerateText
{
class TextAutoGenerateProjectsModel;
/*!
 * Groups the chats of a TextAutoGenerateChatsModel in sections: one section per project, followed by
 * the date sections. A chat which belongs to a project is only listed in that project.
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateHistoryListHeadingsProxyModel final : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHistoryListHeadingsProxyModel(QObject *parent = nullptr);
    ~TextAutoGenerateHistoryListHeadingsProxyModel() override;

    /*! The number of date sections. They are always the last sections, the project sections coming
     *  first, so a date section is not at a fixed row any more. */
    static constexpr uint sectionCount = uint(TextAutoGenerateChat::SectionHistory::NSections);

    // QAbstractItemModel interface
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    [[nodiscard]] QModelIndex parent(const QModelIndex &child) const override;
    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;
    [[nodiscard]] bool hasChildren(const QModelIndex &index) const override;

    // Drag and drop: a chat can be dragged onto a project, which moves it to that project.
    [[nodiscard]] QStringList mimeTypes() const override;
    [[nodiscard]] QMimeData *mimeData(const QModelIndexList &indexes) const override;
    [[nodiscard]] Qt::DropActions supportedDragActions() const override;
    [[nodiscard]] Qt::DropActions supportedDropActions() const override;
    //! Dropping a chat on a project never removes a row, whatever the view asks after a move.
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    [[nodiscard]] bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    // QAbstractProxyModel interface
    void setSourceModel(QAbstractItemModel *sourceModel) override;
    [[nodiscard]] QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
    [[nodiscard]] QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;

Q_SIGNALS:
    /*! Emitted when \a chatId was dropped on a project. The model doesn't store the chats itself, so
     *  the change is left to the owner of the manager. An empty \a projectId removes the chat from
     *  its project. */
    void moveChatToProjectRequested(const QByteArray &chatId, const QByteArray &projectId);

private:
    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles);
    void onProjectsDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles);
    void rebuildSections();
    void resetSections();

    struct Section {
        //! The project this section stands for, empty when it is a date section.
        QByteArray projectId;
        //! Only meaningful for a date section.
        TextAutoGenerateChat::SectionHistory kind = TextAutoGenerateChat::SectionHistory::NSections;
        // kept sorted for performance reasons
        std::vector<QPersistentModelIndex> chats;
    };

    //! The project sections, then the sectionCount date sections.
    std::vector<Section> mSections;
    QPointer<TextAutoGenerateProjectsModel> mProjectsModel;

    //! Stored in the internal id of a section index, as the number of sections isn't constant.
    static constexpr quintptr sectionMarker = std::numeric_limits<quintptr>::max();

    enum class IndexType : uint8_t {
        Root,
        Section,
        History,
    };
    [[nodiscard]] IndexType type(const QModelIndex &index) const;
    [[nodiscard]] bool isValidSectionRow(int row) const;
    //! Returns the row of the section the given source index belongs to.
    [[nodiscard]] int sectionId(const QModelIndex &sourceIndex) const;
    /*! Returns the project a drop on \a parent would move the chats to, or an empty identifier when
     *  \a parent is not a project. */
    [[nodiscard]] QByteArray dropProjectId(const QModelIndex &parent) const;
    [[nodiscard]] TextAutoGenerateProjectsModel *projectsModel() const;
};
}
