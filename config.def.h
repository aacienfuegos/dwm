/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
//static char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#4c566a";
static const char col_gray3[]       = "#a5abb6";
static const char col_gray4[]       = "#d8dee9";
static const char col_cyan[]        = "#6d96a5";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	/* [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  }, */
	[SchemeSel]  = { col_gray1, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	/* { "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 }, */
	/* { "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 }, */
	{ TERMCLASS,      NULL,     NULL,           0,         0,          1,           0,        -1 },
	//{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,      NULL,     "Event Tester",      0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,      NULL,     "Simulation",      0,         0,          0,           1,        -1 }, /* irsim */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	//{ "><>",      NULL },    [> no layout function means floating behavior <]
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|ALTKEY,              KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|ALTKEY|ShiftMask,    KEY,      tagprevmon,     {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[]  = { "brave", NULL };

#include "movestack.c"
#include "selfrestart.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,             					XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,             					XK_w, 		 spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_equal,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ ALTKEY|MODKEY,              XK_k,      incrgaps,       {.i = +3 } },
	{ ALTKEY|MODKEY,              XK_j,      incrgaps,       {.i = -3 } },
	/* { ALTKEY|MODKEY|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { ALTKEY|MODKEY|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { ALTKEY|MODKEY|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { ALTKEY|MODKEY|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	{ MODKEY,              XK_g,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,    XK_g,      defaultgaps,    {0} },
	/* { ALTKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { ALTKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { ALTKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { ALTKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { ALTKEY|MODKEY,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { ALTKEY|MODKEY,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { ALTKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { ALTKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	//{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             XK_q,      killclient,     {0} },
	//{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_Tab,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_Tab,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	// Applications
	{ MODKEY, XK_z,		spawn,		SHCMD("zathura") },
	{ MODKEY, XK_v,		spawn,		SHCMD(TERMINAL " -e pulsemixer") },
	{ MODKEY,	XK_r,		spawn,		SHCMD(TERMINAL " -e lf") },
	{ 0, XK_Print,		spawn,		SHCMD("flameshot gui") },
	{ MODKEY, XK_n,		spawn,		SHCMD(TERMINAL " -e ncmpcpp; pkill -RTMIN+11 dwmblocks") },
	{ MODKEY, XK_f,		spawn,		SHCMD(TERMINAL " -e newsboat; pkill -RTMIN+6 dwmblocks") },
	{ MODKEY, XK_m,		spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },

	// Dmenu
	{ MODKEY, XK_e,		spawn,		SHCMD("dmenu_bookmark") },
	{ MODKEY, XK_d,		spawn,		SHCMD("setdisplay") },
	{ MODKEY, XK_s,		spawn,		SHCMD("passmenu") },
	{ MODKEY, XK_u,		spawn,		SHCMD("dmenuunicode") },
	{ MODKEY, XK_BackSpace,		spawn,		SHCMD("sysact") },
	{ MODKEY, XK_t,		spawn,		SHCMD("dmenu_translate -sl es -tl en") },

	// Music
	{ MODKEY, XK_p,		spawn,		SHCMD("mpc toggle") },
	{ MODKEY, XK_bracketleft,		spawn,		SHCMD("mpc prev") },
	{ MODKEY, XK_bracketright,		spawn,		SHCMD("mpc next") },

	// Media keys
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc toggle") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,		spawn,		SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0, XF86XK_AudioMicMute,	spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD(TERMINAL " -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD(TERMINAL) },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD(TERMINAL " -e htop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD(TERMINAL " -e lf /") },
	{ 0, XF86XK_Battery,		spawn,		SHCMD("") },
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

