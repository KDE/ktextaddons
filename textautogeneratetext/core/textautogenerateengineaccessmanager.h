/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
class QNetworkAccessManager;
namespace TextAutogenerateText
{
/**
 * @brief The TextAutogenerateEngineAccessManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateEngineAccessManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateEngineAccessManager(QObject *parent = nullptr);
    ~TextAutogenerateEngineAccessManager();

    static TextAutogenerateEngineAccessManager *self();

    QNetworkAccessManager *networkManager() const;

private:
    QNetworkAccessManager *const mNetworkAccessManager;
};
}
