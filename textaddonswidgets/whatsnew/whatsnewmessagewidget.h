/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <KMessageWidget>
#include <TextAddonsWidgets/WhatsNewInfo>

#include <QCoreApplication>

namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT WhatsNewMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    explicit WhatsNewMessageWidget(QWidget *parent = nullptr, const QString &applicationName = QCoreApplication::applicationName());
    ~WhatsNewMessageWidget() override;

    void setWhatsNewInfos(const QList<TextAddonsWidgets::WhatsNewInfo> &infos);

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotLinkActivated(const QString &contents);
    QList<TextAddonsWidgets::WhatsNewInfo> mWhatsNewInfos;
    QString mApplicationName;
};
}
