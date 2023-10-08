/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libvoskspeechtotext_export.h"

#include "voskspeechtotextinfo.h"
#include <QAbstractListModel>

class LIBVOSKSPEECHTOTEXT_EXPORT VoskSpeechToTextModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VoskRoles {};

    Q_ENUM(VoskRoles)

    explicit VoskSpeechToTextModel(QObject *parent = nullptr);
    ~VoskSpeechToTextModel() override;

    Q_REQUIRED_RESULT int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role) const override;

    void clear();

    Q_REQUIRED_RESULT QVector<VoskSpeechToTextInfo> speechToTextInfo() const;
    void setSpeechToTextInfo(const QVector<VoskSpeechToTextInfo> &newSpeechToTextInfo);

private:
    QVector<VoskSpeechToTextInfo> mSpeechToTextInfo;
};
