#!/bin/bash
#  Generate project Makefile and its dependencies
#  Copyright (C) 2018  Robert Buj <rbuj@fedoraproject.org>
#
#  This file is part of explorer16 - https://github.com/rbuj/explorer16
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

cat << EOF > Makefile
#  Samples for Explorer 16 Development Board of Microchip
#  Copyright (C) 2018  Robert Buj <rbuj@fedoraproject.org>
#
#  This file is part of explorer16 - https://github.com/rbuj/explorer16
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#
#  There exist several targets which are by default empty and which can be
#  used for execution of your targets. These targets are usually executed
#  before and after some main targets. They are:
#
#     .build-pre:              called before 'build' target
#     .build-post:             called after 'build' target
#     .clean-pre:              called before 'clean' target
#     .clean-post:             called after 'clean' target
#     .clobber-pre:            called before 'clobber' target
#     .clobber-post:           called after 'clobber' target
#     .all-pre:                called before 'all' target
#     .all-post:               called after 'all' target
#     .help-pre:               called before 'help' target
#     .help-post:              called after 'help' target
#
#  Targets beginning with '.' are not intended to be called on their own.
#
#  Main targets can be executed directly, and they are:
#
#     build                    build a specific configuration
#     clean                    remove built files from a configuration
#     clobber                  remove all built files
#     all                      build all configurations
#     help                     print help mesage
#
#  Targets .build-impl, .clean-impl, .clobber-impl, .all-impl, and
#  .help-impl are implemented in nbproject/makefile-impl.mk.
#
#  Available make variables:
#
#     CND_BASEDIR                base directory for relative paths
#     CND_DISTDIR                default top distribution directory (build artifacts)
#     CND_BUILDDIR               default top build directory (object files, ...)
#     CONF                       name of current configuration
#     CND_ARTIFACT_DIR_\${CONF}   directory of build artifact (current configuration)
#     CND_ARTIFACT_NAME_\${CONF}  name of build artifact (current configuration)
#     CND_ARTIFACT_PATH_\${CONF}  path to build artifact (current configuration)
#     CND_PACKAGE_DIR_\${CONF}    directory of package (current configuration)
#     CND_PACKAGE_NAME_\${CONF}   name of package (current configuration)
#     CND_PACKAGE_PATH_\${CONF}   path to package (current configuration)
#
# NOCDDL

# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib

# build
build: .build-post

.build-pre:
# Add your pre 'build' code here...

.build-post: .build-impl
# Add your post 'build' code here...

# clean
clean: .clean-post

.clean-pre:
# Add your pre 'clean' code here...
# WARNING: the IDE does not call this target since it takes a long time to
# simply run make. Instead, the IDE removes the configuration directories
# under build and dist directly without calling make.
# This target is left here so people can do a clean when running a clean
# outside the IDE.

.clean-post: .clean-impl
# Add your post 'clean' code here...

# clobber
clobber: .clobber-post

.clobber-pre:
# Add your pre 'clobber' code here...

.clobber-post: .clobber-impl
# Add your post 'clobber' code here...

# all
all: .all-post

.all-pre:
# Add your pre 'all' code here...

.all-post: .all-impl
# Add your post 'all' code here...

# help
help: .help-post

.help-impl: .help-pre
	@echo ""
	@echo "This makefile supports the following configurations:"
	@echo "    \${ALLCONFS}"
	@echo ""
	@echo "and the following targets:"
	@echo "    build"
	@echo "    clean"
	@echo "    clobber"
	@echo "    all"
	@echo "    help"
	@echo ""
	@echo "Makefile Usage:"
	@echo "    make [CONF=<CONFIGURATION>] [SUB=no] build"
	@echo "    make [CONF=<CONFIGURATION>] [SUB=no] clean"
	@echo "    make [SUB=no] clobber"
	@echo "    make [SUB=no] all"
	@echo "    make help"
	@echo ""
	@echo "Target 'build' will build a specific configuration and, unless 'SUB=no',"
	@echo "    also build subprojects."
	@echo "Target 'clean' will clean a specific configuration and, unless 'SUB=no',"
	@echo "    also clean subprojects."
	@echo "Target 'clobber' will remove all built files from all configurations and,"
	@echo "    unless 'SUB=no', also from subprojects."
	@echo "Target 'all' will will build all configurations and, unless 'SUB=no',"
	@echo "    also build subprojects."
	@echo "Target 'help' prints this message."
	@echo ""

.help-pre:
# Add your pre 'help' code here...

.help-post: .help-impl
# Add your post 'help' code here...

# include project implementation makefile
include nbproject/Makefile-impl.mk

# include project make variables
include nbproject/Makefile-variables.mk
EOF

case "$OSTYPE" in
  darwin*)
    echo "OSX"
    GENERATOR=$(find /Applications/microchip/mplabx/ -name prjMakefilesGenerator.sh | head -n 1)
    if [ -n "$GENERATOR" ]; then
      $GENERATOR -v ./
    else
      echo "can't find prjMakefilesGenerator.sh"
    fi
    ;;
  linux*)
    echo "LINUX"
    GENERATOR=$(find /opt/microchip/mplabx/ -name prjMakefilesGenerator.sh | head -n 1)
    if [ -n "$GENERATOR" ]; then
      $GENERATOR -v ./
    else
      echo "can't find prjMakefilesGenerator.sh"
    fi
    ;;
  msys*)
    echo "WINDOWS: NOT YET IMPLEMENTED"
    ;;
  *)
    echo "unknown: $OSTYPE"
    ;;
esac
