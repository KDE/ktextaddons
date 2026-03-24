/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolBaseJob
 * \brief The TextAutoGenerateTextToolBaseJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolBaseJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolBaseJob : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextToolBaseJob(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextToolBaseJob() override;

    /*!
     */
    virtual void start() = 0;
    /*!
     */
    [[nodiscard]] virtual bool canStart() const = 0;
};
}
