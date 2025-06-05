################################################################################
#
# solution_9
#
################################################################################

SOLUTION_9_VERSION = 0.0.1
SOLUTION_9_SITE = $(BR2_EXTERNAL_EUDYPTULA_PATH)/package/solution-9
SOLUTION_9_SITE_METHOD = local
SOLUTION_9_MODULE_MAKE_OPTS = CONFIG_SOLUTION_9=m

$(eval $(kernel-module))
$(eval $(generic-package))
