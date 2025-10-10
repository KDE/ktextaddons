/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_private_export.h"
#include "whatsnewcomboboxwidget.h"
#include "whatsnewinfo.h"
#include <QWidget>
class QTextBrowser;
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_TESTS_EXPORT WhatsNewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WhatsNewWidget(const QList<TextAddonsWidgets::WhatsNewInfo> &infos, QWidget *parent = nullptr);
    ~WhatsNewWidget() override;

    void updateInformations();

private:
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT int currentVersion() const;
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString generateStartEndHtml(const QString &str) const;
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString importantChangeStr() const;
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString featuresChangeStr() const;
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString bugFixingChangeStr() const;
    TEXTADDONSWIDGETS_NO_EXPORT void slotVersionChanged(int i);
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString createVersionInformation(const WhatsNewInfo &info);
    [[nodiscard]] TEXTADDONSWIDGETS_NO_EXPORT QString generateVersionHeader(int type) const;
    TEXTADDONSWIDGETS_NO_EXPORT void fillComboBox();

    const QList<WhatsNewInfo> mWhatsNewInfo;
    QTextBrowser *const mLabelInfo;
    WhatsNewComboBoxWidget *const mWhatsNewComboBoxWidget;
};
}
