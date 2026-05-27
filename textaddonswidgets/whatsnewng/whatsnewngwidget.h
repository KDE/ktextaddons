/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_private_export.h"
#include <KAboutData>
#include <QList>
#include <QWidget>
class QTextBrowser;
namespace TextAddonsWidgets
{
class WhatsNewComboBoxWidget;
class TEXTADDONSWIDGETS_TESTS_EXPORT WhatsNewNgWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WhatsNewNgWidget(QWidget *parent = nullptr, const QString &applicationId = {});
    ~WhatsNewNgWidget() override;

private:
    TEXTADDONSWIDGETS_NO_EXPORT void initialize(const QString &applicationName);
    TEXTADDONSWIDGETS_NO_EXPORT void slotVersionChanged(int type);
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString generateVersionHeader(int type) const;
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString generateStartEndHtml(const QString &str) const;
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString featuresChangeStr() const;
    QList<KAboutRelease> mAboutRelease;
    QTextBrowser *const mLabelInfo;
    WhatsNewComboBoxWidget *const mWhatsNewComboBoxWidget;
};
}
