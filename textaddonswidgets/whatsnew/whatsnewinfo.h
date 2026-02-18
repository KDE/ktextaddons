/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <QMetaType>
#include <QStringList>
#include <qnamespace.h>

class QDebug;
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::WhatsNewInfo
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/WhatsNewInfo
 *
 * \brief The WhatsNewInfo class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT WhatsNewInfo
{
public:
    /*!
     * \brief Constructor for WhatsNewInfo
     */
    WhatsNewInfo();
    /*!
     * \brief Destructor for WhatsNewInfo
     */
    ~WhatsNewInfo();

    /*!
     * \brief Returns the list of changes
     * \return A string list of changes
     */
    [[nodiscard]] QStringList changes() const;
    /*!
     * \brief Sets the list of changes
     * \param newChanges A string list of changes to set
     */
    void setChanges(const QStringList &newChanges);

    /*!
     * \brief Returns the list of new features
     * \return A string list of new features
     */
    [[nodiscard]] QStringList newFeatures() const;
    /*!
     * \brief Sets the list of new features
     * \param newNewFeatures A string list of new features to set
     */
    void setNewFeatures(const QStringList &newNewFeatures);

    /*!
     * \brief Returns the list of bug fixings
     * \return A string list of bug fixings
     */
    [[nodiscard]] QStringList bugFixings() const;
    /*!
     * \brief Sets the list of bug fixings
     * \param newBugFixings A string list of bug fixings to set
     */
    void setBugFixings(const QStringList &newBugFixings);

    /*!
     * \brief Returns the version string
     * \return The version string
     */
    [[nodiscard]] QString version() const;
    /*!
     * \brief Sets the version string
     * \param newVersion The version string to set
     */
    void setVersion(const QString &newVersion);

private:
    QString mVersion;
    QStringList mChanges;
    QStringList mNewFeatures;
    QStringList mBugFixings;
};
}
QT_DECL_METATYPE_EXTERN_TAGGED(TextAddonsWidgets::WhatsNewInfo, TextAddonsWidgets__WhatsNewInfo, TEXTADDONSWIDGETS_EXPORT)
Q_DECLARE_TYPEINFO(TextAddonsWidgets::WhatsNewInfo, Q_RELOCATABLE_TYPE);
TEXTADDONSWIDGETS_EXPORT QDebug operator<<(QDebug d, const TextAddonsWidgets::WhatsNewInfo &t);
