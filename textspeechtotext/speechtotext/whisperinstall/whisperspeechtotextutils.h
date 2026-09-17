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

/*! Group the settings of the engine are stored in. */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString groupName();
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString modelKey();
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString languageKey();
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString computeTypeKey();
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString deviceKey();

/*!
 * The model of the faster-whisper family to transcribe with, "small" for example.
 *
 * Every setting below answers an empty string as long as nothing was chosen, and
 * that is what it is stored as: whisper_helper.py is the one which knows what to
 * default to, and it must stay free to change it.
 */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString loadModel();
SPEECHTOTEXTWHISPERINSTALL_EXPORT void saveModel(const QString &model);

/*! Language of the dictation ("fr", "en"…), empty to let whisper detect it. */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString loadLanguage();
SPEECHTOTEXTWHISPERINSTALL_EXPORT void saveLanguage(const QString &language);

/*! Quantization used by ctranslate2: "int8" on a cpu, "float16" on a gpu. */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString loadComputeType();
SPEECHTOTEXTWHISPERINSTALL_EXPORT void saveComputeType(const QString &computeType);

/*! Where the model runs: "cpu" or "cuda". */
[[nodiscard]] SPEECHTOTEXTWHISPERINSTALL_EXPORT QString loadDevice();
SPEECHTOTEXTWHISPERINSTALL_EXPORT void saveDevice(const QString &device);
}
