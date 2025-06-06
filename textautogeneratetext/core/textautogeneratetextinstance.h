/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"

#include <QDebug>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstance
{
public:
    TextAutoGenerateTextInstance();
    ~TextAutoGenerateTextInstance();

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QString pluginName() const;
    void setPluginName(const QString &newPluginName);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] QByteArray instanceUuid() const;
    void setInstanceUuid(const QByteArray &newInstanceUuid);

private:
    QString mName;
    QString mPluginName;
    QByteArray mInstanceUuid;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextInstance, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextInstance &t);
