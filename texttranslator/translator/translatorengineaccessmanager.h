/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "texttranslator_export.h"
#include <QObject>
class QNetworkAccessManager;
namespace TextTranslator
{
/*!
 * \class TranslatorEngineAccessManager
 * \inheaderfile TextTranslator/TranslatorEngineAccessManager
 * \inmodule TextTranslator
 * \brief Manages network access for translation engines.
 */
class TEXTTRANSLATOR_EXPORT TranslatorEngineAccessManager : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit TranslatorEngineAccessManager(QObject *parent = nullptr);
    /*!
     */
    ~TranslatorEngineAccessManager();

    /*!
     */
    static TranslatorEngineAccessManager *self();

    /*!
     */
    QNetworkAccessManager *networkManager() const;

private:
    QNetworkAccessManager *const mNetworkAccessManager;
};
}
