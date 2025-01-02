/*
  SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KSharedConfig>
#include <QDialog>
#include <QWidget>

namespace TextAutoCorrectionCore
{
class AutoCorrection;
}
namespace TextAutoCorrectionWidgets
{
class AutoCorrectionWidget;
class AutoCorrectionTextEdit;
class AutoCorrectionLineEdit;
}
class ConfigureTestDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigureTestDialog(TextAutoCorrectionCore::AutoCorrection *autoCorrection, QWidget *parent = nullptr);
    ~ConfigureTestDialog() override;

private Q_SLOTS:
    void slotSaveSettings();

private:
    TextAutoCorrectionWidgets::AutoCorrectionWidget *mWidget = nullptr;
};

class AutocorrectionTestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutocorrectionTestWidget(QWidget *parent = nullptr);
    ~AutocorrectionTestWidget() override;

private Q_SLOTS:
    void slotConfigure();
    void slotChangeMode(bool);

private:
    TextAutoCorrectionWidgets::AutoCorrectionTextEdit *mEdit = nullptr;
    TextAutoCorrectionWidgets::AutoCorrectionLineEdit *mSubject = nullptr;
    TextAutoCorrectionCore::AutoCorrection *mAutoCorrection = nullptr;
    KSharedConfig::Ptr mConfig;
};
