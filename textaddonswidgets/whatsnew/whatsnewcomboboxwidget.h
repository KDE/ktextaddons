/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"
#include <QWidget>
class QComboBox;
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::WhatsNewComboBoxWidget
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/WhatsNewComboBoxWidget
 *
 * \brief The WhatsNewComboBoxWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT WhatsNewComboBoxWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for WhatsNewComboBoxWidget
     * \param parent The parent widget
     */
    explicit WhatsNewComboBoxWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for WhatsNewComboBoxWidget
     */
    ~WhatsNewComboBoxWidget() override;

    /*!
     * \brief Adds a version to the combo box
     * \param name The name of the version
     * \param identifier The identifier for the version
     */
    void addVersion(const QString &name, int identifier);

    /*!
     * \brief Initializes the version combo box
     * \param type The type to initialize
     */
    void initializeVersion(int type);

Q_SIGNALS:
    /*!
     * \brief Emitted when the version selection changes
     * \param type The type of version selected
     */
    void versionChanged(int type);

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotCurrentIndexChanged(int index);
    QComboBox *const mVersionComboBox;
};
}
