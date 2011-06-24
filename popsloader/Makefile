EXTRA_OPTIONS = -j4

all:
	make $(EXTRA_OPTIONS) -C popcorn CONFIG_620=1 CONFIG_639=1 CONFIG_635=1 CONFIG_500=1 #DEBUG=1
	make $(EXTRA_OPTIONS) -C loader 
	make $(EXTRA_OPTIONS) -C core
	@mkdir dist || true
	@cp -f loader/popsloader.prx dist
	@cp -f core/popscore.prx dist
	@cp -rf modules dist
	@cp -f popcorn/popcorn.prx dist/modules/620/
	@cp -f popcorn/popcorn.prx dist/modules/635/
	@cp -f popcorn/popcorn.prx dist/modules/639/

clean:
	make clean -C popcorn
	make clean -C loader
	make clean -C core
