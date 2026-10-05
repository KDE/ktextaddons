/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <KMessageWidget>
#include <TextAddonsWidgets/WhatsNewInfo>

#include <QCoreApplication>

namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::WhatsNewMessageWidget
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/WhatsNewMessageWidget
 *
 * \brief The WhatsNewMessageWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT WhatsNewMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for WhatsNewMessageWidget
     * \param parent The parent widget
     * \param applicationName The name of the application
     */
    explicit WhatsNewMessageWidget(QWidget *parent = nullptr, const QString &applicationName = QCoreApplication::applicationName());
    /*!
     * \brief Destructor for WhatsNewMessageWidget
     */
    ~WhatsNewMessageWidget() override;

    /*!
     * \brief Sets the WhatsNew information to display
     * \param infos A list of WhatsNewInfo objects to display
     */
    void setWhatsNewInfos(const QList<TextAddonsWidgets::WhatsNewInfo> &infos);

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotLinkActivated(const QString &contents);
    QList<TextAddonsWidgets::WhatsNewInfo> mWhatsNewInfos;
    QString mApplicationName;
};
}
