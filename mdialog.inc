/*

	About: modern dialog system
	Author: ziggi

*/

#if defined _mdialog_included
	#endinput
#endif

#define _mdialog_included

/*
	Defines
*/

// external defines
#if !defined MDIALOG_DIALOG_ID
	#define MDIALOG_DIALOG_ID 32700
#endif

#if !defined MAX_FUNCTION_NAME
	#define MAX_FUNCTION_NAME 32
#endif

#if defined MDIALOG_ZLANG_MODE
	#if !defined MDIALOG_MAX_CAPTION_SIZE
		#define MDIALOG_MAX_CAPTION_SIZE 64
	#endif

	#if !defined MDIALOG_MAX_INFO_SIZE
		#define MDIALOG_MAX_INFO_SIZE 2048
	#endif

	#if !defined MDIALOG_MAX_BUTTON_SIZE
		#define MDIALOG_MAX_BUTTON_SIZE 16
	#endif

	#if MDIALOG_MAX_CAPTION_SIZE > MAX_LANG_VALUE_STRING
		#undef MDIALOG_MAX_CAPTION_SIZE
		#define MDIALOG_MAX_CAPTION_SIZE MAX_LANG_VALUE_STRING
	#endif

	#if MDIALOG_MAX_INFO_SIZE > MAX_LANG_MVALUE_STRING
		#undef MDIALOG_MAX_INFO_SIZE
		#define MDIALOG_MAX_INFO_SIZE MAX_LANG_MVALUE_STRING
	#endif

	#if MDIALOG_MAX_BUTTON_SIZE > MAX_LANG_VALUE_STRING
		#undef MDIALOG_MAX_BUTTON_SIZE
		#define MDIALOG_MAX_BUTTON_SIZE MAX_LANG_VALUE_STRING
	#endif
#endif

// internal defines
#define DialogCreate:%0(%1) \
	forward dcr_%0(%1); \
	public dcr_%0(%1)

#define DialogResponse:%0(%1) \
	forward dre_%0(%1); \
	public dre_%0(%1)

#define Dialog: #

/*
	Enums
*/

enum (<<= 1) {
	MDIALOG_NOTVAR_ALL = -1,
	MDIALOG_NOTVAR_NONE = 0,
	MDIALOG_NOTVAR_CAPTION = 1,
	MDIALOG_NOTVAR_INFO,
	MDIALOG_NOTVAR_BUTTON1,
	MDIALOG_NOTVAR_BUTTON2,
}

/*
	Vars
*/

static
	bool:gIsDialogOpen[MAX_PLAYERS char],
	gDialogFunction[MAX_PLAYERS][MAX_FUNCTION_NAME char];

/*
	Dialog_Open
*/

static stock _Dialog_Open(playerid, function[], style, caption[], info[], button1[], button2[])
{
	gIsDialogOpen{playerid} = true;
	gDialogFunction[playerid] = !"dre_";
	strcat(gDialogFunction[playerid], function, sizeof(gDialogFunction[]));
	return ShowPlayerDialog(playerid, MDIALOG_DIALOG_ID, style, caption, info, button1, button2);
}

#if defined MDIALOG_ZLANG_MODE

stock Dialog_Open(playerid, function[], style, caption[], info[], button1[], button2[], notvar_flags = MDIALOG_NOTVAR_NONE, va_args<>)
{
	static
		Lang:lang,
		temp_caption[MDIALOG_MAX_CAPTION_SIZE],
		temp_button1[MDIALOG_MAX_BUTTON_SIZE],
		temp_button2[MDIALOG_MAX_BUTTON_SIZE],
		temp_info[MDIALOG_MAX_INFO_SIZE];

	lang = Lang_GetPlayerLang(playerid);

	if (!(notvar_flags & MDIALOG_NOTVAR_CAPTION)) {
		Lang_GetText(lang, caption, temp_caption);
	} else {
		_MDIALOG_strcpy(temp_caption, caption);
	}

	if (!(notvar_flags & MDIALOG_NOTVAR_INFO)) {
		Lang_GetText(lang, info, temp_info);
	} else {
		_MDIALOG_strcpy(temp_info, info);
	}

	if (!(notvar_flags & MDIALOG_NOTVAR_BUTTON1)) {
		Lang_GetText(lang, button1, temp_button1);
	} else {
		_MDIALOG_strcpy(temp_button1, button1);
	}

	if (!isnull(button2)) {
		if (!(notvar_flags & MDIALOG_NOTVAR_BUTTON2)) {
			Lang_GetText(lang, button2, temp_button2);
		} else {
			_MDIALOG_strcpy(temp_button2, button2);
		}
	}

	if (numargs() > 8) {
		va_format(temp_info, sizeof(temp_info), temp_info, va_start<8>);
	}
	return _Dialog_Open(playerid, function, style, temp_caption, temp_info, temp_button1, temp_button2);
}

#else

stock Dialog_Open(playerid, function[], style, caption[], info[], button1[], button2[])
{
	return _Dialog_Open(playerid, function, style, caption, info, button1, button2);
}

#endif
/*
	Dialog_Close
*/

stock Dialog_Close(playerid)
{
	gIsDialogOpen{playerid} = false;
	gDialogFunction[playerid][0] = '\0';
	return ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, " ", " ", " ", "");
}

/*
	Dialog_IsOpen
*/

stock Dialog_IsOpen(playerid)
{
	return _:gIsDialogOpen{playerid};
}

/*
	Dialog_Show
*/

stock Dialog_Show(playerid, function[])
{
	new call_func[MAX_FUNCTION_NAME char] = !"dcr_";
	strcat(call_func, function);
	return CallLocalFunction(call_func, "d", playerid);
}

/*
	Dialog_Message
*/

#if defined MDIALOG_ZLANG_MODE

stock Dialog_Message(playerid, caption[], info[], button1[], notvar_flags = MDIALOG_NOTVAR_NONE, va_args<>)
{
	static
		Lang:lang,
		temp_caption[MDIALOG_MAX_CAPTION_SIZE],
		temp_button1[MDIALOG_MAX_BUTTON_SIZE],
		temp_info[MDIALOG_MAX_INFO_SIZE];

	lang = Lang_GetPlayerLang(playerid);

	if (!(notvar_flags & MDIALOG_NOTVAR_CAPTION)) {
		Lang_GetText(lang, caption, temp_caption);
	} else {
		_MDIALOG_strcpy(temp_caption, caption);
	}

	if (!(notvar_flags & MDIALOG_NOTVAR_INFO)) {
		Lang_GetText(lang, info, temp_info);
	} else {
		_MDIALOG_strcpy(temp_info, info);
	}

	if (!(notvar_flags & MDIALOG_NOTVAR_BUTTON1)) {
		Lang_GetText(lang, button1, temp_button1);
	} else {
		_MDIALOG_strcpy(temp_button1, button1);
	}

	if (numargs() > 5) {
		va_format(temp_info, sizeof(temp_info), temp_info, va_start<5>);
	}
	return _Dialog_Open(playerid, Dialog:Message, DIALOG_STYLE_MSGBOX, temp_caption, temp_info, temp_button1, "");
}

#else

stock Dialog_Message(playerid, caption[], info[], button1[])
{
	return _Dialog_Open(playerid, Dialog:Message, DIALOG_STYLE_MSGBOX, caption, info, button1, "");
}

#endif

/*
	Dialog_MessageEx
*/

#if defined MDIALOG_ZLANG_MODE

stock Dialog_MessageEx(playerid, response[], caption[], info[], button1[], button2[], notvar_flags = MDIALOG_NOTVAR_NONE, va_args<>)
{
	static
		Lang:lang,
		temp_caption[MDIALOG_MAX_CAPTION_SIZE],
		temp_button1[MDIALOG_MAX_BUTTON_SIZE],
		temp_button2[MDIALOG_MAX_BUTTON_SIZE],
		temp_info[MDIALOG_MAX_INFO_SIZE];

	lang = Lang_GetPlayerLang(playerid);

	if (!(notvar_flags & MDIALOG_NOTVAR_CAPTION)) {
		Lang_GetText(lang, caption, temp_caption);
	} else {
		_MDIALOG_strcpy(temp_caption, caption);
	}

	if (!(notvar_flags & MDIALOG_NOTVAR_INFO)) {
		Lang_GetText(lang, info, temp_info);
	} else {
		_MDIALOG_strcpy(temp_info, info);
	}

	if (!(notvar_flags & MDIALOG_NOTVAR_BUTTON1)) {
		Lang_GetText(lang, button1, temp_button1);
	} else {
		_MDIALOG_strcpy(temp_button1, button1);
	}

	if (!isnull(button2)) {
		if (!(notvar_flags & MDIALOG_NOTVAR_BUTTON2)) {
			Lang_GetText(lang, button2, temp_button2);
		} else {
			_MDIALOG_strcpy(temp_button2, button2);
		}
	}

	if (numargs() > 5) {
		va_format(temp_info, sizeof(temp_info), temp_info, va_start<7>);
	}
	return _Dialog_Open(playerid, response, DIALOG_STYLE_MSGBOX, temp_caption, temp_info, temp_button1, temp_button2);
}

#else

stock Dialog_MessageEx(playerid, response[], caption[], info[], button1[], button2[])
{
	return _Dialog_Open(playerid, response, DIALOG_STYLE_MSGBOX, caption, info, button1, button2);
}

#endif

/*
	OnDialogResponse
*/

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == MDIALOG_DIALOG_ID) {
		if (inputtext[0] == '\0') {
			if (Dialog_IsOpen(playerid)) {
				gIsDialogOpen{playerid} = false;
				return CallLocalFunction(gDialogFunction[playerid], "ddds", playerid, response, listitem, "\1");
			}
			return 0;
		}

		for (new i = strlen(inputtext) - 1; i != -1; i--) {
			if (inputtext[i] == '%') {
				inputtext[i] = '#';
			}
		}

		if (Dialog_IsOpen(playerid)) {
			gIsDialogOpen{playerid} = false;
			return CallLocalFunction(gDialogFunction[playerid], "ddds", playerid, response, listitem, inputtext);
		}
		return 0;
	}

	#if defined MDIALOG_OnDialogResponse
		return MDIALOG_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 0;
	#endif
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif

#define OnDialogResponse MDIALOG_OnDialogResponse
#if defined MDIALOG_OnDialogResponse
	forward MDIALOG_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

/*
	Other functions
*/

static stock _MDIALOG_strcpy(result[], source[], const size = sizeof(result))
{
	result[0] = 0;
	return strcat(result, source, size);
}
