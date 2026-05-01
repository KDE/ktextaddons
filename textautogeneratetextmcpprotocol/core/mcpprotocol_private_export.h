/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_TESTS_EXPORT
#define TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_TESTS_EXPORT TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT
#endif
#else /* not compiling tests */
#define TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_TESTS_EXPORT
#endif
