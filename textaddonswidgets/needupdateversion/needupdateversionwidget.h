/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <KMessageWidget>
#include <TextAddonsWidgets/NeedUpdateVersionUtils>
namespace TextAddonsWidgets
{
/**
 * @brief The NeedUpdateVersionWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT NeedUpdateVersionWidget : public KMessageWidget
{
    Q_OBJECT
public:
    explicit NeedUpdateVersionWidget(QWidget *parent = nullptr);
    ~NeedUpdateVersionWidget() override;

    void setObsoleteVersion(NeedUpdateVersionUtils::ObsoleteVersion obsolete);

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotDisableVersionCheck();
};
}
