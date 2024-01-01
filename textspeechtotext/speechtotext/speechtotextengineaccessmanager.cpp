/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextengineaccessmanager.h"

#include <QNetworkAccessManager>

using namespace TextSpeechToText;
SpeechToTextEngineAccessManager::SpeechToTextEngineAccessManager(QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
}

SpeechToTextEngineAccessManager::~SpeechToTextEngineAccessManager() = default;

SpeechToTextEngineAccessManager *SpeechToTextEngineAccessManager::self()
{
    static SpeechToTextEngineAccessManager s_self;
    return &s_self;
}

QNetworkAccessManager *SpeechToTextEngineAccessManager::networkManager() const
{
    return mNetworkAccessManager;
}

#include "moc_speechtotextengineaccessmanager.cpp"
