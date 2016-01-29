// Нажми ctrl+h и замени все "NEWPWN" на название инклюда
// Название должно быть уникальным
//Коммит через андроид

main()
{
    print("\n----------------------------------");
	print(" NEWPWN.inc has been included");
	PlayersPayDay();
	print("----------------------------------\n");

#if    defined    main_NEWPWN
    main_NEWPWN();
#endif
    return 1;
}
#if    defined    _ALS_main
    #undef    main
#else
    #define    _ALS_main
#endif
#define    main    main_NEWPWN
#if    defined    main_NEWPWN
main_NEWPWN();
#endif


public OnGameModeInit()
{

#if    defined    OnGameModeInit_NEWPWN
    OnGameModeInit();
#endif
	return 1;
}
#if    defined    _ALS_OnGameModeInit
    #undef    OnGameModeInit
#else
    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit    OnGameModeInit_NEWPWN
#if    defined    OnGameModeInit_NEWPWN
forward OnGameModeInit_NEWPWN();
#endif

public OnGameModeExit()
{

#if    defined    OnGameModeExit_NEWPWN
    OnGameModeExit();
#endif
	return 1;
}
#if    defined    _ALS_OnGameModeExit
    #undef    OnGameModeExit
#else
    #define    _ALS_OnGameModeExit
#endif
#define    OnGameModeExit    OnGameModeExit_NEWPWN
#if    defined    OnGameModeExit_NEWPWN
forward OnGameModeExit_NEWPWN();
#endif

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	
#if    defined    OnPlayerConnect_NEWPWN
    OnPlayerRequestClass_NEWPWN(playerid, classid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerRequestClass
    #undef    OnPlayerRequestClass
#else
    #define    _ALS_OnPlayerRequestClass
#endif
#define    OnPlayerRequestClass    OnPlayerRequestClass_NEWPWN
#if    defined    OnPlayerRequestClass_NEWPWN
forward OnPlayerRequestClass_NEWPWN(playerid, classid);
#endif

public OnPlayerConnect(playerid)
{

#if    defined    OnPlayerConnect_NEWPWN
    OnPlayerConnect_NEWPWN(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerConnect
    #undef    OnPlayerConnect
#else
    #define    _ALS_OnPlayerConnect
#endif
#define    OnPlayerConnect    OnPlayerConnect_NEWPWN
#if    defined    OnPlayerConnect_NEWPWN
forward OnPlayerConnect_NEWPWN(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{

#if    defined    OnPlayerDisconnect_NEWPWN
    OnPlayerDisconnect_NEWPWN(playerid, reason);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerDisconnect
    #undef    OnPlayerDisconnect
#else
    #define    _ALS_OnPlayerDisconnect
#endif
#define    OnPlayerDisconnect    OnPlayerDisconnect_NEWPWN
#if    defined    OnPlayerDisconnect_NEWPWN
forward OnPlayerDisconnect_NEWPWN(playerid, reason);
#endif

public OnPlayerSpawn(playerid)
{

#if    defined    OnPlayerSpawn_NEWPWN
    OnPlayerSpawn_NEWPWN(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerSpawn
    #undef    OnPlayerSpawn
#else
    #define    _ALS_OnPlayerSpawn
#endif
#define    OnPlayerSpawn    OnPlayerSpawn_NEWPWN
#if    defined    OnPlayerSpawn_NEWPWN
forward OnPlayerSpawn_NEWPWN(playerid);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{

#if    defined    OnPlayerDeath_NEWPWN
    OnPlayerDeath_NEWPWN(playerid, killerid, reason);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerDeath
    #undef    OnPlayerDeath
#else
    #define    _ALS_OnPlayerDeath
#endif
#define    OnPlayerDeath    OnPlayerDeath_NEWPWN
#if    defined    OnPlayerDeath_NEWPWN
forward OnPlayerDeath_NEWPWN(playerid, killerid, reason);
#endif

public OnVehicleSpawn(vehicleid)
{

#if    defined    OnVehicleSpawn_NEWPWN
    OnVehicleSpawn_NEWPWN(vehicleid);
#endif
	return 1;
}
#if    defined    _ALS_OnVehicleSpawn
    #undef    OnVehicleSpawn
#else
    #define    _ALS_OnVehicleSpawn
#endif
#define    OnVehicleSpawn    OnVehicleSpawn_NEWPWN
#if    defined    OnVehicleSpawn_NEWPWN
forward OnVehicleSpawn_NEWPWN(vehicleid);
#endif

public OnVehicleDeath(vehicleid, killerid)
{

#if    defined    OnVehicleDeath_NEWPWN
    OnVehicleDeath_NEWPWN(vehicleid, killerid);
#endif
	return 1;
}
#if    defined    _ALS_OnVehicleDeath
    #undef    OnVehicleDeath
#else
    #define    _ALS_OnVehicleDeath
#endif
#define    OnVehicleDeath    OnVehicleDeath_NEWPWN
#if    defined    OnVehicleDeath_NEWPWN
forward OnVehicleDeath_NEWPWN(vehicleid, killerid);
#endif

public OnPlayerText(playerid, text[])
{

#if    defined    OnPlayerText_NEWPWN
    OnPlayerText_NEWPWN(playerid, text[]);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerText
    #undef    OnPlayerText
#else
    #define    _ALS_OnPlayerText
#endif
#define    OnPlayerText    OnPlayerText_NEWPWN
#if    defined    OnPlayerText_NEWPWN
forward OnPlayerText_NEWPWN(playerid, text[]);
#endif

public OnPlayerCommandText(playerid, commandtext[])
{
    if (strcmp("/mycommand", cmdtext, true, 10) == 0)
	{
		// Do something here
		return 1;
	}
#if    defined    OnPlayerCommandText_NEWPWN
    OnPlayerCommandText_NEWPWN(playerid, commandtext[]);
#endif
	return 0;
}
#if    defined    _ALS_OnPlayerCommandText
    #undef    OnPlayerCommandText
#else
    #define    _ALS_OnPlayerCommandText
#endif
#define    OnPlayerCommandText    OnPlayerCommandText_NEWPWN
#if    defined    OnPlayerCommandText_NEWPWN
forward OnPlayerCommandText_NEWPWN(playerid, commandtext[]);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{

#if    defined    OnPlayerEnterVehicle_NEWPWN
    OnPlayerEnterVehicle_NEWPWN(playerid, vehicleid, ispassenger);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerEnterVehicle
    #undef    OnPlayerEnterVehicle
#else
    #define    _ALS_OnPlayerEnterVehicle
#endif
#define    OnPlayerEnterVehicle    OnPlayerEnterVehicle_NEWPWN
#if    defined    OnPlayerEnterVehicle_NEWPWN
forward OnPlayerEnterVehicle_NEWPWN(playerid, vehicleid, ispassenger);
#endif

public OnPlayerExitVehicle(playerid, vehicleid)
{

#if    defined    OnPlayerExitVehicle_NEWPWN
    OnPlayerExitVehicle_NEWPWN(playerid, vehicleid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerExitVehicle
    #undef    OnPlayerExitVehicle
#else
    #define    _ALS_OnPlayerExitVehicle
#endif
#define    OnPlayerExitVehicle    OnPlayerExitVehicle_NEWPWN
#if    defined    OnPlayerExitVehicle_NEWPWN
forward OnPlayerExitVehicle_NEWPWN(playerid, vehicleid);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{

#if    defined    OnPlayerStateChange_NEWPWN
    OnPlayerStateChange_NEWPWN(playerid, newstate, oldstate);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerStateChange
    #undef    OnPlayerStateChange
#else
    #define    _ALS_OnPlayerStateChange
#endif
#define    OnPlayerStateChange    OnPlayerStateChange_NEWPWN
#if    defined    OnPlayerStateChange_NEWPWN
forward OnPlayerStateChange_NEWPWN(playerid, newstate, oldstate);
#endif

public OnPlayerEnterCheckpoint(playerid)
{

#if    defined    OnPlayerEnterCheckpoint_NEWPWN
    OnPlayerEnterCheckpoint_NEWPWN(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerEnterCheckpoint
    #undef    OnPlayerEnterCheckpoint
#else
    #define    _ALS_OnPlayerEnterCheckpoint
#endif
#define    OnPlayerEnterCheckpoint    OnPlayerEnterCheckpoint_NEWPWN
#if    defined    OnPlayerEnterCheckpoint_NEWPWN
forward OnPlayerEnterCheckpoint_NEWPWN(playerid);
#endif

public OnPlayerLeaveCheckpoint(playerid)
{

#if    defined    OnPlayerLeaveCheckpoint_NEWPWN
    OnPlayerLeaveCheckpoint_NEWPWN(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerLeaveCheckpoint
    #undef    OnPlayerLeaveCheckpoint
#else
    #define    _ALS_OnPlayerLeaveCheckpoint
#endif
#define    OnPlayerLeaveCheckpoint    OnPlayerLeaveCheckpoint_NEWPWN
#if    defined    OnPlayerLeaveCheckpoint_NEWPWN
forward OnPlayerLeaveCheckpoint_NEWPWN(playerid);
#endif

public OnPlayerEnterRaceCheckpoint(playerid)
{

#if    defined    OnPlayerEnterRaceCheckpoint_NEWPWN
    OnPlayerEnterRaceCheckpoint_NEWPWN(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerEnterRaceCheckpoint
    #undef    OnPlayerEnterRaceCheckpoint
#else
    #define    _ALS_OnPlayerEnterRaceCheckpoint
#endif
#define    OnPlayerEnterRaceCheckpoint    OnPlayerEnterRaceCheckpoint_NEWPWN
#if    defined    OnPlayerEnterRaceCheckpoint_NEWPWN
forward OnPlayerEnterRaceCheckpoint_NEWPWN(playerid);
#endif

public OnPlayerLeaveRaceCheckpoint(playerid)
{

#if    defined    OnPlayerLeaveRaceCheckpoint_NEWPWN
    OnPlayerLeaveRaceCheckpoint_NEWPWN(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerLeaveRaceCheckpoint
    #undef    OnPlayerLeaveRaceCheckpoint
#else
    #define    _ALS_OnPlayerLeaveRaceCheckpoint
#endif
#define    OnPlayerLeaveRaceCheckpoint    OnPlayerLeaveRaceCheckpoint_NEWPWN
#if    defined    OnPlayerLeaveRaceCheckpoint_NEWPWN
forward OnPlayerLeaveRaceCheckpoint_NEWPWN(playerid);
#endif

public OnRconCommand(cmd[])
{

#if    defined    OnRconCommand_NEWPWN
    OnRconCommand_NEWPWN(cmd[]);
#endif
	return 1;
}
#if    defined    _ALS_OnRconCommand
    #undef    OnRconCommand
#else
    #define    _ALS_OnRconCommand
#endif
#define    OnRconCommand    OnRconCommand_NEWPWN
#if    defined    OnRconCommand_NEWPWN
forward OnRconCommand_NEWPWN(cmd[]);
#endif

public OnPlayerRequestSpawn(playerid)
{

#if    defined    OnPlayerRequestSpawn_NEWPWN
    OnPlayerRequestSpawn_NEWPWN(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerRequestSpawn
    #undef    OnPlayerRequestSpawn
#else
    #define    _ALS_OnPlayerRequestSpawn
#endif
#define    OnPlayerRequestSpawn    OnPlayerRequestSpawn_NEWPWN
#if    defined    OnPlayerRequestSpawn_NEWPWN
forward OnPlayerRequestSpawn_NEWPWN(playerid);
#endif

public OnObjectMoved(objectid)
{

#if    defined    OnObjectMoved_NEWPWN
    OnObjectMoved_NEWPWN(objectid);
#endif
	return 1;
}
#if    defined    _ALS_OnObjectMoved
    #undef    OnObjectMoved
#else
    #define    _ALS_OnObjectMoved
#endif
#define    OnObjectMoved    OnObjectMoved_NEWPWN
#if    defined    OnObjectMoved_NEWPWN
forward OnObjectMoved_NEWPWN(objectid);
#endif

public OnPlayerObjectMoved(playerid, objectid)
{

#if    defined    OnPlayerObjectMoved_NEWPWN
    OnPlayerObjectMoved_NEWPWN(playerid, objectid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerObjectMoved
    #undef    OnPlayerObjectMoved
#else
    #define    _ALS_OnPlayerObjectMoved
#endif
#define    OnPlayerObjectMoved    OnPlayerObjectMoved_NEWPWN
#if    defined    OnPlayerObjectMoved_NEWPWN
forward OnPlayerObjectMoved_NEWPWN(playerid, objectid);
#endif

public OnPlayerPickUpPickup(playerid, pickupid)
{

#if    defined    OnPlayerPickUpPickup_NEWPWN
    OnPlayerPickUpPickup_NEWPWN(playerid, pickupid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerPickUpPickup
    #undef    OnPlayerPickUpPickup
#else
    #define    _ALS_OnPlayerPickUpPickup
#endif
#define    OnPlayerPickUpPickup    OnPlayerPickUpPickup_NEWPWN
#if    defined    OnPlayerPickUpPickup_NEWPWN
forward OnPlayerPickUpPickup_NEWPWN(playerid, pickupid);
#endif

public OnVehicleMod(playerid, vehicleid, componentid)
{

#if    defined    OnVehicleMod_NEWPWN
    OnVehicleMod_NEWPWN(playerid, vehicleid, componentid);
#endif
	return 1;
}
#if    defined    _ALS_OnVehicleMod
    #undef    OnVehicleMod
#else
    #define    _ALS_OnVehicleMod
#endif
#define    OnVehicleMod    OnVehicleMod_NEWPWN
#if    defined    OnVehicleMod_NEWPWN
forward OnVehicleMod_NEWPWN(playerid, vehicleid, componentid);
#endif

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{

#if    defined    OnVehiclePaintjob_NEWPWN
    OnVehiclePaintjob_NEWPWN(playerid, vehicleid, paintjobid);
#endif
	return 1;
}
#if    defined    _ALS_OnVehiclePaintjob
    #undef    OnVehiclePaintjob
#else
    #define    _ALS_OnVehiclePaintjob
#endif
#define    OnVehiclePaintjob    OnVehiclePaintjob_NEWPWN
#if    defined    OnVehiclePaintjob_NEWPWN
forward OnVehiclePaintjob_NEWPWN(playerid, vehicleid, paintjobid);
#endif

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{

#if    defined    OnVehicleRespray_NEWPWN
    OnVehicleRespray_NEWPWN(playerid, vehicleid, color1, color2);
#endif
	return 1;
}
#if    defined    _ALS_OnVehicleRespray
    #undef    OnVehicleRespray
#else
    #define    _ALS_OnVehicleRespray
#endif
#define    OnVehicleRespray    OnVehicleRespray_NEWPWN
#if    defined    OnVehicleRespray_NEWPWN
forward OnVehicleRespray_NEWPWN(playerid, vehicleid, color1, color2);
#endif

public OnPlayerSelectedMenuRow(playerid, row)
{

#if    defined    OnPlayerSelectedMenuRow_NEWPWN
    OnPlayerSelectedMenuRow_NEWPWN(playerid, row);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerSelectedMenuRow
    #undef    OnPlayerSelectedMenuRow
#else
    #define    _ALS_OnPlayerSelectedMenuRow
#endif
#define    OnPlayerSelectedMenuRow    OnPlayerSelectedMenuRow_NEWPWN
#if    defined    OnPlayerSelectedMenuRow_NEWPWN
forward OnPlayerSelectedMenuRow_NEWPWN(playerid, row);
#endif

public OnPlayerExitedMenu(playerid)
{

#if    defined    OnPlayerExitedMenu_NEWPWN
    OnPlayerExitedMenu_NEWPWN(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerExitedMenu
    #undef    OnPlayerExitedMenu
#else
    #define    _ALS_OnPlayerExitedMenu
#endif
#define    OnPlayerExitedMenu    OnPlayerExitedMenu_NEWPWN
#if    defined    OnPlayerExitedMenu_NEWPWN
forward OnPlayerExitedMenu_NEWPWN(playerid);
#endif

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{

#if    defined    OnPlayerInteriorChange_NEWPWN
    OnPlayerInteriorChange_NEWPWN(playerid, newinteriorid, oldinteriorid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerInteriorChange
    #undef    OnPlayerInteriorChange
#else
    #define    _ALS_OnPlayerInteriorChange
#endif
#define    OnPlayerInteriorChange    OnPlayerInteriorChange_NEWPWN
#if    defined    OnPlayerInteriorChange_NEWPWN
forward OnPlayerInteriorChange_NEWPWN(playerid, newinteriorid, oldinteriorid);
#endif

public OnPlayerKeyStateChange(playerid, neykeys, oldkeys)
{

#if    defined    OnPlayerKeyStateChange_NEWPWN
    OnPlayerKeyStateChange_NEWPWN(playerid, neykeys, oldkeys);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerKeyStateChange
    #undef    OnPlayerKeyStateChange
#else
    #define    _ALS_OnPlayerKeyStateChange
#endif
#define    OnPlayerKeyStateChange    OnPlayerKeyStateChange_NEWPWN
#if    defined    OnPlayerKeyStateChange_NEWPWN
forward OnPlayerKeyStateChange_NEWPWN(playerid, neykeys, oldkeys);
#endif

public OnRconLoginAttempt(ip[], password[], success)
{

#if    defined    OnRconLoginAttempt_NEWPWN
    OnRconLoginAttempt_NEWPWN(ip[], password[], success);
#endif
	return 1;
}
#if    defined    _ALS_OnRconLoginAttempt
    #undef    OnRconLoginAttempt
#else
    #define    _ALS_OnRconLoginAttempt
#endif
#define    OnRconLoginAttempt    OnRconLoginAttempt_NEWPWN
#if    defined    OnRconLoginAttempt_NEWPWN
forward OnRconLoginAttempt_NEWPWN(ip[], password[], success);
#endif

public OnPlayerUpdate(playerid)
{

#if    defined    OnPlayerUpdate_NEWPWN
    OnPlayerUpdate_NEWPWN(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerUpdate
    #undef    OnPlayerUpdate
#else
    #define    _ALS_OnPlayerUpdate
#endif
#define    OnPlayerUpdate    OnPlayerUpdate_NEWPWN
#if    defined    OnPlayerUpdate_NEWPWN
forward OnPlayerUpdate_NEWPWN(playerid);
#endif

public OnPlayerStreamIn(playerid, forplayerid)
{

#if    defined    OnPlayerStreamIn_NEWPWN
    OnPlayerStreamIn_NEWPWN(playerid, forplayerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerStreamIn
    #undef    OnPlayerStreamIn
#else
    #define    _ALS_OnPlayerStreamIn
#endif
#define    OnPlayerStreamIn    OnPlayerStreamIn_NEWPWN
#if    defined    OnPlayerStreamIn_NEWPWN
forward OnPlayerStreamIn_NEWPWN(playerid, forplayerid);
#endif

public OnPlayerStreamOut(playerid, forplayerid)
{

#if    defined    OnPlayerStreamOut_NEWPWN
    OnPlayerStreamOut_NEWPWN(playerid, forplayerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerStreamOut
    #undef    OnPlayerStreamOut
#else
    #define    _ALS_OnPlayerStreamOut
#endif
#define    OnPlayerStreamOut    OnPlayerStreamOut_NEWPWN
#if    defined    OnPlayerStreamOut_NEWPWN
forward OnPlayerStreamOut_NEWPWN(playerid, forplayerid);
#endif

public OnVehicleStreamIn(vehicleid, forvehicleid)
{

#if    defined    OnVehicleStreamIn_NEWPWN
    OnVehicleStreamIn_NEWPWN(vehicleid, forvehicleid);
#endif
	return 1;
}
#if    defined    _ALS_OnVehicleStreamIn
    #undef    OnVehicleStreamIn
#else
    #define    _ALS_OnVehicleStreamIn
#endif
#define    OnVehicleStreamIn    OnVehicleStreamIn_NEWPWN
#if    defined    OnVehicleStreamIn_NEWPWN
forward OnVehicleStreamIn_NEWPWN(vehicleid, forvehicleid);
#endif

public OnVehicleStreamOut(vehicleid, forvehicleid)
{

#if    defined    OnVehicleStreamOut_NEWPWN
    OnVehicleStreamOut_NEWPWN(vehicleid, forvehicleid);
#endif
	return 1;
}
#if    defined    _ALS_OnVehicleStreamOut
    #undef    OnVehicleStreamOut
#else
    #define    _ALS_OnVehicleStreamOut
#endif
#define    OnVehicleStreamOut    OnVehicleStreamOut_NEWPWN
#if    defined    OnVehicleStreamOut_NEWPWN
forward OnVehicleStreamOut_NEWPWN(vehicleid, forvehicleid);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{

#if    defined    OnDialogResponse_NEWPWN
    OnDialogResponse_NEWPWN(playerid, dialogid, response, listitem, inputtext[]);
#endif
	return 1;
}
#if    defined    _ALS_OnDialogResponse
    #undef    OnDialogResponse
#else
    #define    _ALS_OnDialogResponse
#endif
#define    OnDialogResponse    OnDialogResponse_NEWPWN
#if    defined    OnDialogResponse_NEWPWN
forward OnDialogResponse_NEWPWN(playerid, dialogid, response, listitem, inputtext[]);
#endif


public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{

#if    defined    OnPlayerClickPlayer_NEWPWN
    OnPlayerClickPlayer_NEWPWN(playerid, clickedplayerid, source);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerClickPlayer
    #undef    OnPlayerClickPlayer
#else
    #define    _ALS_OnPlayerClickPlayer
#endif
#define    OnPlayerClickPlayer    OnPlayerClickPlayer_NEWPWN
#if    defined    OnPlayerClickPlayer_NEWPWN
forward OnPlayerClickPlayer_NEWPWN(playerid, clickedplayerid, source);
#endif
