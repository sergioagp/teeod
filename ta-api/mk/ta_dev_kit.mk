ta-dev-kit-dir := $(patsubst %/,%,$(abspath $(dir $(lastword $(MAKEFILE_LIST)))..))


-include sub.mk
include $(ta-dev-kit-dir)/Makefile