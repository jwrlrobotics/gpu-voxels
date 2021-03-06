# This is for emacs file handling -*- mode: cmake; indent-tabs-mode: nil -*-
IF(DOXYGEN_FOUND)
  IF(HTML_HELP_COMPILER)
    SET(DOCUMENTATION_HTML_HELP YES)
  ELSE(HTML_HELP_COMPILER)
    SET(DOCUMENTATION_HTML_HELP NO)
  ENDIF(HTML_HELP_COMPILER)
  IF(DOXYGEN_DOT_EXECUTABLE)
    SET(HAVE_DOT YES)
  ELSE(DOXYGEN_DOT_EXECUTABLE)
    SET(HAVE_DOT NO)
  ENDIF(DOXYGEN_DOT_EXECUTABLE)

  SET(DOC_SOURCE_DIR "\"${CMAKE_SOURCE_DIR}/packages\"\\")
  FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html")
  SET(doxyfile "${CMAKE_CURRENT_BINARY_DIR}/doxyfile")
  CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in" ${doxyfile})
  ADD_CUSTOM_TARGET(doc ${DOXYGEN_EXECUTABLE} ${doxyfile})
  IF(DOCUMENTATION_HTML_HELP STREQUAL YES)
    INSTALL(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
            DESTINATION "${ICMAKER_DOC_INSTALL_PATH}"
            COMPONENT doc
            FILES_MATCHING PATTERN *.chm
            )
  ELSE(DOCUMENTATION_HTML_HELP STREQUAL YES)
    INSTALL(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
            DESTINATION "${ICMAKER_DOC_INSTALL_PATH}"
            COMPONENT doc
            PATTERN "*.md5" EXCLUDE
            PATTERN "*.map" EXCLUDE
            PATTERN "*.chm" EXCLUDE)
  ENDIF(DOCUMENTATION_HTML_HELP STREQUAL YES)
ENDIF(DOXYGEN_FOUND)
