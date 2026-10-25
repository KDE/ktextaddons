/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libvoskspeechtotext_private_export.h"
#include "managermodelvoskspeechtotext.h"
#include "voskdownloadlanguagejob.h"
#include <QWidget>
class QTreeView;
class VoskSpeechToTextModel;
class QLineEdit;
class VoskSpeechToTextProxyModel;
class QProgressBar;
class QLabel;
class VoskEngineLanguageTreeView;
class LIBVOSKSPEECHTOTEXT_TESTS_EXPORT VoskEngineLanguageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VoskEngineLanguageWidget(QWidget *parent = nullptr);
    ~VoskEngineLanguageWidget() override;

private:
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void slotTextChanged(const QString &str);
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void slotDownLoad(const VoskDownloadLanguageJob::DownloadLanguageInfo &info);
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void slotDelete(const QString &identifier);
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void slotUpdateListLanguage();
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void slotError(const QString &str);
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void updateListModel();
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void slotProgressInfo(const ManagerModelVoskSpeechToText::ProgressInfo &info);
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void slotDownloadLanguage();
    VoskEngineLanguageTreeView *const mTreeView;
    QLineEdit *const mSearchLineEdit;
    VoskSpeechToTextModel *const mVoskSpeechToTextModel;
    VoskSpeechToTextProxyModel *const mVoskSpeechToTextProxyModel;
    QProgressBar *const mProgressBar;
    QLabel *const mProgressBarLabel;
    QWidget *const mProgressBarWidget;
};
