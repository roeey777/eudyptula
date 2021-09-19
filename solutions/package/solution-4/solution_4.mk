################################################################################
#
# solution_4
#
################################################################################

SOLUTION_4_VERSION = 0.0.1
SOLUTION_4_SITE = $(BR2_EXTERNAL_EUDYPTULA_PATH)/package/solution-4
SOLUTION_4_SITE_METHOD = local
SOLUTION_4_MODULE_MAKE_OPTS = CONFIG_SOLUTION_4=m

$(eval $(kernel-module))
$(eval $(generic-package))
