# mdialog
Modern dialog system.

# Functions
#### Open dialog
```Pawn
Dialog_Open(playerid, function[], style, caption[], info[], button1[], button2[]);
```

#### Close dialog
```Pawn
Dialog_Close(playerid);
```

#### Check on openning dialog
```Pawn
Dialog_IsOpen(playerid);
```

#### Show dialog by name
```Pawn
Dialog_Show(playerid, function[]);
```

#### Show message dialog
```Pawn
Dialog_Message(playerid, caption[], info[], button1[]);
```

#### Show message dialog with custom response callback
```Pawn
Dialog_MessageEx(playerid, response[], caption[], info[], button1[], button2[]);
```

# [zlang](https://github.com/Open-GTO/zlang) support
If MDIALOG_ZLANG_MODE is defined then some mdialog functions take a new view.

#### Open dialog
```Pawn
Dialog_Open(playerid, function[], style, caption[], info[], button1[], button2[], notvar_flags = MDIALOG_NOTVAR_NONE, {Float, _}:...);
```

#### Show message dialog
```Pawn
Dialog_Message(playerid, caption[], info[], button1[], notvar_flags = MDIALOG_NOTVAR_NONE, {Float, _}:...);
```

#### Show message dialog with custom response callback
```Pawn
Dialog_MessageEx(playerid, response[], caption[], info[], button1[], button2[], notvar_flags = MDIALOG_NOTVAR_NONE, {Float, _}:...);
```

#### Bit flags for **notvar_flags**
```
MDIALOG_NOTVAR_ALL
MDIALOG_NOTVAR_NONE
MDIALOG_NOTVAR_CAPTION
MDIALOG_NOTVAR_INFO
MDIALOG_NOTVAR_BUTTON1
MDIALOG_NOTVAR_BUTTON2
```

# Tags support
You can use tags for markup your dialogs:

Tag | Description
----|-----------
\\\c | Centers the text
\\\r | Aligns the text to the right

![tags example](https://user-images.githubusercontent.com/1020099/30522188-aac33382-9bd4-11e7-9d78-92b240309931.png)

# Usage
You can use `DialogCreate:` and `DialogResponse:` prefixes:
```Pawn
DialogCreate:test(playerid)
{
	Dialog_Open(playerid, Dialog:test, DIALOG_STYLE_MSGBOX,
	            "Hello",
	            "Are you ok?",
	            "Yes", "No");
}

DialogResponse:test(playerid, response, listitem, inputtext[])
{
	if (!response) {
		SendClientMessage(playerid, -1, "This club only for OK guys!");
		Dialog_Show(playerid, Dialog:test);
		return 1;
	}

	SendClientMessage(playerid, -1, "Welcome to the club");
	return 1;
}
```

# Usage with zlang mode
```Pawn
#define MDIALOG_ZLANG_MODE
#include "mdialog"

DialogCreate:test(playerid)
{
	Dialog_Open(playerid, Dialog:test, DIALOG_STYLE_MSGBOX,
	            "Hello",
	            "LANG_ARE_YOU_OK",
	            "Yes", "BUTTON_NO",
	            MDIALOG_NOTVAR_CAPTION | MDIALOG_NOTVAR_BUTTON1,
	            playerid);
}

DialogResponse:test(playerid, response, listitem, inputtext[])
{
	if (!response) {
		SendClientMessage(playerid, -1, "This club only for OK guys!");
		Dialog_Show(playerid, Dialog:test);
		return 1;
	}

	SendClientMessage(playerid, -1, "Welcome to the club");
	return 1;
}
```

Lang file:
```
LANG_ARE_YOU_OK = Hey id %d, are you ok?
BUTTON_NO = No
```
