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
 * \class TextAutoGenerateText::TextAutoGenerateAgent
 * \brief The TextAutoGenerateAgent class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateAgent
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAgent
{
public:
    /*!
     * \brief TextAutoGenerateAgent
     */
    TextAutoGenerateAgent();
    /*!
     * \brief TextAutoGenerateAgent
     */
    ~TextAutoGenerateAgent();

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] QString description() const;
    /*!
     */
    void setDescription(const QString &newDescription);

private:
    QString mName;
    QString mDescription;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateAgent, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAgent &t);
