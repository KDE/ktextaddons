/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "speechtotextwhisper_export.h"
#include <QString>
#include <QStringList>

namespace WhisperSpeechToTextUtils
{
/*! Interpreter used to create the virtualenv, faster-whisper has no version constraint. */
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QString pythonVersion();
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QString pythonVersionPath();

/*! Name of the helper script driving faster-whisper. */
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QString pythonScript();
/*! Absolute path of the helper script, empty when it is not installed. */
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QString pythonScriptPath();

/*!
 * The modules the helper script needs, with their pip names.
 *
 * Kept in sync with REQUIRED_MODULES/PIP_NAMES in whisper_helper.py: it is
 * what has to be installed when the script has not been able to answer at all.
 */
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QStringList requiredModules();

/*!
 * The modules are installed in a virtualenv of their own, and not system wide:
 * on a distribution which follows PEP 668 pip refuses to touch the system
 * python anyway.
 */
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QString defaultVenvPath();
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QString defaultVenvPython();
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QString defaultVenvPip();
/*! Python of the virtualenv, empty when it has not been created yet. */
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QString venvPython();
/*! Pip of the virtualenv, empty when it has not been created yet. */
[[nodiscard]] SPEECHTOTEXTWHISPER_EXPORT QString venvPip();
};
