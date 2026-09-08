/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "savedsizedialog.h"
#include <QShowEvent>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

using namespace TextAddonsWidgets;

SavedSizeDialog::SavedSizeDialog(QLatin1StringView configGroupName, QSize defaultSize, QWidget *parent)
    : QDialog(parent)
    , mConfigGroupName(configGroupName)
    , mDefaultSize(defaultSize)
{
}

SavedSizeDialog::~SavedSizeDialog()
{
    if (mWasInitialized) {
        TextAddonsWidgets::LoadDialogSizeUtils::saveDialogSize(this, mConfigGroupName);
    }
}

void SavedSizeDialog::showEvent(QShowEvent *event)
{
    if (!event->spontaneous() && !mWasInitialized) {
        mWasInitialized = true;
        TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, mConfigGroupName, mDefaultSize.width(), mDefaultSize.height());
    }
    QDialog::showEvent(event);
}
#include "moc_savedsizedialog.cpp"
