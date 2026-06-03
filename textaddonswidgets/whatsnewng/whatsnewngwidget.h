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
    explicit WhatsNewNgWidget(QWidget *parent = nullptr);
    ~WhatsNewNgWidget() override;

    void setReleases(const QList<KAboutRelease> &info);

private:
    TEXTADDONSWIDGETS_NO_EXPORT void initialize();
    TEXTADDONSWIDGETS_NO_EXPORT void slotVersionChanged(int type);
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString generateVersionHeader(const KAboutRelease &release) const;
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString generateStartEndHtml(const QString &str) const;
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString featuresChangeStr() const;
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString generateUrl(const KAboutRelease &release) const;
    QList<KAboutRelease> mAboutRelease;
    QTextBrowser *const mLabelInfo;
    WhatsNewComboBoxWidget *const mWhatsNewComboBoxWidget;
};
}
