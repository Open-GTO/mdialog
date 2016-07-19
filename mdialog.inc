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
#define DialogCreate:%0(%1) \
	forward dcr_%0(%1); \
	public dcr_%0(%1)

#define DialogResponse:%0(%1) \
	forward dre_%0(%1); \
	public dre_%0(%1)

#define Dialog: #

// internal defines
#if !defined MDIALOG_DIALOG_ID
	#define MDIALOG_DIALOG_ID 32700
#endif

#if !defined MAX_FUNCTION_NAME
	#define MAX_FUNCTION_NAME 32
#endif

/*
	Vars
*/

static
	bool:gIsDialogOpen[MAX_PLAYERS char],
	gDialogFunction[MAX_PLAYERS][(MAX_FUNCTION_NAME - 4) char];

/*
	Dialog_Open
*/

#if defined MDIALOG_ZLANG_MODE

stock Dialog_Open(playerid, function[], style, var_caption[], var_info[], var_button1[], var_button2[], va_args<>)
{
	gIsDialogOpen{playerid} = true;
	gDialogFunction[playerid] = !"dre_";
	strcat(gDialogFunction[playerid], function, sizeof(gDialogFunction[]));

	static
		Lang:lang,
		caption[MAX_LANG_VALUE_STRING],
		button1[MAX_LANG_VALUE_STRING],
		button2[MAX_LANG_VALUE_STRING],
		info[MAX_LANG_VALUE_STRING];

	lang = Lang_GetPlayerLang(playerid);

	Lang_GetText(lang, var_caption, caption);
	Lang_GetText(lang, var_button1, button1);
	Lang_GetText(lang, var_button2, button2);
	Lang_GetText(lang, var_info, info);
	va_format(info, sizeof(info), info, va_start<7>);

	return ShowPlayerDialog(playerid, MDIALOG_DIALOG_ID, style, caption, info, button1, button2);
}

#define Dialog_Open(%0$%1) Dialog_Open(%0#%1)

#else

stock Dialog_Open(playerid, function[], style, caption[], info[], button1[], button2[])
{
	gIsDialogOpen{playerid} = true;
	gDialogFunction[playerid] = !"dre_";
	strcat(gDialogFunction[playerid], function, sizeof(gDialogFunction[]));
	return ShowPlayerDialog(playerid, MDIALOG_DIALOG_ID, style, caption, info, button1, button2);
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

stock Dialog_Message(playerid, caption[], info[], button1[])
{
	return Dialog_Open(playerid, Dialog:Message, DIALOG_STYLE_MSGBOX, caption, info, button1, "");
}

/*
	Dialog_MessageEx
*/

stock Dialog_MessageEx(playerid, response[], caption[], info[], button1[], button2[])
{
	return Dialog_Open(playerid, response, DIALOG_STYLE_MSGBOX, caption, info, button1, button2);
}

/*
	OnDialogResponse
*/

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == MDIALOG_DIALOG_ID) {
		if (inputtext[0] == '\0') {
			inputtext[0] = '\1';
		} else {
			for (new i = strlen(inputtext) - 1; i != -1; i--) {
				if (inputtext[i] == '%') {
					inputtext[i] = '#';
				}
			}
		}

		if (Dialog_IsOpen(playerid)) {
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
