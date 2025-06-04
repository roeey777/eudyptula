################################################################################
#
# solution_8
#
################################################################################

SOLUTION_8_VERSION = 0.0.1
SOLUTION_8_SITE = $(BR2_EXTERNAL_EUDYPTULA_PATH)/package/solution-8
SOLUTION_8_SITE_METHOD = local
SOLUTION_8_MODULE_MAKE_OPTS = CONFIG_SOLUTION_8=m

$(eval $(kernel-module))
$(eval $(generic-package))
