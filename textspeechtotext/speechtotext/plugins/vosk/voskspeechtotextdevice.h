/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libvoskspeechtotext_export.h"
#include <QIODevice>

class LIBVOSKSPEECHTOTEXT_EXPORT VoskSpeechToTextDevice : public QIODevice
{
    Q_OBJECT
public:
    explicit VoskSpeechToTextDevice(QObject *parent = nullptr);
    ~VoskSpeechToTextDevice() override;

protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
};
