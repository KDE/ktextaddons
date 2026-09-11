# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

# Everything needed to check and install the python side of kokoro, without
# the engine itself: an application can offer the installation without pulling
# QtMultimedia and the backend.
add_library(
    kokoroinstalltexttospeech
    texttospeechkokoroinstallmessagewidget.h
    texttospeechkokoroinstallmessagewidget.cpp
)
ecm_qt_declare_logging_category(kokoroinstalltexttospeech
    HEADER texttospeech_kokoroinstall_lib_debug.h
    IDENTIFIER KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG
    CATEGORY_NAME org.kde.kf.textospeech_lib.kokoroinstall
    DESCRIPTION "kokoro install text to speech lib"
    EXPORT KTEXTADDONS
)

target_sources(
    kokoroinstalltexttospeech
    PRIVATE
        texttospeechkokoroutils.h
        texttospeechkokoroutils.cpp
        texttospeechkokoroinstallpythondialog.h
        texttospeechkokoroinstallpythondialog.cpp
        texttospeechkokoroinstallpythonwidget.h
        texttospeechkokoroinstallpythonwidget.cpp
        textedittexttospeech_kokoroinstall_private_export.h
        texttospeechkokorocheckjob.h
        texttospeechkokorocheckjob.cpp
        texttospeechkokoroinstalljob.h
        texttospeechkokoroinstalljob.cpp
        texttospeechkokoroinstallpythonevenvjob.h
        texttospeechkokoroinstallpythonevenvjob.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        kokoroinstalltexttospeech
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(kokoroinstalltexttospeech BASE_NAME kokoroinstalltexttospeech)

# The headers are not installed: the sources of this repository which link
# against it include them from the build tree.
target_include_directories(
    kokoroinstalltexttospeech
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(
    kokoroinstalltexttospeech
    PUBLIC
        Qt::TextToSpeech
        Qt::Widgets
    PRIVATE
        KF6::I18n
        KF6::TextAddonsWidgets
)

set_target_properties(
    kokoroinstalltexttospeech
    PROPERTIES
        VERSION
            ${TEXTEDITTEXTTOSPEECH_VERSION}
        SOVERSION
            ${TEXTEDITTEXTTOSPEECH_SOVERSION}
        EXPORT_NAME
            kokoroinstalltexttospeech
)

# KF6TextEditTextToSpeech links against it privately, and a shared library still
# records its private dependencies, so the target has to be part of the same
# export set.
install(
    TARGETS
        kokoroinstalltexttospeech
    EXPORT KF6TextEditTextToSpeechTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

# The backend script: the check and the install need it as much as the engine does,
# and TextToSpeechKokoroUtils::pythonScriptPath() is the one which locates it.
install(PROGRAMS scripts/kokoro_helper.py DESTINATION ${KDE_INSTALL_BINDIR})

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
