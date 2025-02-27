/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTAUTOGENERATETEXT_TESTS_EXPORT
#define TEXTAUTOGENERATETEXT_TESTS_EXPORT TEXTAUTOGENERATETEXT_EXPORT
#endif
#else /* not compiling tests */
#define TEXTAUTOGENERATETEXT_TESTS_EXPORT
#endif
