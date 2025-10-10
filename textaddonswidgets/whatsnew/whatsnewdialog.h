/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textaddonswidgets_export.h"
#include <TextAddonsWidgets/WhatsNewInfo>

#include <QCoreApplication>
#include <QDialog>

namespace TextAddonsWidgets
{
class WhatsNewWidget;
class TEXTADDONSWIDGETS_EXPORT WhatsNewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WhatsNewDialog(const QList<TextAddonsWidgets::WhatsNewInfo> &infos,
                            QWidget *parent = nullptr,
                            const QString &applicationName = QCoreApplication::applicationName());
    ~WhatsNewDialog() override;

    void updateInformations();

private:
    TEXTADDONSWIDGETS_NO_EXPORT void readConfig();
    TEXTADDONSWIDGETS_NO_EXPORT void writeConfig();
    WhatsNewWidget *const mWhatsNewWidget;
};
}
