/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textautogeneratemenutextinfo.h"
#include "textautogeneratetext_private_export.h"

#include <QAbstractListModel>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateMenuModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMenuModel(QObject *parent = nullptr);
    ~TextAutoGenerateMenuModel() override;

    enum AiTextRoles : uint16_t {
        TextRole = Qt::UserRole + 1,
        EnabledRole,
    };

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    [[nodiscard]] QList<TextAutoGenerateMenuTextInfo> infos() const;
    void setInfos(const QList<TextAutoGenerateMenuTextInfo> &newAskItems);

    void addItem(const TextAutoGenerateMenuTextInfo &msg);
    void removeInfo(int index);

private:
    QList<TextAutoGenerateMenuTextInfo> mTextInfos;
};
}
