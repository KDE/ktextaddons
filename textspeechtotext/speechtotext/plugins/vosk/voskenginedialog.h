/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libvoskspeechtotext_export.h"
#include <QDialog>
class VoskEngineLanguageWidget;
class LIBVOSKSPEECHTOTEXT_EXPORT VoskEngineDialog : public QDialog
{
    Q_OBJECT
public:
    explicit VoskEngineDialog(QWidget *parent = nullptr);
    ~VoskEngineDialog() override;

private:
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void writeConfig();
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void readConfig();
    VoskEngineLanguageWidget *const mVoskEngineWidget;
};
