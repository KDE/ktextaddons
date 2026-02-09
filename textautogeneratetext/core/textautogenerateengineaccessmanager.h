/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
class QNetworkAccessManager;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateEngineAccessManager
 * \brief The TextAutoGenerateEngineAccessManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateEngineAccessManager
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateEngineAccessManager : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateEngineAccessManager(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateEngineAccessManager();

    /*!
     */
    static TextAutoGenerateEngineAccessManager *self();

    /*!
     */
    [[nodiscard]] QNetworkAccessManager *networkManager() const;

private:
    QNetworkAccessManager *const mNetworkAccessManager;
};
}
