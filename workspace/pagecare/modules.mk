mod_pagecare.la: mod_pagecare.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_pagecare.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_pagecare.la
