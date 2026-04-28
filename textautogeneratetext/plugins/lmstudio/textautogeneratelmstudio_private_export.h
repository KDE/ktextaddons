/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratelmstudio_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTAUTOGENERATELMSTUDIO_TESTS_EXPORT
#define TEXTAUTOGENERATELMSTUDIO_TESTS_EXPORT TEXTAUTOGENERATELMSTUDIO_EXPORT
#endif
#else /* not compiling tests */
#define TEXTAUTOGENERATELMSTUDIO_TESTS_EXPORT
#endif
