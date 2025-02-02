/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_private_export.h"
#include "managermodeltranslator.h"
#include <QWidget>
class QTreeView;
class TranslatorModel;
class QLineEdit;
class TranslatorProxyModel;
class QProgressBar;
class QLabel;
class LIBBERGAMOT_TESTS_EXPORT BergamotEngineLanguageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BergamotEngineLanguageWidget(QWidget *parent = nullptr);
    ~BergamotEngineLanguageWidget() override;

private:
    void slotTextChanged(const QString &str);
    void slotDownLoad(const QString &url, const QString &checkSum);
    void slotDelete(const QString &identifier);
    void slotUpdateListLanguage();
    void slotError(const QString &str);
    void updateListModel();
    void slotProgressInfo(const ManagerModelTranslator::ProgressInfo &info);
    QTreeView *const mTreeView;
    QLineEdit *const mSearchLineEdit;
    TranslatorModel *const mTranslatorModel;
    TranslatorProxyModel *const mTranslatorProxyModel;
    QProgressBar *const mProgressBar;
    QLabel *const mProgressBarLabel;
    QWidget *const mProgressBarWidget;
};
