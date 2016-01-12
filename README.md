# mdialog
Modern dialog system

# Functions
```Pawn
// open dialog
Dialog_Open(playerid, function[], style, caption[], info[], button1[], button2[]);
// close dialog
Dialog_Close(playerid);
// check on openning dialog
Dialog_IsOpen(playerid);
// show dialog by name
Dialog_Show(playerid, function[]);
// show message dialog
Dialog_Message(playerid, caption[], info[], button1[]);
// show message dialog with custop response callback
Dialog_MessageEx(playerid, response[], caption[], info[], button1[], button2[]);
```

# Usage
You can use `DialogCreate:` and `DialogResponse:` prefixes:
```Pawn
DialogCreate:test(playerid)
{
	Dialog_Open(playerid, Dialog:test, DIALOG_STYLE_MSGBOX,
			"Hello",
			"Are you ok?",
			"Yes", "No"
		);
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
