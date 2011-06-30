Sony files are copyrighted. Grab a psardumper and get them yourself.
Here are the file list you need to run popsloader:

/kd/popsman.prx
/kd/pops_0*g.prx(>= 6.00) or /kd/pops.prx(<= 5.51)
/kd/impose.prx(<=4.00)
/kd/resource/impose.rsc(fetch one from any OFW between 3.00 and 4.01, and put it under ms0:/seplugins/popsloader/modules/)
/vsh/module/common_util.prx
/vsh/module/pafmini.prx
/vsh/module/libpspvmc.prx(>=3.40)
/kd/meaudio.prx(<=3.03)

The files should be placed into the corsspending direcotry.
The structure of popsloader direcotry must be like this:

.
├── modules
│   ├── 302
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── meaudio.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 303
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── meaudio.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 310
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 311
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 330
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 340
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 350
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 351
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 352
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 371
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 372
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 380
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 390
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 393
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 396
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 401
│   │   ├── common_util.prx
│   │   ├── impose.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 500
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 501
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 503
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 550
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 551
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 600
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── pops_04g.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 610
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── pops_04g.prx
│   │   ├── pops_05g.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 620
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── pops_01g.prx
│   │   ├── pops_02g.prx
│   │   ├── pops_03g.prx
│   │   ├── pops_04g.prx
│   │   ├── pops_05g.prx
│   │   ├── pops_07g.prx
│   │   ├── pops_09g.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 635
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── pops_01g.prx
│   │   ├── pops_02g.prx
│   │   ├── pops_03g.prx
│   │   ├── pops_04g.prx
│   │   ├── pops_05g.prx
│   │   ├── pops_07g.prx
│   │   ├── pops_09g.prx
│   │   └── popsman.prx
│   ├── 639
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── pops_01g.prx
│   │   ├── pops_02g.prx
│   │   ├── pops_03g.prx
│   │   ├── pops_04g.prx
│   │   ├── pops_07g.prx
│   │   ├── pops_09g.prx
│   │   └── popsman.prx
│   ├── impose.rsc
│   ├── proheaparea.prx
│   └── README.txt
├── popscore.prx
└── popsloader.prx

27 directories, 195 files
