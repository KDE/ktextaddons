/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
class QDebig;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGeneratePrompt
 * \brief The TextAutoGeneratePrompt class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGeneratePrompt
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGeneratePrompt
{
public:
    /*!
     * \brief TextAutoGeneratePrompt
     */
    TextAutoGeneratePrompt();
    /*!
     * \brief TextAutoGeneratePrompt
     */
    ~TextAutoGeneratePrompt();

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] QString text() const;
    /*!
     */
    void setText(const QString &newText);

private:
    QString mName;
    QString mText;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGeneratePrompt, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGeneratePrompt &t);
