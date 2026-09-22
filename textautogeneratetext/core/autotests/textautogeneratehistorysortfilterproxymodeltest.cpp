/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorysortfilterproxymodeltest.h"
#include "core/models/textautogeneratechatsmodel.h"
#include "core/models/textautogeneratehistorylistheadingsproxymodel.h"
#include "core/models/textautogeneratehistorysortfilterproxymodel.h"
#include "core/textautogenerateprojectsmanager.h"
#include <QMimeData>
#include <QSignalSpy>
#include <QTest>
#include <algorithm>
QTEST_GUILESS_MAIN(TextAutoGenerateHistorySortFilterProxyModelTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

namespace
{
[[nodiscard]] TextAutoGenerateChat createChat(const QByteArray &identifier, const QString &title, const QList<QByteArray> &tags)
{
    TextAutoGenerateChat chat;
    chat.setIdentifier(identifier);
    chat.setTitle(title);
    chat.setTags(tags);
    return chat;
}

/*! Returns the identifiers of the chats the proxy shows, sections excluded. */
[[nodiscard]] QList<QByteArray> visibleChats(const QAbstractItemModel &model)
{
    QList<QByteArray> identifiers;
    for (int section = 0, sectionCount = model.rowCount({}); section < sectionCount; ++section) {
        const QModelIndex sectionIndex = model.index(section, 0, {});
        for (int row = 0, rowCount = model.rowCount(sectionIndex); row < rowCount; ++row) {
            identifiers.append(model.index(row, 0, sectionIndex).data(TextAutoGenerateChatsModel::Identifier).toByteArray());
        }
    }
    // The chats are sorted by date, which the test does not set: compare the content, not the order.
    std::sort(identifiers.begin(), identifiers.end());
    return identifiers;
}
}

TextAutoGenerateHistorySortFilterProxyModelTest::TextAutoGenerateHistorySortFilterProxyModelTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateHistorySortFilterProxyModelTest::shouldHaveDefaultValues()
{
    TextAutoGenerateHistorySortFilterProxyModel proxy;
    QVERIFY(proxy.filterTags().isEmpty());
    QVERIFY(!proxy.showArchived());
}

void TextAutoGenerateHistorySortFilterProxyModelTest::shouldFilterByTags()
{
    TextAutoGenerateChatsModel chatsModel;
    chatsModel.addChat(createChat("chat1"_ba, u"chat1"_s, {"tag1"_ba}));
    chatsModel.addChat(createChat("chat2"_ba, u"chat2"_s, {"tag1"_ba, "tag2"_ba}));
    chatsModel.addChat(createChat("chat3"_ba, u"chat3"_s, {}));

    TextAutoGenerateHistoryListHeadingsProxyModel headingsModel;
    headingsModel.setSourceModel(&chatsModel);

    TextAutoGenerateHistorySortFilterProxyModel proxy;
    proxy.setSourceModel(&headingsModel);

    // No tag selected: no filtering at all.
    QCOMPARE(visibleChats(proxy).count(), 3);

    proxy.setFilterTags({"tag2"_ba});
    QCOMPARE(proxy.filterTags(), QList<QByteArray>{"tag2"_ba});
    QCOMPARE(visibleChats(proxy), QList<QByteArray>{"chat2"_ba});

    // A chat matches as soon as it has one of the selected tags.
    proxy.setFilterTags({"tag1"_ba, "tag2"_ba});
    const QList<QByteArray> expected{"chat1"_ba, "chat2"_ba};
    QCOMPARE(visibleChats(proxy), expected);

    // An unknown tag hides everything, no chat uses it.
    proxy.setFilterTags({"unknown"_ba});
    QVERIFY(visibleChats(proxy).isEmpty());

    proxy.setFilterTags({});
    QCOMPARE(visibleChats(proxy).count(), 3);
}

void TextAutoGenerateHistorySortFilterProxyModelTest::shouldDropChatOnProjectThroughTheWholeChain()
{
    // GIVEN the model chain a history view uses
    TextAutoGenerateProjectsManager projectsManager;
    TextAutoGenerateProject project;
    project.setIdentifier("project1");
    project.setName(u"Project 1"_s);
    projectsManager.setProjects({project});

    TextAutoGenerateChatsModel chatsModel;
    chatsModel.setTextAutoGenerateProjectsManager(&projectsManager);
    chatsModel.setChats({createChat("chat1", u"Chat 1"_s, {})});

    TextAutoGenerateHistoryListHeadingsProxyModel headingsProxy;
    headingsProxy.setSourceModel(&chatsModel);

    TextAutoGenerateHistorySortFilterProxyModel proxy;
    proxy.setSourceModel(&headingsProxy);

    // THEN dragging and dropping use the same action: QAbstractItemView only drops when the action
    // the drag was started with is one of the supported drop actions, and both are forwarded from
    // the source model through the proxies.
    QCOMPARE(proxy.supportedDragActions(), Qt::MoveAction);
    QCOMPARE(proxy.supportedDropActions(), Qt::MoveAction);

    QModelIndex projectSection;
    QModelIndex chatIndex;
    for (int section = 0, sectionCount = proxy.rowCount({}); section < sectionCount; ++section) {
        const QModelIndex sectionIndex = proxy.index(section, 0, {});
        if (sectionIndex.data(TextAutoGenerateChatsModel::Project).toByteArray() == "project1") {
            projectSection = sectionIndex;
        }
        for (int row = 0, rowCount = proxy.rowCount(sectionIndex); row < rowCount; ++row) {
            const QModelIndex idx = proxy.index(row, 0, sectionIndex);
            if (idx.data(TextAutoGenerateChatsModel::Identifier).toByteArray() == "chat1") {
                chatIndex = idx;
            }
        }
    }
    QVERIFY(projectSection.isValid());
    QVERIFY(chatIndex.isValid());
    QVERIFY(chatIndex.flags().testFlag(Qt::ItemIsDragEnabled));
    QVERIFY(projectSection.flags().testFlag(Qt::ItemIsDropEnabled));

    // WHEN the chat is dropped on the project
    std::unique_ptr<QMimeData> mimeData(proxy.mimeData({chatIndex}));
    QVERIFY(mimeData);
    QSignalSpy moveRequestedSpy(&headingsProxy, &TextAutoGenerateHistoryListHeadingsProxyModel::moveChatToProjectRequested);
    QVERIFY(proxy.canDropMimeData(mimeData.get(), Qt::MoveAction, -1, -1, projectSection));
    QVERIFY(proxy.dropMimeData(mimeData.get(), Qt::MoveAction, -1, -1, projectSection));

    // THEN the move is requested, and removing the dragged row is refused, as a drop only moves the
    // chat to another section.
    QCOMPARE(moveRequestedSpy.count(), 1);
    QCOMPARE(moveRequestedSpy.at(0).at(0).toByteArray(), "chat1"_ba);
    QCOMPARE(moveRequestedSpy.at(0).at(1).toByteArray(), "project1"_ba);
    QVERIFY(!proxy.removeRows(chatIndex.row(), 1, chatIndex.parent()));
    QCOMPARE(chatsModel.rowCount(), 1);
}

#include "moc_textautogeneratehistorysortfilterproxymodeltest.cpp"
