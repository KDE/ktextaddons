/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "speechtotextwhisperinstall_export.h"
#include <QString>
#include <QStringList>

namespace WhisperSpeechToTextUtils
{
/*! Interpreter used to create the virtualenv, faster-whisper has no version constraint. */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString pythonVersion();
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString pythonVersionPath();

/*! Name of the helper script driving faster-whisper. */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString pythonScript();
/*! Absolute path of the helper script, empty when it is not installed. */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString pythonScriptPath();

/*!
 * The modules the helper script needs, with their pip names.
 *
 * Kept in sync with REQUIRED_MODULES/PIP_NAMES in whisper_helper.py: it is
 * what has to be installed when the script has not been able to answer at all.
 */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QStringList requiredModules();

/*!
 * The modules are installed in a virtualenv of their own, and not system wide:
 * on a distribution which follows PEP 668 pip refuses to touch the system
 * python anyway.
 */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString defaultVenvPath();
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString defaultVenvPython();
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString defaultVenvPip();
/*! Python of the virtualenv, empty when it has not been created yet. */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString venvPython();
/*! Pip of the virtualenv, empty when it has not been created yet. */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString venvPip();
};
