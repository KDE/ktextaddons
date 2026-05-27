/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <KAboutData>
#include <KMessageWidget>

namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::WhatsNewMessageNgWidget
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/WhatsNewMessageNgWidget
 *
 * \brief The WhatsNewMessageNgWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT WhatsNewMessageNgWidget : public KMessageWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for WhatsNewMessageNgWidget
     * \param applicationName
     * \param parent
     */
    explicit WhatsNewMessageNgWidget(const QString &applicationName, QWidget *parent = nullptr);
    /*!
     * \brief Constructor for WhatsNewMessageNgWidget
     * \param parent
     */
    explicit WhatsNewMessageNgWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for WhatsNewMessageNgWidget
     */
    ~WhatsNewMessageNgWidget() override;
    /*!
     * \brief setReleases
     * \param info
     */
    void setReleases(const QList<KAboutRelease> &info);

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotLinkActivated(const QString &contents);
    QString mApplicationName;
    QList<KAboutRelease> mReleasesInfo;
};
}
