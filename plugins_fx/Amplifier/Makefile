# --------------------------------------------------------------
# Project name, used for binaries

NAME = LMMSAmplifier

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	LMMSAmplifier.cpp

# --------------------------------------------------------------
# Do some magic

UI_TYPE = generic
FILE_BROWSER_DISABLED = true
include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

TARGETS += clap
TARGETS += jack
TARGETS += ladspa
TARGETS += lv2_sep
TARGETS += vst2
TARGETS += vst3

ifeq ($(HAVE_CAIRO_OR_OPENGL),true)
ifeq ($(HAVE_LIBLO),true)
TARGETS += dssi
endif
endif

all: $(TARGETS)

# --------------------------------------------------------------
