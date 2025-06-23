/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateengineaccessmanager.h"
using namespace Qt::Literals::StringLiterals;

#include <QNetworkAccessManager>

using namespace TextAutoGenerateText;
TextAutoGenerateEngineAccessManager::TextAutoGenerateEngineAccessManager(QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
}

TextAutoGenerateEngineAccessManager::~TextAutoGenerateEngineAccessManager() = default;

TextAutoGenerateEngineAccessManager *TextAutoGenerateEngineAccessManager::self()
{
    static TextAutoGenerateEngineAccessManager s_self;
    return &s_self;
}

QNetworkAccessManager *TextAutoGenerateEngineAccessManager::networkManager() const
{
    return mNetworkAccessManager;
}

#include "moc_textautogenerateengineaccessmanager.cpp"
