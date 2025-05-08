/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateengineaccessmanager.h"

#include <QNetworkAccessManager>

using namespace TextAutoGenerateText;
TextAutogenerateEngineAccessManager::TextAutogenerateEngineAccessManager(QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
}

TextAutogenerateEngineAccessManager::~TextAutogenerateEngineAccessManager() = default;

TextAutogenerateEngineAccessManager *TextAutogenerateEngineAccessManager::self()
{
    static TextAutogenerateEngineAccessManager s_self;
    return &s_self;
}

QNetworkAccessManager *TextAutogenerateEngineAccessManager::networkManager() const
{
    return mNetworkAccessManager;
}

#include "moc_textautogenerateengineaccessmanager.cpp"
