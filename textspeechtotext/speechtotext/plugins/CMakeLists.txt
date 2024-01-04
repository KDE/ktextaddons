# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
add_subdirectory(google)
add_subdirectory(whisper)

if (SPEAK_TO_TEXT_VOSK_PLUGIN)
    find_package(Vosk)
    if (NOT ${Vosk_FOUND})
        message(WARNING "Vosk not found! Download vosk from https://github.com/alphacep/vosk-api/releases
            and copy the library and the 'vosk-api.h' file in ${PROJECT_SOURCE_DIR}")
        return()
    endif()

    add_subdirectory(vosk)
endif()
