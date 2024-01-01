/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
class QNetworkAccessManager;
namespace TextSpeechToText
{
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextEngineAccessManager : public QObject
{
    Q_OBJECT
public:
    explicit SpeechToTextEngineAccessManager(QObject *parent = nullptr);
    ~SpeechToTextEngineAccessManager();

    static SpeechToTextEngineAccessManager *self();

    QNetworkAccessManager *networkManager() const;

private:
    QNetworkAccessManager *const mNetworkAccessManager;
};
}
