# SPDX-FileCopyrightText: 2022 Weng Xuetian <wengxt@gmail.com>
# SPDX-License-Identifier: LGPL-2.0-or-later

file(GLOB EMOJI_DATA_FILES "*.dict")
install(FILES ${EMOJI_DATA_FILES} DESTINATION ${KDE_INSTALL_DATADIR}/kf6/emoji)
