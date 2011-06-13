EXTRA_OPTIONS = -j4

all:
	make $(EXTRA_OPTIONS) -C loader 
	make $(EXTRA_OPTIONS) -C core
	@mkdir dist || true
	@cp -f loader/popsloader.prx dist
	@cp -f core/popscore.prx dist
	@cp -rf modules dist

clean:
	make clean -C loader
	make clean -C core
