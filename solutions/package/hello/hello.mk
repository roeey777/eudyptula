################################################################################
#
# hello
#
################################################################################

HELLO_VERSION = 0.0.1
HELLO_SITE = $(BR2_EXTERNAL_EUDYPTULA_PATH)/package/hello
HELLO_SITE_METHOD = local
HELLO_MODULE_MAKE_OPTS = CONFIG_HELLO=m

$(eval $(kernel-module))
$(eval $(generic-package))
