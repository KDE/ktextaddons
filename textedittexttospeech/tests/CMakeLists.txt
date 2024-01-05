# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(texttospeechwidget_gui texttospeechwidget_gui.cpp)
target_link_libraries(texttospeechwidget_gui
    KF${KF_MAJOR_VERSION}::TextEditTextToSpeech KF${KF_MAJOR_VERSION}::CoreAddons Qt::Widgets KF${KF_MAJOR_VERSION}::I18n
    )

#####
add_executable(texttospeechgui texttospeechgui.cpp texttospeechgui.h)
target_link_libraries(texttospeechgui
    KF${KF_MAJOR_VERSION}::TextEditTextToSpeech KF${KF_MAJOR_VERSION}::CoreAddons Qt::Widgets KF${KF_MAJOR_VERSION}::I18n
    )

#####
add_executable(texttospeechconfiggui texttospeechconfiggui.cpp texttospeechconfiggui.h)
target_link_libraries(texttospeechconfiggui
    KF${KF_MAJOR_VERSION}::TextEditTextToSpeech KF${KF_MAJOR_VERSION}::CoreAddons Qt::Widgets KF${KF_MAJOR_VERSION}::I18n
    )

#####
add_executable(texttospeechconfigdialoggui texttospeechconfigdialoggui.cpp)
target_link_libraries(texttospeechconfigdialoggui
    KF${KF_MAJOR_VERSION}::TextEditTextToSpeech KF${KF_MAJOR_VERSION}::CoreAddons Qt::Widgets KF${KF_MAJOR_VERSION}::I18n
    )

#####
add_executable(texttospeechcontainergui texttospeechcontainergui.cpp texttospeechcontainergui.h)
target_link_libraries(texttospeechcontainergui
    KF${KF_MAJOR_VERSION}::TextEditTextToSpeech KF${KF_MAJOR_VERSION}::CoreAddons Qt::Widgets KF${KF_MAJOR_VERSION}::I18n
    )
