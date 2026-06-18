/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistheadingsproxymodeltest.h"
#include "core/models/textautogeneratehistorylistheadingsproxymodel.h"

#include <QAbstractListModel>
#include <QTest>

using namespace TextAutoGenerateText;

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
            return QVariant::fromValue(TextAutoGenerateChatsModel::SectionHistory(mSections.at(index.row())));
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
    model.setSections({int(TextAutoGenerateChatsModel::SectionHistory::Today)});

    TextAutoGenerateHistoryListHeadingsProxyModel proxy;
    proxy.setSourceModel(&model);

    QVERIFY(!proxy.index(999, 0, {}).isValid());
    QVERIFY(!proxy.index(0, 1, {}).isValid());

    const QModelIndex sectionToday = proxy.index(int(TextAutoGenerateChatsModel::SectionHistory::Today), 0, {});
    QVERIFY(sectionToday.isValid());

    QVERIFY(proxy.index(0, 0, sectionToday).isValid());
    QVERIFY(!proxy.index(999, 0, sectionToday).isValid());
}

#include "moc_textautogeneratehistorylistheadingsproxymodeltest.cpp"
#include "textautogeneratehistorylistheadingsproxymodeltest.moc"
