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

#if !defined MDIALOG_MAX_LINES
	#define MDIALOG_MAX_LINES 100
#endif

#if !defined MDIALOG_MAX_SPACES
	#define MDIALOG_MAX_SPACES 200
#endif

#if !defined MDIALOG_MIN_DIALOG_WIDTH
	#define MDIALOG_MIN_DIALOG_WIDTH 200.0
#endif

#if !defined MDIALOG_MAX_CAPTION_SIZE
	#define MDIALOG_MAX_CAPTION_SIZE 64
#endif

#if !defined MDIALOG_MAX_INFO_SIZE
	#define MDIALOG_MAX_INFO_SIZE 4096
#endif

#if defined MDIALOG_ZLANG_MODE
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

#if !defined FIX_const
	#define FIX_const 0
	#define MDIALOG_FIX_CLEAR
#endif

native MDialogFix_ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[]) = ShowPlayerDialog;

#if !FIX_const
	#if defined _ALS_ShowPlayerDialog
		#undef ShowPlayerDialog
	#else
		#define _ALS_ShowPlayerDialog
	#endif

	#define ShowPlayerDialog MDialogFix_ShowPlayerDialog

	#if defined MDIALOG_FIX_CLEAR
		#undef MDIALOG_FIX_CLEAR
		#undef FIX_const
	#endif
#endif

#if !defined isnull
	#define isnull(%1) \
				((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

// internal defines
#define DialogCreate:%0(%1) \
	forward dcr_%0(%1); \
	public dcr_%0(%1)

#define DialogResponse:%0(%1) \
	forward dre_%0(%1); \
	public dre_%0(%1)

#define DialogInterrupt:%0(%1) \
	forward din_%0(%1); \
	public din_%0(%1)

#define Dialog: #

/*
	Enums
*/

enum E_MDIALOG_TAG {
	E_MDIALOG_TAG_NONE = -1,
	E_MDIALOG_TAG_CENTER,
	E_MDIALOG_TAG_RIGHT,
};

/*
	Vars
*/

#if !defined MDIALOG_DISABLE_TAGS
static
	Float:gCharSize[256] = {
		-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
		4.4453125, // space
		5.328125, // !
		7.5859375, // "
		8.8984375, // #
		8.8984375, // $
		14.2265625, // %
		11.5546875, // &
		3.8046875, // '
		5.328125, // (
		5.328125, // )
		6.2265625, // *
		9.34375, // +
		4.4453125, // ,
		5.328125, // -
		4.4453125, // .
		4.4453125, // /
		8.8984375, // 0
		8.8984375, // 1
		8.8984375, // 2
		8.8984375, // 3
		8.8984375, // 4
		8.8984375, // 5
		8.8984375, // 6
		8.8984375, // 7
		8.8984375, // 8
		8.8984375, // 9
		5.328125, // :
		5.328125, // ;
		9.34375, // <
		9.34375, // =
		9.34375, // >
		9.7734375, // ?
		15.6015625, // @
		11.5546875, // A
		11.5546875, // B
		11.5546875, // C
		11.5546875, // D
		10.671875, // E
		9.7734375, // F
		12.4453125, // G
		11.5546875, // H
		4.4453125, // I
		8.8984375, // J
		11.5546875, // K
		9.7734375, // L
		13.328125, // M
		11.5546875, // N
		12.4453125, // O
		10.671875, // P
		12.4453125, // Q
		11.5546875, // R
		10.671875, // S
		9.7734375, // T
		11.5546875, // U
		10.671875, // V
		15.1015625, // W
		10.671875, // X
		10.671875, // Y
		9.7734375, // Z
		5.328125, // [
		4.4453125, // backslash
		5.328125, // ]
		9.34375, // ^
		8.8984375, // _
		5.328125, // `
		8.8984375, // a
		9.7734375, // b
		8.8984375, // c
		9.7734375, // d
		8.8984375, // e
		5.328125, // f
		9.7734375, // g
		9.7734375, // h
		4.4453125, // i
		4.4453125, // j
		8.8984375, // k
		4.4453125, // l
		14.2265625, // m
		9.7734375, // n
		9.7734375, // o
		9.7734375, // p
		9.7734375, // q
		6.2265625, // r
		8.8984375, // s
		5.328125, // t
		9.7734375, // u
		8.8984375, // v
		12.4453125, // w
		8.8984375, // x
		8.8984375, // y
		8.0, // z
		6.2265625, // {
		4.4765625, // |
		6.2265625, // }
		9.34375, // ~
		8.0, // 
		14.1640625, // €
		9.0703125, // 
		4.4453125, // ‚
		6.6640625, // ƒ
		8.0, // „
		16.0, // …
		8.8984375, // †
		8.8984375, // ‡
		8.8984375, // ˆ
		16.0, // ‰
		17.5, // Š
		5.328125, // ‹
		17.0, // Œ
		9.765625, // 
		14.0, // Ž
		11.5, // 
		9.7734375, // 
		4.4453125, // ‘
		4.4453125, // ’
		8.0, // “
		8.0, // ”
		5.6015625, // •
		8.8984375, // –
		16.0, // —
		16.0, // ™
		15.5, // š
		5.328125, // ›
		14.5, // œ
		8.0078125, // 
		9.7734375, // ž
		9.6640625, // Ÿ
		4.4453125, //
		9.953125, // ¡
		8.8984375, // ¢
		8.8984375, // £
		8.8984375, // ¤
		7.7890625, // ¥
		4.4765625, // ¦
		8.8984375, // §
		-1.0,
		10.703125, // ¨
		11.7890625, // ©
		11.3828125, // ª
		8.8984375, // «
		9.34375, // ¬
		0.0, // ­
		11.7890625, // ®
		4.4140625, // ¯
		6.3984375, // °
		8.78125, // ±
		4.4453125, // ²
		4.4453125, // ³
		7.1484375, // ´
		9.21875, // µ
		8.8984375, // ¶
		5.328125, // ·
		8.8984375, // ¸
		17.8359375, // ¹
		8.8359375, // º
		8.8984375, // »
		4.4453125, // ¼
		10.671875, // ½
		8.8984375, // ¾
		4.5, // ¿
		11.5546875, // À
		11.5, // Á
		11.5546875, // Â
		9.0703125, // Ã
		11.3984375, // Ä
		10.671875, // Å
		14.4609375, // Æ
		10.0234375, // Ç
		11.5, // È
		11.5, // É
		9.765625, // Ê
		11.2265625, // Ë
		13.328125, // Ì
		11.5546875, // Í
		12.4453125, // Î
		11.5, // Ï
		10.671875, // Ð
		11.5546875, // Ñ
		9.7734375, // Ò
		9.953125, // Ó
		13.65625, // Ô
		10.671875, // Õ
		11.6875, // Ö
		11.2421875, // ×
		16.078125, // Ø
		16.3046875, // Ù
		13.9140625, // Ú
		15.6640625, // Û
		11.5, // Ü
		11.3828125, // Ý
		16.5, // Þ
		11.5, // ß
		8.8984375, // à
		9.8828125, // á
		9.8359375, // â
		6.6640625, // ã
		10.15625, // ä
		8.8984375, // å
		11.34375, // æ
		7.953125, // ç
		9.8359375, // è
		9.8359375, // é
		8.0078125, // ê
		10.1640625, // ë
		11.8359375, // ì
		9.6640625, // í
		9.7734375, // î
		9.6640625, // ï
		9.7734375, // ð
		8.8984375, // ñ
		7.8359375, // ò
		8.8984375, // ó
		14.0, // ô
		8.8984375, // õ
		9.8359375, // ö
		9.2890625, // ÷
		13.3359375, // ø
		13.5, // ù
		11.6640625, // ú
		13.6640625, // û
		9.8359375, // ü
		8.8359375, // ý
		13.6640625, // þ
		9.3359375 // ÿ
	};

static
	gTag[E_MDIALOG_TAG][] = {
		"\\c",
		"\\r"
	},
	gTagLength[E_MDIALOG_TAG];

#endif

static
	bool:gIsDialogOpen[MAX_PLAYERS char],
	gDialogFunction[MAX_PLAYERS][MAX_FUNCTION_NAME];

/*
	OnGameModeInit
*/

#if !defined MDIALOG_DISABLE_TAGS

public OnGameModeInit()
{
	for (new tag = 0; tag < sizeof(gTag); tag++) {
		gTagLength[E_MDIALOG_TAG:tag] = strlen(gTag[E_MDIALOG_TAG:tag]);
	}

	#if defined MDialog_OnGameModeInit
		return MDialog_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit MDialog_OnGameModeInit
#if defined MDialog_OnGameModeInit
	forward MDialog_OnGameModeInit();
#endif

#endif

/*
	ShowPlayerDialog
*/

stock MDialog_ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[])
{
	if (dialogid != -1 && dialogid != MDIALOG_DIALOG_ID) {
		if (Dialog_IsOpen(playerid)) {
			Dialog_Close(playerid, gDialogFunction[playerid][4], false);
		}
	}

	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}
#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif

#define ShowPlayerDialog MDialog_ShowPlayerDialog

/*
	Dialog_Open
*/

static stock _Dialog_Open(playerid, const function[], style, const caption[], const info[], const button1[], const button2[])
{
	if (Dialog_IsOpen(playerid)) {
		Dialog_Interrupt(playerid, gDialogFunction[playerid][4]);
	}

	gIsDialogOpen{playerid} = true;

	gDialogFunction[playerid] = "dre_";
	strcat(gDialogFunction[playerid], function, sizeof(gDialogFunction[]));

	switch (style) {
		case DIALOG_STYLE_MSGBOX, DIALOG_STYLE_INPUT, DIALOG_STYLE_PASSWORD: {
			#if defined MDIALOG_DISABLE_TAGS
				return ShowPlayerDialog(playerid, MDIALOG_DIALOG_ID, style, caption, info, button1, button2);
			#else
				static info_result[MDIALOG_MAX_INFO_SIZE];
				_MDialog_ProcessTags(info, info_result);
				return ShowPlayerDialog(playerid, MDIALOG_DIALOG_ID, style, caption, info_result, button1, button2);
			#endif
		}
	}

	return ShowPlayerDialog(playerid, MDIALOG_DIALOG_ID, style, caption, info, button1, button2);
}

#if defined MDIALOG_ZLANG_MODE

stock Dialog_Open(playerid, const function[], style, const caption[], const info[], const button1[], const button2[], lang_args<>)
{
	static
		Lang:lang,
		temp_caption[MDIALOG_MAX_CAPTION_SIZE],
		temp_button1[MDIALOG_MAX_BUTTON_SIZE],
		temp_button2[MDIALOG_MAX_BUTTON_SIZE],
		temp_info[MDIALOG_MAX_INFO_SIZE];

	lang = Lang_GetPlayerLang(playerid);

	Lang_GetText(lang, caption, temp_caption);
	Lang_GetText(lang, info, temp_info);
	Lang_GetText(lang, button1, temp_button1);

	if (!isnull(button2)) {
		Lang_GetText(lang, button2, temp_button2);
	} else {
		temp_button2[0] = '\0';
	}

	if (numargs() > 7) {
		Lang_format(temp_info, sizeof(temp_info), temp_info, lang_start<7>);
	}

	return _Dialog_Open(playerid, function, style, temp_caption, temp_info, temp_button1, temp_button2);
}

#else

stock Dialog_Open(playerid, const function[], style, const caption[], const info[], const button1[], const button2[])
{
	return _Dialog_Open(playerid, function, style, caption, info, button1, button2);
}

#endif

/*
	Dialog_Close
*/

stock Dialog_Close(playerid, const function[] = "", showDialog = true)
{
	gIsDialogOpen{playerid} = false;
	gDialogFunction[playerid][0] = '\0';

	Dialog_Interrupt(playerid, function);

	if (showDialog) {
		return MDialogFix_ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, " ", " ", " ", "");
	}

	return 1;
}

stock Dialog_Interrupt(playerid, const function[])
{
	if (!isnull(function)) {
		new call_func[MAX_FUNCTION_NAME char] = !"din_";
		strcat(call_func, function);
		return CallLocalFunction(call_func, "d", playerid);
	}
	return 0;
}

/*
	Dialog_IsOpen
*/

stock Dialog_IsOpen(playerid, const function[] = "")
{
	if (isnull(function)) {
		return _:gIsDialogOpen{playerid};
	}

	if (!isnull(gDialogFunction[playerid]) && gIsDialogOpen{playerid} && strcmp(gDialogFunction[playerid][4], function) == 0) {
		return 1;
	}

	return 0;
}

/*
	Dialog_Show
*/

stock Dialog_Show(playerid, const function[])
{
	new call_func[MAX_FUNCTION_NAME char] = !"dcr_";
	strcat(call_func, function);
	return CallLocalFunction(call_func, "d", playerid);
}

/*
	Dialog_GetCurrent
*/

stock Dialog_GetCurrent(playerid, function[], const size = sizeof(function))
{
	if (gDialogFunction[playerid][0] == '\0') {
		function[0] = '\0';
		return 0;
	}

	return _MDialog_strcpy(function, gDialogFunction[playerid][4], size);
}

/*
	Dialog_Message
*/

#if defined MDIALOG_ZLANG_MODE

stock Dialog_Message(playerid, const caption[], const info[], const button1[], lang_args<>)
{
	static
		Lang:lang,
		temp_caption[MDIALOG_MAX_CAPTION_SIZE],
		temp_button1[MDIALOG_MAX_BUTTON_SIZE],
		temp_info[MDIALOG_MAX_INFO_SIZE];

	lang = Lang_GetPlayerLang(playerid);

	Lang_GetText(lang, caption, temp_caption);
	Lang_GetText(lang, info, temp_info);
	Lang_GetText(lang, button1, temp_button1);

	if (numargs() > 4) {
		Lang_format(temp_info, sizeof(temp_info), temp_info, lang_start<4>);
	}

	return _Dialog_Open(playerid, Dialog:Message, DIALOG_STYLE_MSGBOX, temp_caption, temp_info, temp_button1, "");
}

#else

stock Dialog_Message(playerid, const caption[], const info[], const button1[])
{
	return _Dialog_Open(playerid, Dialog:Message, DIALOG_STYLE_MSGBOX, caption, info, button1, "");
}

#endif

/*
	Dialog_MessageEx
*/

#if defined MDIALOG_ZLANG_MODE

stock Dialog_MessageEx(playerid, const response[], const caption[], const info[], const button1[], const button2[], lang_args<>)
{
	static
		Lang:lang,
		temp_caption[MDIALOG_MAX_CAPTION_SIZE],
		temp_button1[MDIALOG_MAX_BUTTON_SIZE],
		temp_button2[MDIALOG_MAX_BUTTON_SIZE],
		temp_info[MDIALOG_MAX_INFO_SIZE];

	lang = Lang_GetPlayerLang(playerid);

	Lang_GetText(lang, caption, temp_caption);
	Lang_GetText(lang, info, temp_info);
	Lang_GetText(lang, button1, temp_button1);

	if (!isnull(button2)) {
		Lang_GetText(lang, button2, temp_button2);
	} else {
		temp_button2[0] = '\0';
	}

	if (numargs() > 6) {
		Lang_format(temp_info, sizeof(temp_info), temp_info, lang_start<6>);
	}

	return _Dialog_Open(playerid, response, DIALOG_STYLE_MSGBOX, temp_caption, temp_info, temp_button1, temp_button2);
}

#else

stock Dialog_MessageEx(playerid, const response[], const caption[], const info[], const button1[], const button2[])
{
	return _Dialog_Open(playerid, response, DIALOG_STYLE_MSGBOX, caption, info, button1, button2);
}

#endif

/*
	OnDialogResponse
*/

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	static temp[128];
	_MDialog_strcpy(temp, inputtext);

	if (dialogid == MDIALOG_DIALOG_ID) {
		if (temp[0] == '\0') {
			if (Dialog_IsOpen(playerid)) {
				gIsDialogOpen{playerid} = false;
				return CallLocalFunction(gDialogFunction[playerid], "ddds", playerid, response, listitem, "\1");
			}
			return 0;
		}

		for (new i = strlen(temp) - 1; i != -1; i--) {
			if (temp[i] == '%') {
				temp[i] = '#';
			}
		}

		if (Dialog_IsOpen(playerid)) {
			gIsDialogOpen{playerid} = false;
			return CallLocalFunction(gDialogFunction[playerid], "ddds", playerid, response, listitem, temp);
		}
		return 0;
	}

	#if defined MDialog_OnDialogResponse
		return MDialog_OnDialogResponse(playerid, dialogid, response, listitem, temp);
	#else
		return 0;
	#endif
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif

#define OnDialogResponse MDialog_OnDialogResponse
#if defined MDialog_OnDialogResponse
	forward MDialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

/*
	_MDialog_ProcessTags
*/
#if !defined MDIALOG_DISABLE_TAGS

static stock _MDialog_ProcessTags(const info[], result_info[], const size = sizeof(result_info))
{
	static
		line_lengths[MDIALOG_MAX_LINES],
		Float:line_sizes[MDIALOG_MAX_LINES],
		line_pos[MDIALOG_MAX_LINES],
		sep_pos,
		prev_sep_pos,
		E_MDIALOG_TAG:tag,
		tag_pos,
		tag_length,
		E_MDIALOG_TAG:tag_line[MDIALOG_MAX_LINES],
		lines_count,
		length,
		Float:max_size,
		i,
		Float:temp_size;

	// if string is packed
	if (info{0} != 0) {
		strunpack(result_info, info, size);
	} else {
		_MDialog_strcpy(result_info, info, size);
	}

	// reset variables
	lines_count = 0;
	sep_pos = 0;
	prev_sep_pos = 0;
	max_size = 0.0;

	// get biggest line and save line sizes
	while (sep_pos >= 0) {
		// get line length
		sep_pos = strfind(result_info, "\n", false, prev_sep_pos + 1);
		if (sep_pos == -1) {
			length = strlen(result_info) - prev_sep_pos - 1;
		} else {
			length = sep_pos - prev_sep_pos - _:(lines_count != 0);
			line_pos[lines_count + 1] = sep_pos + 1;
		}

		// check for tag
		tag_line[lines_count] = E_MDIALOG_TAG_NONE;

		for (tag = E_MDIALOG_TAG:0; tag < E_MDIALOG_TAG; tag++) {
			tag_pos = line_pos[lines_count] - 1;
			if (tag_pos < 0) {
				tag_pos = 0;
			}

			tag_pos = strfind(result_info, gTag[tag], false, tag_pos);

			// if tag exists
			if (tag_pos != -1 && (sep_pos == -1 || tag_pos < line_pos[lines_count + 1])) {
				tag_line[lines_count] = tag;

				// remove the tag
				tag_length = gTagLength[tag];

				strdel(result_info, tag_pos, tag_pos + tag_length);
				length -= tag_length;
				sep_pos -= tag_length;
				line_pos[lines_count + 1] -= tag_length;

				break;
			}
		}

		// remember length
		line_lengths[lines_count] = length;

		// get line size
		line_sizes[lines_count] = 0;

		for (i = prev_sep_pos; i <= prev_sep_pos + length; i++) {
			if (result_info[i] == '{') {
				i += 7;
				continue;
			}

			temp_size = gCharSize[ result_info[i] ];
			if (temp_size != -1) {
				line_sizes[lines_count] += temp_size;
			}
		}

		// update max size
		temp_size = line_sizes[lines_count];
		if (temp_size > max_size) {
			max_size = temp_size;
		}

		// save separator position for the future
		prev_sep_pos = sep_pos;

		// check for array borders
		lines_count++;
		if (lines_count >= MDIALOG_MAX_LINES) {
			break;
		}
	}

	if (max_size < MDIALOG_MIN_DIALOG_WIDTH) {
		max_size = MDIALOG_MIN_DIALOG_WIDTH;
	}

	// add spaces to the string
	static
		spaces_string[MDIALOG_MAX_SPACES],
		spaces,
		j;

	for (i = 0; i < lines_count; i++) {
		// get spaces count by tag
		switch (tag_line[i]) {
			case E_MDIALOG_TAG_NONE: {
				continue;
			}
			case E_MDIALOG_TAG_CENTER: {
				spaces = floatround((max_size - line_sizes[i]) / 2.0 / gCharSize[' ']);
			}
			case E_MDIALOG_TAG_RIGHT: {
				spaces = floatround((max_size - line_sizes[i]) / gCharSize[' ']);
			}
		}

		// is spaces are needed
		if (spaces == 0) {
			continue;
		}

		// make spaces string
		for (j = 0; j <= spaces; j++) {
			spaces_string[j] = ' ';
		}

		spaces_string[spaces + 1] = '\0';
		line_sizes[i] += spaces * gCharSize[' '];

		// insert spaces into the string
		format(result_info, size, "%.*s%s%s", line_pos[i], result_info, spaces_string, result_info[ line_pos[i] ]);

		// update line positions
		for (j = i + 1; j < lines_count; j++) {
			line_pos[j] += spaces + 1;
		}
	}
}

#endif

/*
	Other functions
*/

static stock _MDialog_strcpy(result[], const source[], const size = sizeof(result))
{
	result[0] = 0;
	return strcat(result, source, size);
}

/*
	strlen
*/

stock MDialog_strlen(const string[])
{
	if (isnull(string)) {
		return 0;
	}

	return strlen(string);
}
#if defined _ALS_strlen
	#undef strlen
#else
	#define _ALS_strlen
#endif

#define strlen MDialog_strlen
