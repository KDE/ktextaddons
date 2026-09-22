/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistheadingsproxymodeltest.h"
#include "core/models/textautogeneratehistorylistheadingsproxymodel.h"
#include "core/models/textautogenerateprojectsmodel.h"
#include "core/textautogenerateprojectsmanager.h"

#include <QAbstractListModel>
#include <QDateTime>
#include <QMimeData>
#include <QSignalSpy>
#include <QTest>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

namespace
{
TextAutoGenerateProject createProject(const QByteArray &identifier, const QString &name)
{
    TextAutoGenerateProject project;
    project.setIdentifier(identifier);
    project.setName(name);
    return project;
}

TextAutoGenerateChat createChat(const QByteArray &identifier, const QByteArray &projectId = {})
{
    TextAutoGenerateChat chat;
    chat.setIdentifier(identifier);
    chat.setProjectId(projectId);
    chat.setDateTime(QDateTime(QDate::currentDate(), QTime(12, 0)).toSecsSinceEpoch());
    return chat;
}

//! The row of a date section, which follow the project sections.
int dateSectionRow(int projectCount, TextAutoGenerateChat::SectionHistory kind)
{
    return projectCount + int(kind);
}
}

namespace
{
class FakeChatsModel final : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FakeChatsModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
    }

    [[nodiscard]] int rowCount(const QModelIndex &parent = {}) const override
    {
        return parent.isValid() ? 0 : mSections.size();
    }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override
    {
        if (!index.isValid() || index.row() < 0 || index.row() >= mSections.size()) {
            return {};
        }
        if (role == TextAutoGenerateChatsModel::Section) {
            return QVariant::fromValue(TextAutoGenerateChat::SectionHistory(mSections.at(index.row())));
        }
        return {};
    }

    void setSections(const QList<int> &sections)
    {
        beginResetModel();
        mSections = sections;
        endResetModel();
    }

private:
    QList<int> mSections;
};
}

QTEST_GUILESS_MAIN(TextAutoGenerateHistoryListHeadingsProxyModelTest)

TextAutoGenerateHistoryListHeadingsProxyModelTest::TextAutoGenerateHistoryListHeadingsProxyModelTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateHistoryListHeadingsProxyModelTest::shouldHandleNullSourceModel()
{
    TextAutoGenerateHistoryListHeadingsProxyModel proxy;
    proxy.setSourceModel(nullptr);

    QCOMPARE(proxy.rowCount({}), int(TextAutoGenerateHistoryListHeadingsProxyModel::sectionCount));
    QVERIFY(!proxy.mapToSource(proxy.index(0, 0, {})).isValid());
}

void TextAutoGenerateHistoryListHeadingsProxyModelTest::shouldRejectInvalidIndexes()
{
    FakeChatsModel model;
    model.setSections({int(TextAutoGenerateChat::SectionHistory::Today)});

    TextAutoGenerateHistoryListHeadingsProxyModel proxy;
    proxy.setSourceModel(&model);

    QVERIFY(!proxy.index(999, 0, {}).isValid());
    QVERIFY(!proxy.index(0, 1, {}).isValid());

    const QModelIndex sectionToday = proxy.index(int(TextAutoGenerateChat::SectionHistory::Today), 0, {});
    QVERIFY(sectionToday.isValid());

    QVERIFY(proxy.index(0, 0, sectionToday).isValid());
    QVERIFY(!proxy.index(999, 0, sectionToday).isValid());
}

void TextAutoGenerateHistoryListHeadingsProxyModelTest::shouldGroupChatsByProject()
{
    // GIVEN two projects, a chat in the first one and a chat without project
    TextAutoGenerateProjectsManager projectsManager;
    projectsManager.setProjects({createProject("project1", u"Project 1"_s), createProject("project2", u"Project 2"_s)});

    TextAutoGenerateChatsModel chatsModel;
    chatsModel.setTextAutoGenerateProjectsManager(&projectsManager);
    chatsModel.setChats({createChat("chat1", "project1"), createChat("chat2")});

    // WHEN
    TextAutoGenerateHistoryListHeadingsProxyModel proxy;
    proxy.setSourceModel(&chatsModel);

    // THEN the project sections come first, followed by the date sections
    QCOMPARE(proxy.rowCount({}), 2 + int(TextAutoGenerateHistoryListHeadingsProxyModel::sectionCount));

    const QModelIndex project1 = proxy.index(0, 0, {});
    QCOMPARE(project1.data(Qt::DisplayRole).toString(), u"Project 1"_s);
    QCOMPARE(project1.data(TextAutoGenerateChatsModel::Project).toByteArray(), "project1");
    QCOMPARE(proxy.rowCount(project1), 1);
    QCOMPARE(proxy.index(0, 0, project1).data(TextAutoGenerateChatsModel::Identifier).toByteArray(), "chat1");

    // An empty project keeps its own section
    const QModelIndex project2 = proxy.index(1, 0, {});
    QCOMPARE(project2.data(Qt::DisplayRole).toString(), u"Project 2"_s);
    QCOMPARE(proxy.rowCount(project2), 0);

    // A date section has no project identifier, and only holds the chat which belongs to no project
    const QModelIndex today = proxy.index(dateSectionRow(2, TextAutoGenerateChat::SectionHistory::Today), 0, {});
    QVERIFY(today.data(TextAutoGenerateChatsModel::Project).toByteArray().isEmpty());
    QCOMPARE(proxy.rowCount(today), 1);
    QCOMPARE(proxy.index(0, 0, today).data(TextAutoGenerateChatsModel::Identifier).toByteArray(), "chat2");
}

void TextAutoGenerateHistoryListHeadingsProxyModelTest::shouldMoveChatBetweenProjectAndDateSection()
{
    // GIVEN a chat which belongs to no project
    TextAutoGenerateProjectsManager projectsManager;
    projectsManager.setProjects({createProject("project1", u"Project 1"_s)});

    TextAutoGenerateChatsModel chatsModel;
    chatsModel.setTextAutoGenerateProjectsManager(&projectsManager);
    chatsModel.setChats({createChat("chat1")});

    TextAutoGenerateHistoryListHeadingsProxyModel proxy;
    proxy.setSourceModel(&chatsModel);

    const QModelIndex project1 = proxy.index(0, 0, {});
    const QModelIndex today = proxy.index(dateSectionRow(1, TextAutoGenerateChat::SectionHistory::Today), 0, {});
    QCOMPARE(proxy.rowCount(project1), 0);
    QCOMPARE(proxy.rowCount(today), 1);

    // WHEN it is moved to the project
    QVERIFY(chatsModel.setChatProject("chat1", "project1"));

    // THEN it leaves its date section
    QCOMPARE(proxy.rowCount(project1), 1);
    QCOMPARE(proxy.rowCount(today), 0);

    // WHEN it is removed from the project
    QVERIFY(chatsModel.setChatProject("chat1", {}));

    // THEN it comes back to its date section
    QCOMPARE(proxy.rowCount(project1), 0);
    QCOMPARE(proxy.rowCount(today), 1);
}

void TextAutoGenerateHistoryListHeadingsProxyModelTest::shouldFollowProjectChanges()
{
    TextAutoGenerateProjectsManager projectsManager;
    projectsManager.setProjects({createProject("project1", u"Project 1"_s)});

    TextAutoGenerateChatsModel chatsModel;
    chatsModel.setTextAutoGenerateProjectsManager(&projectsManager);
    chatsModel.setChats({createChat("chat1", "project1")});

    TextAutoGenerateHistoryListHeadingsProxyModel proxy;
    proxy.setSourceModel(&chatsModel);
    QCOMPARE(proxy.rowCount({}), 1 + int(TextAutoGenerateHistoryListHeadingsProxyModel::sectionCount));

    // Adding a project adds a section
    projectsManager.addProject(createProject("project2", u"Project 2"_s));
    QCOMPARE(proxy.rowCount({}), 2 + int(TextAutoGenerateHistoryListHeadingsProxyModel::sectionCount));
    QCOMPARE(proxy.index(1, 0, {}).data(Qt::DisplayRole).toString(), u"Project 2"_s);

    // Renaming a project only changes its heading
    projectsManager.updateProject(createProject("project1", u"Renamed"_s));
    QCOMPARE(proxy.index(0, 0, {}).data(Qt::DisplayRole).toString(), u"Renamed"_s);

    // Removing a project removes its section, its chats falling back to their date section
    projectsManager.removeProject("project1");
    QCOMPARE(proxy.rowCount({}), 1 + int(TextAutoGenerateHistoryListHeadingsProxyModel::sectionCount));
    const QModelIndex today = proxy.index(dateSectionRow(1, TextAutoGenerateChat::SectionHistory::Today), 0, {});
    QCOMPARE(proxy.rowCount(today), 1);
    QCOMPARE(proxy.index(0, 0, today).data(TextAutoGenerateChatsModel::Identifier).toByteArray(), "chat1");
}

void TextAutoGenerateHistoryListHeadingsProxyModelTest::shouldOnlyAllowDroppingChatsOnProjects()
{
    TextAutoGenerateProjectsManager projectsManager;
    projectsManager.setProjects({createProject("project1", u"Project 1"_s)});

    TextAutoGenerateChatsModel chatsModel;
    chatsModel.setTextAutoGenerateProjectsManager(&projectsManager);
    chatsModel.setChats({createChat("chat1")});

    TextAutoGenerateHistoryListHeadingsProxyModel proxy;
    proxy.setSourceModel(&chatsModel);

    const QModelIndex project1 = proxy.index(0, 0, {});
    const QModelIndex today = proxy.index(dateSectionRow(1, TextAutoGenerateChat::SectionHistory::Today), 0, {});
    const QModelIndex chat = proxy.index(0, 0, today);
    QVERIFY(chat.isValid());

    // A chat can be dragged, a section can't.
    QVERIFY(chat.flags().testFlag(Qt::ItemIsDragEnabled));
    QVERIFY(!project1.flags().testFlag(Qt::ItemIsDragEnabled));

    // Only a project accepts a drop.
    QVERIFY(project1.flags().testFlag(Qt::ItemIsDropEnabled));
    QVERIFY(!today.flags().testFlag(Qt::ItemIsDropEnabled));
    QVERIFY(!chat.flags().testFlag(Qt::ItemIsDropEnabled));
    QVERIFY(!proxy.flags({}).testFlag(Qt::ItemIsDropEnabled));

    std::unique_ptr<QMimeData> mimeData(proxy.mimeData({chat}));
    QVERIFY(mimeData);
    QCOMPARE(proxy.mimeTypes().count(), 1);
    QVERIFY(mimeData->hasFormat(proxy.mimeTypes().constFirst()));

    // A section carries no chat to drop.
    QVERIFY(!proxy.mimeData({project1}));

    // Dropping somewhere else than on a project, or dropping something else, is refused.
    QVERIFY(!proxy.canDropMimeData(mimeData.get(), Qt::MoveAction, -1, -1, today));
    QVERIFY(!proxy.canDropMimeData(mimeData.get(), Qt::MoveAction, -1, -1, {}));
    QVERIFY(proxy.canDropMimeData(mimeData.get(), Qt::MoveAction, -1, -1, project1));

    QMimeData foreignMimeData;
    foreignMimeData.setText(u"foo"_s);
    QVERIFY(!proxy.canDropMimeData(&foreignMimeData, Qt::MoveAction, -1, -1, project1));
}

void TextAutoGenerateHistoryListHeadingsProxyModelTest::shouldRequestMoveWhenDroppingChatOnProject()
{
    TextAutoGenerateProjectsManager projectsManager;
    projectsManager.setProjects({createProject("project1", u"Project 1"_s)});

    TextAutoGenerateChatsModel chatsModel;
    chatsModel.setTextAutoGenerateProjectsManager(&projectsManager);
    chatsModel.setChats({createChat("chat1")});

    TextAutoGenerateHistoryListHeadingsProxyModel proxy;
    proxy.setSourceModel(&chatsModel);

    const QModelIndex project1 = proxy.index(0, 0, {});
    const QModelIndex today = proxy.index(dateSectionRow(1, TextAutoGenerateChat::SectionHistory::Today), 0, {});
    std::unique_ptr<QMimeData> mimeData(proxy.mimeData({proxy.index(0, 0, today)}));
    QVERIFY(mimeData);

    // WHEN
    QSignalSpy moveRequestedSpy(&proxy, &TextAutoGenerateHistoryListHeadingsProxyModel::moveChatToProjectRequested);
    QVERIFY(proxy.dropMimeData(mimeData.get(), Qt::MoveAction, -1, -1, project1));

    // THEN the model only asks for the move: it doesn't store the chats itself.
    QCOMPARE(moveRequestedSpy.count(), 1);
    QCOMPARE(moveRequestedSpy.at(0).at(0).toByteArray(), "chat1"_ba);
    QCOMPARE(moveRequestedSpy.at(0).at(1).toByteArray(), "project1"_ba);
    QCOMPARE(proxy.rowCount(project1), 0);

    QVERIFY(!proxy.dropMimeData(mimeData.get(), Qt::MoveAction, -1, -1, today));
    QCOMPARE(moveRequestedSpy.count(), 1);
}

#include "moc_textautogeneratehistorylistheadingsproxymodeltest.cpp"
#include "textautogeneratehistorylistheadingsproxymodeltest.moc"
