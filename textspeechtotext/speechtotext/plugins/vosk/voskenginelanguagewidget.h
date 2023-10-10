/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "downloadlanguagejob.h"
#include "libvoskspeechtotext_private_export.h"
#include "managermodelvoskspeechtotext.h"
#include <QWidget>
class QTreeView;
class VoskSpeechToTextModel;
class QLineEdit;
class VoskSpeechToTextProxyModel;
class QProgressBar;
class QLabel;
class LIBVOSKSPEECHTOTEXT_TESTS_EXPORT VoskEngineLanguageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VoskEngineLanguageWidget(QWidget *parent = nullptr);
    ~VoskEngineLanguageWidget() override;

private:
    void slotTextChanged(const QString &str);
    void slotDownLoad(const DownloadLanguageJob::DownloadLanguageInfo &info);
    void slotDelete(const QString &identifier);
    void slotUpdateListLanguage();
    void slotError(const QString &str);
    void updateListModel();
    void slotProgressInfo(const ManagerModelVoskSpeechToText::ProgressInfo &info);
    QTreeView *const mTreeView;
    QLineEdit *const mSearchLineEdit;
    VoskSpeechToTextModel *const mVoskSpeechToTextModel;
    VoskSpeechToTextProxyModel *const mVoskSpeechToTextProxyModel;
    QProgressBar *const mProgressBar;
    QLabel *const mProgressBarLabel;
    QWidget *const mProgressBarWidget;
};
