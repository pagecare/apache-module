mod_learn.la: mod_learn.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_learn.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_learn.la
