/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libbergamot_private_export.h"
#include "translator.h"
#include <QAbstractListModel>

class LIBBERGAMOT_TESTS_EXPORT TranslatorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TranslatorRoles {
        Source = Qt::UserRole + 1,
        Target,
        TypeTranslator,
        Repository,
        Version,
        Available,
        LastColumn = Available,
    };

    Q_ENUM(TranslatorRoles)

    explicit TranslatorModel(QObject *parent = nullptr);
    ~TranslatorModel() override;

    Q_REQUIRED_RESULT int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role) const override;

    void clear();

    void insertTranslators(const QVector<Translator> &translators);

    Q_REQUIRED_RESULT QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Q_REQUIRED_RESULT int columnCount(const QModelIndex &parent) const override;

protected:
private:
    QVector<Translator> mTranslators;
};
