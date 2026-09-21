/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QColor>
#include <QString>
class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTag
 * \brief The TextAutoGenerateTag class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateTag
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTag
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTag
{
public:
    TextAutoGenerateTag();

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QByteArray identifier() const;
    void setIdentifier(const QByteArray &newIdentifier);

    [[nodiscard]] QColor color() const;
    void setColor(const QColor &newColor);

private:
    QString mName;
    QByteArray mIdentifier;
    QColor mColor;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTag, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTag &t);
