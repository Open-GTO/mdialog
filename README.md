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

#### Check on opening dialog by name or any (if function is empty)
```Pawn
Dialog_IsOpen(playerid, function[] = "");
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
Dialog_Open(playerid, function[], style, caption[], info[], button1[], button2[], {Float, _}:...);
```

#### Show message dialog
```Pawn
Dialog_Message(playerid, caption[], info[], button1[], {Float, _}:...);
```

#### Show message dialog with custom response callback
```Pawn
Dialog_MessageEx(playerid, response[], caption[], info[], button1[], button2[], {Float, _}:...);
```

# Tags support
You can use tags for markup your dialogs:

Tag | Description
----|-----------
\\\c | Centers the text
\\\r | Aligns the text to the right

![tags example](https://user-images.githubusercontent.com/1020099/30522188-aac33382-9bd4-11e7-9d78-92b240309931.png)

You also can disable tags with definition of `MDIALOG_DISABLE_TAGS` before `mdialog` including. This can be useful if you are not interested in this feature and wants a little bit more performance.

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
