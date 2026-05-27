/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textaddonswidgets_export.h"

#include <QCoreApplication>
#include <QDialog>

namespace TextAddonsWidgets
{
class WhatsNewNgWidget;
/*!
 * \class TextAddonsWidgets::WhatsNewDialogNg
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/WhatsNewDialogNg
 *
 * \brief The WhatsNewDialogNg class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT WhatsNewNgDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for WhatsNewDialogNg
     * \param parent The parent widget
     * \param applicationName The name of the application
     */
    explicit WhatsNewNgDialog(const QString &applicationId, const QString &applicationName, QWidget *parent = nullptr);
    explicit WhatsNewNgDialog(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for WhatsNewDialog
     */
    ~WhatsNewNgDialog() override;

private:
    TEXTADDONSWIDGETS_NO_EXPORT void initialize();
    TEXTADDONSWIDGETS_NO_EXPORT void readConfig();
    TEXTADDONSWIDGETS_NO_EXPORT void writeConfig();
    WhatsNewNgWidget *const mWhatsNewWidget;
};
}
