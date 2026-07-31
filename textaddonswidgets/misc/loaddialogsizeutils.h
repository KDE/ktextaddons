/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <QWidget>
namespace TextAddonsWidgets::LoadDialogSizeUtils
{
void TEXTADDONSWIDGETS_EXPORT loadDialogSizeScaled(QWidget *w, const QString &key, int width, int height);
};
