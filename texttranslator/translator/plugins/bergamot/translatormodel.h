/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "bergamotengineutils.h"
#include "libbergamot_private_export.h"
#include "translator.h"
#include <QAbstractListModel>

class LIBBERGAMOT_TESTS_EXPORT TranslatorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TranslatorRoles {
        Source,
        Target,
        TypeTranslator,
        Repository,
        InstalledVersion,
        AvailableVersion,
        Installed,
        CheckSum,
        Identifier,
        NeedToUpdateLanguage,
        Url,
        LastColumn = Url,
    };

    Q_ENUM(TranslatorRoles)

    explicit TranslatorModel(QObject *parent = nullptr);
    ~TranslatorModel() override;

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    void clear();

    void insertTranslators(const QVector<Translator> &translators);

    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

    void removeLanguage(const QString &identifier);

    void updateInstalledLanguage();

private:
    [[nodiscard]] bool isInstalled(const QString &shortName) const;
    [[nodiscard]] int versionInstalled(const QString &shortName) const;
    [[nodiscard]] bool needToUpdateLanguageModel(const Translator &translator) const;
    QVector<Translator> mTranslators;
    QVector<BergamotEngineUtils::LanguageInstalled> mLanguageInstalled;
};
