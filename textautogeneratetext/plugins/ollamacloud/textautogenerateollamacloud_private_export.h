/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogenerateollamaonline_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT
#define TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT TEXTAUTOGENERATEOLLAMAONLINE_EXPORT
#endif
#else /* not compiling tests */
#define TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT
#endif
