/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "voskspeechtotextinfo.h"
#include <QAbstractListModel>

class VoskSpeechToTextModel : public QAbstractListModel
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

private:
    QVector<VoskSpeechToTextInfo> mSpeechToTextInfo;
};
