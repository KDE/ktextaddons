/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratemistral_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTAUTOGENERATEMISTRAL_TESTS_EXPORT
#define TEXTAUTOGENERATEMISTRAL_TESTS_EXPORT TEXTAUTOGENERATEMISTRAL_EXPORT
#endif
#else /* not compiling tests */
#define TEXTAUTOGENERATEMISTRAL_TESTS_EXPORT
#endif
