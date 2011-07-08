EXTRA_OPTIONS = -j4

ifeq ($(DEBUG), 1)
EXTRA_OPTIONS += DEBUG=1
endif

all:
	make $(EXTRA_OPTIONS) -C proheaparea
	make $(EXTRA_OPTIONS) -C loader 
	make $(EXTRA_OPTIONS) -C core
	@mkdir dist || true
	@mkdir modules/302 2> /dev/null || true
	@mkdir modules/303 2> /dev/null || true
	@mkdir modules/310 2> /dev/null || true
	@mkdir modules/311 2> /dev/null || true
	@mkdir modules/330 2> /dev/null || true
	@mkdir modules/340 2> /dev/null || true
	@mkdir modules/350 2> /dev/null || true
	@mkdir modules/351 2> /dev/null || true
	@mkdir modules/352 2> /dev/null || true
	@mkdir modules/371 2> /dev/null || true
	@mkdir modules/372 2> /dev/null || true
	@mkdir modules/380 2> /dev/null || true
	@mkdir modules/390 2> /dev/null || true
	@mkdir modules/393 2> /dev/null || true
	@mkdir modules/396 2> /dev/null || true
	@mkdir modules/401 2> /dev/null || true
	@mkdir modules/500 2> /dev/null || true
	@mkdir modules/501 2> /dev/null || true
	@mkdir modules/503 2> /dev/null || true
	@mkdir modules/550 2> /dev/null || true
	@mkdir modules/551 2> /dev/null || true
	@mkdir modules/600 2> /dev/null || true
	@mkdir modules/610 2> /dev/null || true
	@mkdir modules/620 2> /dev/null || true
	@mkdir modules/635 2> /dev/null || true
	@mkdir modules/639 2> /dev/null || true
	@cp -f loader/popsloader.prx dist
	@cp -f core/popscore.prx dist
	@cp -rf modules dist
	@cp -f proheaparea/proheaparea.prx dist/modules
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_302=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/302/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_303=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/303/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_310=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/310/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_311=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/311/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_330=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/330/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_340=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/340/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_350=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/350/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_351=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/351/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_352=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/352/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_371=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/371/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_372=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/372/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_380=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/380/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_390=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/390/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_393=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/393/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_396=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/396/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_401=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/401/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_500=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/500/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_501=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/501/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_503=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/503/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_550=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/550/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_551=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/551/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_600=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/600/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_610=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/610/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_620=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/620/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_635=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/635/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_639=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/639/

clean:
	make clean -C proheaparea
	make clean -C popcorn
	make clean -C loader
	make clean -C core
