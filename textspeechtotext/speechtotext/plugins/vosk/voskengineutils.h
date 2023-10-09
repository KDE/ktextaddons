/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "libvoskspeechtotext_export.h"
#include <QString>
namespace VoskEngineUtils
{
Q_REQUIRED_RESULT LIBVOSKSPEECHTOTEXT_EXPORT QString defaultVoskRepository();
Q_REQUIRED_RESULT LIBVOSKSPEECHTOTEXT_EXPORT QString storageLanguagePath();
};
