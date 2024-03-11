/*
  SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>
namespace TextTranslator
{
/**
 * @brief The NetworkManager class
 * @author Laurent Montel <montel@kde.org>
 */
class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager() override;
    static NetworkManager *self();

    [[nodiscard]] bool isOnline() const;

Q_SIGNALS:
    void networkStatusChanged(bool isOnline);
};
}
