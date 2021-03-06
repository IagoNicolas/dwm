/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Terminus:size=9" };
static const char dmenufont[]       = "Terminus:size=9";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

static const Rule rules[] = {
	/*  xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	 /* class      instance    title       tags mask     isfloating   monitor*/
	 { "Gimp",     NULL,       NULL,       0,            0,           -1 },
	 //{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[+]",      tile },    /* first entry is default */
	{ "[ ]",      monocle },
};

/* key definitions */
#define ALTKEY Mod1Mask
#define SUPKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ ALTKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALTKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { ALTKEY|ShiftMask,             KEY,      view,            {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	// Program commands.
	{ SUPKEY,                       XK_1,      spawn,          SHCMD("firefox") },
	{ SUPKEY,                       XK_2,      spawn,          SHCMD("nemo") },
	{ SUPKEY,                       XK_3,      spawn,          SHCMD("tilix") },
	{ SUPKEY,                       XK_4,      spawn,          SHCMD("code") },
	//{ SUPKEY,                       XK_5,      spawn,          SHCMD("spyder") },
	//{ SUPKEY,                       XK_6,      spawn,          SHCMD("virt-manager") },
	//{ SUPKEY,                       XK_7,      spawn,          SHCMD("jetbrains-toolbox") },
	//{ SUPKEY,                       XK_8,      spawn,          SHCMD("simple-scan") },
	{ SUPKEY,                       XK_9,      spawn,          SHCMD("chromium") },
	{ SUPKEY,                       XK_0,      spawn,          SHCMD("tilix -e btop") },
	// Special key commands.
    { 0,                            XF86XK_MonBrightnessUp, spawn, SHCMD("xbacklight -inc 10") },
    { 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 10") },
    { 0,                            XF86XK_AudioRaiseVolume, spawn, SHCMD("amixer -D pulse sset Master 10%+") },
    { 0,                            XF86XK_AudioLowerVolume, spawn, SHCMD("amixer -D pulse sset Master 10%-") },
    { 0,                            XF86XK_AudioMute, spawn, SHCMD("amixer -D pulse sset Master toggle") },
    { 0,                            XF86XK_AudioMicMute, spawn, SHCMD("amixer set Capture toggle") },
    { ALTKEY,                       XK_Print,            spawn, SHCMD("flameshot gui -p /home/necronzero/Pictures/Screenshots") },
    { SUPKEY,                       XK_Print,            spawn, SHCMD("flameshot full -p /home/necronzero/Pictures/Screenshots") },
    { 0,                            XF86XK_Favorites,    spawn, SHCMD("groff -mom /home/necronzero/.config/help.mom -Tpdf | zathura -") },
    // Default Commands.
	{ ALTKEY,                       XK_r,      spawn,          SHCMD("rofi -show drun") },
	{ SUPKEY,                       XK_Return, spawn,          SHCMD("tilix") },
    { ALTKEY,                       XK_Return, zoom,           {0} },
	{ ALTKEY,                       XK_b,      togglebar,      {0} },
	{ ALTKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ ALTKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ ALTKEY,                       XK_Up,     incnmaster,     {.i = +1 } },
	{ ALTKEY,                       XK_Down,   incnmaster,     {.i = -1 } },
	{ ALTKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.05} },
	{ ALTKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.05} },
	//{ ALTKEY,                       XK_Tab,    view,           {0} },
	{ ALTKEY,                       XK_q,      killclient,     {0} },
	//{ ALTKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ ALTKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ ALTKEY,                       XK_Tab,    setlayout,      {0} },
	//{ ALTKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	//{ ALTKEY,                       XK_0,      view,           {.ui = ~0 } },
	//{ ALTKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ ALTKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ ALTKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ ALTKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ ALTKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    TAGKEYS(                        XK_0,                      9)
	{ ALTKEY|ControlMask,           XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         ALTKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         ALTKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         ALTKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            ALTKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            ALTKEY,         Button3,        toggletag,      {0} },
};
