#
# Carrie R. Lust makefile for DMAKE 4.0 / emx 0.9d
#

# set this to something if debug version should be created
DEBUG  = 

# adjust this as desired/required
CFLAGS = -g -Wall -fno-exceptions -fno-rtti
CC     = gcc $(CFLAGS)
I      = e:/prog/emx/include/

# where the various files are (to be) kept; no trailing slashes please!
SRC    = src
TMP    = tmp
OUT    = out
DATA   = $(SRC)/data
DISTR  = distr

# -------------------------------------------------------------------------

.IF $(DEBUG)
    o=o
    $(TMP)/%.$(o) : $(SRC)/%.cpp ; $(CC) -o $@ -c $<
.ELSE
    o=obj
    $(TMP)/%.$(o) : $(SRC)/%.cpp ; $(CC) -o $@ -Zomf -Zsys -O2 -c $<
.END

# -- 'big' targes ---------------------------------------------------------

default:      all
all:          clust ressources

distr .IGNORE:  all
	copy "$(OUT)\*.hlp" "$(DISTR)"
	copy "$(OUT)\*.exe" "$(DISTR)"
	del "$(DISTR)\*~"
	del "$(DISTR)\*.INI"

clust:        $(OUT)/clust.exe
ressources:   $(OUT)/clust.hlp

# -- 'small' targets ------------------------------------------------------

$(OUT)/clust.exe:      $(TMP)/clust.$(o) \
                       $(TMP)/about.$(o) \
                       $(TMP)/chrginfo.$(o) \
                       $(TMP)/clock.$(o) \
                       $(TMP)/connectn.$(o) \
                       $(TMP)/crdntr.$(o) \
                       $(TMP)/display.$(o) \
                       $(TMP)/helper.$(o) \
                       $(TMP)/items.$(o) \
                       $(TMP)/settings.$(o) \
                       $(TMP)/warner.$(o) \
                       $(SRC)/clust.def \
                       $(TMP)/clust.res
.IF $(DEBUG)
	$(CC) -o $(OUT)/clust -Zmt -lstdcpp $(TMP)/*.$(o) $(SRC)/clust.def
	emxbind -bpq e:/prog/emx/bin/emxl $(OUT)/clust
# FIXME the above is probably totally wrong now ...
.ELSE
	$(CC) -o $(OUT)/clust.exe -Zomf -Zsys -Zmt -s -lstdcpp $<
.END

$(TMP)/clust.res:      $(SRC)/clust.rc $(SRC)/clust.h $(DATA)/clust.ico
	rc -r "$(SRC)/clust.rc" "$@"

$(TMP)/helper.$(o):     $(SRC)/version.h $(SRC)/helper.cpp

# -- language ressources --------------------------------------------------

$(OUT)/clust.hlp:       $(SRC)/clust.ipf $(DATA)/teamlogo.bmp \
                        $(DATA)/wow.bmp $(DATA)/clust.bmp
	ipfc /D:001 /C:850 $(SRC)/clust.ipf $@

# -------------------------------------------------------------------------
