/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QAbstractListModel>

class VoskSpeechToTextModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit VoskSpeechToTextModel(QObject *parent = nullptr);
    ~VoskSpeechToTextModel() override;
};
