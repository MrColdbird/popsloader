EXTRA_OPTIONS = -j4

ifeq ($(DEBUG), 1)
EXTRA_OPTIONS += DEBUG=1
endif

all:
	make $(EXTRA_OPTIONS) -C loader 
	make $(EXTRA_OPTIONS) -C core
	@mkdir dist || true
	@cp -f loader/popsloader.prx dist
	@cp -f core/popscore.prx dist
	@cp -rf modules dist
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
	make $(EXTRA_OPTIONS) CONFIG_373=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/373/
	make $(EXTRA_OPTIONS) clean -C popcorn
	make $(EXTRA_OPTIONS) CONFIG_400=1 -C popcorn
	@cp -f popcorn/popcorn.prx dist/modules/400/
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
	make clean -C popcorn
	make clean -C loader
	make clean -C core
