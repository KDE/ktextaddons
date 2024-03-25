/*
  SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QAbstractListModel>
namespace TextAutoCorrectionWidgets
{
class AutoCorrectionLanguageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AutoCorrectionLanguageModelRoles {
        LocaleI18n = Qt::UserRole + 1,
        Locale,
    };
    Q_ENUM(AutoCorrectionLanguageModelRoles)

    explicit AutoCorrectionLanguageModel(QObject *parent = nullptr);
    ~AutoCorrectionLanguageModel() override;

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    [[nodiscard]] QString language(int index) const;

private:
    struct LocaleInfo {
        QString localeTranslated;
        QString localeCode;
    };
    void fillModel();

    QList<LocaleInfo> mLocalInfos;
};
}
