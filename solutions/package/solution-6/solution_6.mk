################################################################################
#
# solution_6
#
################################################################################

SOLUTION_6_VERSION = 0.0.1
SOLUTION_6_SITE = $(BR2_EXTERNAL_EUDYPTULA_PATH)/package/solution-6
SOLUTION_6_SITE_METHOD = local
SOLUTION_6_MODULE_MAKE_OPTS = CONFIG_SOLUTION_6=m

$(eval $(kernel-module))
$(eval $(generic-package))
