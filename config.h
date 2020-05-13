/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 1;   // border pixel of windows
static const unsigned int snap           = 32;  // snap pixel
static const unsigned int systraypinning = 0;   // 0: sloppy systray follows selected monitor, >0: pin systray to monitor X
static const unsigned int systrayspacing = 2;   // systray spacing
static const int systraypinningfailfirst = 1;   // 1: if pinning fails, display systray on the first monitor, False: display systray on the last monito
static const int showsystray             = 1;   // 0 means no systray
static const int showbar                 = 1;   // 0 means no bar
static const int topbar                  = 1;   // 0 means bottom bar
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab			= showtab_auto;   // Default tab bar show mode
static const int toptab				= False;          // False means bottom tab bar

/* FONTS */
static const char *fonts[]          = { "monospace:size=9" };

/* COLORS */
/* static const char myActive[]        ="#434c5e";	// nord2 */
static const char foreground[]      ="#eceff4";	// nord6
static const char myNormBorder[]    ="#3b4252";	// nord1
static const char myActive[]        ="#5E81AC";	// nord10
static const char myBlack[]         ="#2e3440";	// nord0
static const char myActiveBorder[]  ="#D8DEE9"; // nord4
static const char *colors[][3]      = {
	/*               fg          bg        border   */
	[SchemeNorm] = { foreground, myBlack,  myNormBorder },
	[SchemeSel]  = { myActive, myBlack, myActiveBorder },
	/* [SchemeSel]  = { foreground, myActive, myActiveBorder  }, */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "code", "42" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           0,         0,        -1 },
	{ "st",       NULL,       NULL,       0,            0,           1,         1,        -1 },
	{ "ksnip",    NULL,       NULL,       0,            1,           0,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; // factor of master area size [0.05..0.95]
static const int nmaster     = 1;    // number of clients in master area
static const int resizehints = 1;    // 1 means respect size hints in tiled resizals

#include "horizgrid.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	/* MOD+T */       { "[]=",      tile },    // first entry is default
	/* MOD+F */       { "><>",      NULL },    // no layout function means floating behavior
        /* MOD+Z */       { "[M]",      monocle },
        /* MOD+G */       { "###",      horizgrid },
        /* MOD+R */       { "[\\]",     dwindle },
        /* MOD+C */       { "|M|",      centeredmaster },
        /* MOD+B */       { "TTT",      bstack },
        /* MOD+SHIFT+B */ { "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask // SUPER-KEY
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", "10", NULL };
static const char *termcmd[]  = { "st", NULL };

/* SCRATCHPAD */
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include "movestack.c"
#include "selfrestart.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_F4,     quit,           {0} },
        { MODKEY|ShiftMask,             XK_F5,     self_restart,   {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_x,      spawn,          SHCMD("dlock") },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("dpowermenu") },

	/* SPAWN PROGRAMS */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_space,  togglescratch,  {.v = scratchpadcmd } },

	/* VOLUME CONTROL */
        { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("smixer mute") },
        { MODKEY,                       XK_plus,   spawn,          SHCMD("smixer up 1") },
        { MODKEY|ShiftMask,             XK_plus,   spawn,          SHCMD("smixer up 5") },
        { MODKEY,                       XK_minus,  spawn,          SHCMD("smixer down 1") },
        { MODKEY|ShiftMask,             XK_minus,  spawn,          SHCMD("smixer down 5") },

	/* MUSIC CONTROL */
        { MODKEY,                       XK_m,      spawn,          SHCMD("st -t cmus -e cmus") },
        { MODKEY,                       XK_p,      spawn,          SHCMD("smixer pause") },
        { MODKEY,                       XK_n,      spawn,          SHCMD("smixer next") },
        { MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("smixer prev") },

	/* MOUNT EXTERNALS */
        { MODKEY,                       XK_F9,      spawn,         SHCMD("dmount -m") },
        { MODKEY,                       XK_F10,     spawn,         SHCMD("dmount -u") },

	/* POMODORO */
        { MODKEY,                       XK_Delete,  spawn,         SHCMD("pomodoro") },
        { MODKEY|ShiftMask,             XK_Delete,  spawn,         SHCMD("pomodoro -c") },

	/* TOGGLE BARS */
	{ MODKEY|ShiftMask,             XK_d,      togglebar,      {0} },
	{ MODKEY,                       XK_w,      tabmode,        {-1} },

	/* FOCUS */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

	/* MODIFY MASTER-STACK */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	/* RESIZE WINDOWS */
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },

	/* MOVE WINDOWS */
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } }, // move selected window +1
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } }, // move selected window -1
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },        // promote selected window as master

	/* MOVE FLOATING WINDOWS */
        { MODKEY,			XK_Down,   moveresize,     {.v = (int []){ 0, 25, 0, 0 }}},
        { MODKEY,			XK_Up,	   moveresize,     {.v = (int []){ 0, -25, 0, 0 }}},
        { MODKEY,			XK_Right,  moveresize,     {.v = (int []){ 25, 0, 0, 0 }}},
        { MODKEY,			XK_Left,   moveresize,     {.v = (int []){ -25, 0, 0, 0 }}},

	/* RESIZE FLOATING WINDOWS */
        { MODKEY|ShiftMask,		XK_Down,   moveresize,     {.v = (int []){ 0, 0, 0, 25 }}},
        { MODKEY|ShiftMask,		XK_Up,	   moveresize,     {.v = (int []){ 0, 0, 0, -25 }}},
        { MODKEY|ShiftMask,		XK_Right,  moveresize,     {.v = (int []){ 0, 0, 25, 0 }}},
        { MODKEY|ShiftMask,		XK_Left,   moveresize,     {.v = (int []){ 0, 0, -25, 0 }}},

	/* LAYOUTS */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_z,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_b,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_Tab,    setlayout,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	/* WINDOW-TAGS */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },

	/* MULTIMONITOR */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/* TAGKEYS */
	{ MODKEY,                       XK_Tab,    view,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

	{ ClkWinTitle,          0,              Button1,        zoom,           {0} },

	/* { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } }, */
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
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};
