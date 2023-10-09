/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskengineutils.h"
#include <QStandardPaths>

QString VoskEngineUtils::defaultVoskRepository()
{
    return QStringLiteral("https://alphacephei.com/vosk/models/model-list.json");
}

QString VoskEngineUtils::storageLanguagePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QStringLiteral("/vosk-texttospeech");
}
