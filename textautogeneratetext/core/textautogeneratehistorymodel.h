/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratehistoryinfo.h"
#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <QList>

namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateHistoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum HistoryRole : uint16_t {
        Subject = Qt::UserRole + 1,
        DateTime,
        Model,
        Engine,
        ReferenceUuid,
    };

    explicit TextAutoGenerateHistoryModel(QObject *parent = nullptr);
    ~TextAutoGenerateHistoryModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] QList<TextAutoGenerateHistoryInfo> historyInfos() const;
    void setHistoryInfos(const QList<TextAutoGenerateHistoryInfo> &newHistoryInfos);

    void clear();
    void addInfo(const TextAutoGenerateHistoryInfo &msg);

    [[nodiscard]] bool removeInfo(const QByteArray &uuid);

private:
    QList<TextAutoGenerateHistoryInfo> mHistoryInfos;
};
}
