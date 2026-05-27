/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

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
     * \param parent The parent widget
     * \param applicationName The name of the application
     */
    explicit WhatsNewMessageNgWidget(const QString &applicationId, const QString &applicationName, QWidget *parent = nullptr);
    explicit WhatsNewMessageNgWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for WhatsNewMessageNgWidget
     */
    ~WhatsNewMessageNgWidget() override;

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotLinkActivated(const QString &contents);
    QString mApplicationName;
    QString mApplicationId;
};
}
