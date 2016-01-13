#define MAILER_URL "epic-rp.esy.es/mailer.php" // This has to be defined BEFORE you include mailer.
#define isnull(%1) \
((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))

#include <a_samp>
#include <a_mysql>
#include <foreach>
#include <streamer>
#include <sscanf2>
#include <dc_cmd>
#include <gvar>
#include <regex>
#include <easyDialog>
#include <md5>
#include <a_mailer>

#define SERVER_NAME			"Epic Roleplay"
#define SERVER_NUMBER		"Development"
#define SERVER_COUNTRY		"San Andreas"
#define GAMEMODE_NAME		"ERP"
#define GAMEMODE_VERSION	"0.0.8"

new MySQL;
#define SQL_HOST			"localhost"
#define SQL_DB				"epicrp"
#define SQL_USER			"root"
#define SQL_PASS			""

#define S_ACCEPT			1054
#define S_DENY              1055
#define S_MISSIONCOMPLETE	1058

#define COLOR_WHITE			0xFFFFFFFF
#define COLOR_LOGO          0x565656FF
#define COLOR_GRAY          0x919191FF
#define COLOR_GRAY2         0x565656FF
#define COLOR_PINK          0xFFC0CBFF
#define COLOR_RED           0xE91218FF
#define COLOR_YELLOW        0xe6e912FF
#define COLOR_GREEN         0x12e97bFF
#define COLOR_BLACK         0x000000FF

#define cOLOR_WHITE			FFFFFF
#define cOLOR_ORANGE        e94b12
#define cOLOR_GRAY          919191
#define cOLOR_GRAY2         565656
#define cOLOR_BLACK         000000
#define cOLOR_AQUA          68C4AF
#define cOLOR_GREEN         12e97b
#define cOLOR_RED           E91218
#define cOLOR_PINK          FFC0CB

#include <epicrp/players.inc>
#include <epicrp/vehicles.inc>
#include <epicrp/interiors.inc>
#include <epicrp/inventory.inc>
#include <epicrp/gps.inc>

AntiDeAMX()
{
    new a[][] =
    {
        "Unarmed (Fist)",
        "Brass K"
    };
    #pragma unused a
}

main()
{
	print("\n----------------------------------");
	print(" EpicRP gamemode has been started");
	print("----------------------------------\n");
}

public OnGameModeInit()
{
    AntiDeAMX();
	SendRconCommand("hostname "SERVER_NAME" | Server: "SERVER_NUMBER);
	SendRconCommand("mapname "SERVER_COUNTRY);
	SetGameModeText(GAMEMODE_NAME" v"GAMEMODE_VERSION);
	
	mysql_log(LOG_ERROR | LOG_WARNING, LOG_TYPE_HTML);
	MySQL = mysql_connect(SQL_HOST, SQL_USER,SQL_DB, SQL_PASS);
    mysql_query(MySQL, "SET CHARSET cp1251");
	mysql_query(MySQL, "SET COLLATION_CONNECTION=cp1251");
	mysql_query(MySQL, "SET CHARACTER_SET_CLIENT=cp1251");
	mysql_query(MySQL, "SET CHARACTER_SET_RESULTS=cp1251");
	mysql_query(MySQL, "SET NAMES cp1251;");
    mysql_query(MySQL, "SET SESSION character_set_server=cp1251;");
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	return 1;
}

public OnPlayerConnect(playerid)
{
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnPlayerSpawn(playerid)
{
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 0;
}

public OnPlayerCommandText(playerid, cmdtext[])
{

	return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}
