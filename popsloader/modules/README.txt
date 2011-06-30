Sony files are copyrighted. Grab a psardumper and get them yourself.
Here are the file list you need to run popsloader:

PSX on PSP Compatibility List:
http://gamerspress.com/mediawiki/index.php?title=PSX_on_PSP_Compatibility_List

Older OFW Download:
http://freeplay.halfmoon.ws/fw/updates/

/kd/popsman.prx
/kd/pops_0*g.prx(>= 6.00) or /kd/pops.prx(<= 5.51)
/kd/impose.prx((fetch one from 4.01, and put it under ms0:/seplugins/popsloader/modules/))
/kd/resource/impose.rsc(fetch one from 4.01, and put it under ms0:/seplugins/popsloader/modules/)
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
│   │   ├── meaudio.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 303
│   │   ├── common_util.prx
│   │   ├── meaudio.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 310
│   │   ├── common_util.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 311
│   │   ├── common_util.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 330
│   │   ├── common_util.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 340
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 350
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 351
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 352
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 371
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 372
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 380
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 390
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 393
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 396
│   │   ├── common_util.prx
│   │   ├── libpspvmc.prx
│   │   ├── pafmini.prx
│   │   ├── popcorn.prx
│   │   ├── popsman.prx
│   │   └── pops.prx
│   ├── 401
│   │   ├── common_util.prx
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
│   ├── impose.prx
│   ├── proheaparea.prx
│   └── README.txt
├── popscore.prx
└── popsloader.prx
