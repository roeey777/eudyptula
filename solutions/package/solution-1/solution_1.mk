################################################################################
#
# solution_1
#
################################################################################

SOLUTION_1_VERSION = 0.0.1
SOLUTION_1_SITE = $(BR2_EXTERNAL_EUDYPTULA_PATH)/package/solution-1
SOLUTION_1_SITE_METHOD = local
SOLUTION_1_MODULE_MAKE_OPTS = CONFIG_SOLUTION_1=m

$(eval $(kernel-module))
$(eval $(generic-package))
