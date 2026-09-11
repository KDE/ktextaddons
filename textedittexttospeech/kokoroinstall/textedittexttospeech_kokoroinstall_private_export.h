/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kokoroinstalltexttospeech_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef KOKOROINSTALLTEXTTOSPEECH_TESTS_EXPORT
#define KOKOROINSTALLTEXTTOSPEECH_TESTS_EXPORT KOKOROINSTALLTEXTTOSPEECH_EXPORT
#endif
#else /* not compiling tests */
#define KOKOROINSTALLTEXTTOSPEECH_TESTS_EXPORT
#endif
