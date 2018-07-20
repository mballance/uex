
UEX_MKFILES_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

UEX_DIR := $(abspath $(UEX_MKFILES_DIR)/..)
UEX := $(UEX_DIR)
export UEX

