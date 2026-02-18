/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <KMessageWidget>
#include <TextAddonsWidgets/NeedUpdateVersionUtils>
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::NeedUpdateVersionWidget
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/NeedUpdateVersionWidget
 *
 * \brief The NeedUpdateVersionWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT NeedUpdateVersionWidget : public KMessageWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for NeedUpdateVersionWidget
     * \param parent The parent widget
     */
    explicit NeedUpdateVersionWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for NeedUpdateVersionWidget
     */
    ~NeedUpdateVersionWidget() override;

    /*!
     * \brief Sets the obsolete version status
     * \param obsolete The obsolete version type
     */
    void setObsoleteVersion(NeedUpdateVersionUtils::ObsoleteVersion obsolete);

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotDisableVersionCheck();
};
}
