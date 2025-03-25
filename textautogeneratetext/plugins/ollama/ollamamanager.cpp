/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamanager.h"
#include "ollamautils.h"
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>

OllamaManager::OllamaManager(QObject *parent)
    : QObject{parent}
{
}

OllamaManager::~OllamaManager() = default;

void OllamaManager::loadModels()
{
    /*
      QNetworkRequest req{QUrl::fromUserInput(m_ollamaUrl + OllamaUtils::tagsPath())};
      req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
      auto rep = m_manager->get(req);
      m_ollamaCheck = connect(rep, &QNetworkReply::finished, this, [this, rep] {
          if (rep->error() != QNetworkReply::NoError) {
              Q_EMIT errorOccurred(i18n("Failed to connect to interface at %1: %2", m_ollamaUrl, rep->errorString()));
              m_hasError = true;
              Q_EMIT readyChanged();
              Q_EMIT hasErrorChanged();
              return;
          }

          const auto json = QJsonDocument::fromJson(rep->readAll());
          const auto models = json["models"_L1].toArray();
          for (const QJsonValue &model : models) {
              m_models.push_back(model["name"_L1].toString());
          }
          Q_EMIT modelsChanged();

          m_ready = !m_models.isEmpty();
          m_hasError = false;
          Q_EMIT readyChanged();
          Q_EMIT hasErrorChanged();
      });
      */
}

QDebug operator<<(QDebug d, const OllamaManager::ModelsInfo &t)
{
    d.space() << "models:" << t.models;
    d.space() << "hasError:" << t.hasError;
    d.space() << "isReady:" << t.isReady;
    return d;
}
#include "moc_ollamamanager.cpp"
