/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textspeechtotext_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTSPEECHTOTEXT_TESTS_EXPORT
#define TEXTSPEECHTOTEXT_TESTS_EXPORT TEXTSPEECHTOTEXT_EXPORT
#endif
#else /* not compiling tests */
#define TEXTSPEECHTOTEXT_TESTS_EXPORT
#endif
