LOCAL_PATH := $(shell pwd)

global-incdirs-y += include

# source file
srcs-y += bitcoin_wallet_ta.c

# adding bip39 required crypto functions
