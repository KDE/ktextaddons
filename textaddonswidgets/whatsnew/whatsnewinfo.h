/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <QDebug>
#include <QStringList>
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT WhatsNewInfo
{
public:
    WhatsNewInfo();
    ~WhatsNewInfo();

    [[nodiscard]] QStringList changes() const;
    void setChanges(const QStringList &newChanges);

    [[nodiscard]] QStringList newFeatures() const;
    void setNewFeatures(const QStringList &newNewFeatures);

    [[nodiscard]] QStringList bugFixings() const;
    void setBugFixings(const QStringList &newBugFixings);

    [[nodiscard]] QString version() const;
    void setVersion(const QString &newVersion);

private:
    QString mVersion;
    QStringList mChanges;
    QStringList mNewFeatures;
    QStringList mBugFixings;
};
}
Q_DECLARE_METATYPE(TextAddonsWidgets::WhatsNewInfo)
Q_DECLARE_TYPEINFO(TextAddonsWidgets::WhatsNewInfo, Q_RELOCATABLE_TYPE);
TEXTADDONSWIDGETS_EXPORT QDebug operator<<(QDebug d, const TextAddonsWidgets::WhatsNewInfo &t);
