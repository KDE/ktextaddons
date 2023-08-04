/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_private_export.h"
#include <QWidget>
class QTreeView;
class TranslatorModel;
class QLineEdit;
class LIBBERGAMOT_TESTS_EXPORT BergamotEngineLanguageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BergamotEngineLanguageWidget(QWidget *parent = nullptr);
    ~BergamotEngineLanguageWidget() override;

private:
    void slotTextChanged(const QString &str);
    void slotDownLoad();
    void slotDelete();
    void slotUpdateListLanguage();
    void slotError(const QString &str);
    void updateListModel();
    QTreeView *const mTreeView;
    QLineEdit *const mSearchLineEdit;
    TranslatorModel *const mTranslatorModel;
};
