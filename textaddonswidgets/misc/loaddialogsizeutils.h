/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <QWidget>
class QDialog;
namespace TextAddonsWidgets::LoadDialogSizeUtils
{
void TEXTADDONSWIDGETS_EXPORT loadDialogSizeScaled(QWidget *w, const QString &key, int width, int height);
void TEXTADDONSWIDGETS_EXPORT saveDialogSize(QWidget *w, const QString &key);
/*!
 * Makes \a dialog restore its size when it is first shown and store it again
 * when it goes away, using \a key as the state config group. \a defaultSize is
 * used the first time, when nothing was stored yet.
 *
 * Works for any QDialog subclass, KPageDialog included, and does not require
 * the dialog to derive from a specific base class.
 */
void TEXTADDONSWIDGETS_EXPORT manageDialogSize(QDialog *dialog, const QString &key, QSize defaultSize);
};
