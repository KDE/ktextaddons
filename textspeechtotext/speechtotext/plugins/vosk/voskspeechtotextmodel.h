/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libvoskspeechtotext_export.h"
#include "voskengineutils.h"

#include "voskspeechtotextinfo.h"
#include <QAbstractListModel>

class LIBVOSKSPEECHTOTEXT_EXPORT VoskSpeechToTextModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VoskRoles {
        Identifier,
        LangText,
        Size,
        SizeByte,
        CheckSum,
        Installed,
        AvailableVersion,
        InstalledVersion,
        NeedToUpdateLanguage,
        Name,
        Url,
        LastColumn = Url,
    };

    Q_ENUM(VoskRoles)

    explicit VoskSpeechToTextModel(QObject *parent = nullptr);
    ~VoskSpeechToTextModel() override;

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    void clear();

    [[nodiscard]] QVector<VoskSpeechToTextInfo> speechToTextInfos() const;
    void setSpeechToTextInfos(const QVector<VoskSpeechToTextInfo> &newSpeechToTextInfo);

    void updateInstalledLanguage();

    void removeLanguage(const QString &name);

protected:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    int columnCount(const QModelIndex &parent) const override;

private:
    [[nodiscard]] bool isInstalled(const QString &shortName) const;
    [[nodiscard]] QString versionInstalled(const QString &shortName) const;
    [[nodiscard]] bool needToUpdateLanguageModel(const VoskSpeechToTextInfo &language) const;
    QVector<VoskSpeechToTextInfo> mSpeechToTextInfos;
    QVector<VoskEngineUtils::LanguageInstalled> mLanguageInstalled;
};
