/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "translatorengineaccessmanager.h"
using namespace Qt::Literals::StringLiterals;

#include <QNetworkAccessManager>

using namespace TextTranslator;
TranslatorEngineAccessManager::TranslatorEngineAccessManager(QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
}

TranslatorEngineAccessManager::~TranslatorEngineAccessManager() = default;

TranslatorEngineAccessManager *TranslatorEngineAccessManager::self()
{
    static TranslatorEngineAccessManager s_self;
    return &s_self;
}

QNetworkAccessManager *TranslatorEngineAccessManager::networkManager() const
{
    return mNetworkAccessManager;
}

#include "moc_translatorengineaccessmanager.cpp"
