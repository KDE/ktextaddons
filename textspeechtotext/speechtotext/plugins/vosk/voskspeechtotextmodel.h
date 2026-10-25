/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

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
        Active,
        Url,
        LastColumn = Url,
    };

    Q_ENUM(VoskRoles)

    explicit VoskSpeechToTextModel(QObject *parent = nullptr);
    ~VoskSpeechToTextModel() override;

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    void clear();

    [[nodiscard]] QList<VoskSpeechToTextInfo> speechToTextInfos() const;
    void setSpeechToTextInfos(const QList<VoskSpeechToTextInfo> &newSpeechToTextInfo);

    void updateInstalledLanguage();

    void removeLanguage(const QString &name);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    [[nodiscard]] QString activeLanguage() const;
    void setActiveLanguage(const QString &newActiveLanguage);

private:
    int columnCount(const QModelIndex &parent) const override;
    [[nodiscard]] LIBVOSKSPEECHTOTEXT_NO_EXPORT bool isInstalled(const QString &shortName) const;
    [[nodiscard]] LIBVOSKSPEECHTOTEXT_NO_EXPORT QString versionInstalled(const QString &shortName) const;
    [[nodiscard]] LIBVOSKSPEECHTOTEXT_NO_EXPORT bool needToUpdateLanguageModel(const VoskSpeechToTextInfo &language) const;
    [[nodiscard]] LIBVOSKSPEECHTOTEXT_NO_EXPORT bool isActive(const VoskSpeechToTextInfo &language) const;
    QList<VoskSpeechToTextInfo> mSpeechToTextInfos;
    QList<VoskEngineUtils::LanguageInstalled> mLanguageInstalled;
    QString mActiveLanguage;
};
