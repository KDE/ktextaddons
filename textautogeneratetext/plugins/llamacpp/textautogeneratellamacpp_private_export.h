/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratellamacpp_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTAUTOGENERATELLAMACPP_TESTS_EXPORT
#define TEXTAUTOGENERATELLAMACPP_TESTS_EXPORT TEXTAUTOGENERATELLAMACPP_EXPORT
#endif
#else /* not compiling tests */
#define TEXTAUTOGENERATELLAMACPP_TESTS_EXPORT
#endif
