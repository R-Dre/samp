enum mInfo
{
	mName[MAX_PLAYER_NAME],
	mPrice
};

enum nInfo
{
	gpsName[50],
	Float: gpsX,
	Float: gpsY,
	Float: gpsZ
};

new NAVInfo[30][nInfo] = {
	{"���-������", 0.0, 0.0, 0.0},
	{"����� �.���-������", 0.0, 0.0, 0.0},
	{"����������� ����������� �.���-������", 0.0, 0.0, 0.0},
	{"�������� �.���-������", 0.0, 0.0, 0.0},
	{"����� ��������� �.���-������", 0.0, 0.0, 0.0},
	{"����������� �����", 0.0, 0.0, 0.0},
	{"��������� ������ ������", 0.0, 0.0, 0.0},
	{"��������� �.���-������", 0.0, 0.0, 0.0},
	{"�������� ������������ �.���-������", 0.0, 0.0, 0.0},
	{"���������� ������", 0.0, 0.0, 0.0},
	{"���-������", 0.0, 0.0, 0.0},
	{"����� �.���-������", 0.0, 0.0, 0.0},
	{"����������� ����������� �.���-������", 0.0, 0.0, 0.0},
	{"�������� �.���-������", 0.0, 0.0, 0.0},
	{"����� ��������� �.���-������", 0.0, 0.0, 0.0},
	{"��������� �����", 0.0, 0.0, 0.0},
	{"��������� �������� ������", 0.0, 0.0, 0.0},
	{"��������� �.���-������", 0.0, 0.0, 0.0},
	{"�������� ������������ �.���-������", 0.0, 0.0, 0.0},
	{"������-������� ����", 0.0, 0.0, 0.0},
	{"���-��������", 0.0, 0.0, 0.0},
	{"����� �.���-��������", 0.0, 0.0, 0.0},
	{"����������� ����������� �.���-��������", 0.0, 0.0, 0.0},
	{"�������� �.���-��������", 0.0, 0.0, 0.0},
	{"����� ��������� �.���-��������", 0.0, 0.0, 0.0},
	{"��������������������� �����", 0.0, 0.0, 0.0},
	{"��������� ������� ������", 0.0, 0.0, 0.0},
	{"��������� �.���-��������", 0.0, 0.0, 0.0},
	{"�������� ������������ �.���-��������", 0.0, 0.0, 0.0},
	{"������-��������� ����", 0.0, 0.0, 0.0}
};

new aVehicleNames[212][mInfo] = {	// Vehicle Names - Betamaster
	{"Landstalker",26500},
	{"Bravura",3000},
	{"Buffalo",60000},
	{"Linerunner",50000},
	{"Perrenial",4500},
	{"Sentinel",35000},
	{"Dumper",80000},
	{"Firetruck",50000},
	{"Trashmaster",35000},
	{"Stretch",60000},
	{"Manana",3500},
	{"Infernus",12000},
	{"Voodoo",17000},
	{"Pony",5000},
	{"Mule",6000},
	{"Cheetah",80000},
	{"Ambulance",50000},
	{"Leviathan",300000},
	{"Moonbeam",5000},
	{"Esperanto",8500},
	{"Taxi",3000},
	{"Washington",40000},
	{"Bobcat",27500},
	{"Mr Whoopee",14000},
	{"BF Injection",30000},
	{"Hunter",1000000},
	{"Premier",45000},
	{"Enforcer",100000},
	{"Securicar",100000},
	{"Banshee",75000},
	{"Predator",500000},
	{"Bus",50000},
	{"Rhino",2000000},
	{"Barracks",50000},
	{"Hotknife",100000},
	{"Trailer 1",20000}, //artict1
	{"Previon",6500},
	{"Coach",50000},
	{"Cabbie",25000},
	{"Stallion",18000},
	{"Rumpo",5000},
	{"RC Bandit",1000},
	{"Romero",30000},
	{"Packer",75000},
	{"Monster",100000},
	{"Admiral",30000},
	{"Squalo",140000},
	{"Seasparrow",1000000},
	{"Pizzaboy",500},
	{"Tram",1000000},
	{"Trailer 2",20000}, //artict2
	{"Turismo",105000},
	{"Speeder",150000},
	{"Reefer",50000},
	{"Tropic",100000},
	{"Flatbed",40000},
	{"Yankee",35000},
	{"Caddy",7000},
	{"Solair",35000},
	{"Berkley's RC Van",7000},
	{"Skimmer",150000},
	{"PCJ-600",10000},
	{"Faggio",1500},
	{"Freeway",12000},
	{"RC Baron",5000},
	{"RC Raider",5000},
	{"Glendale",8000},
	{"Oceanic",10000},
	{"Sanchez",10000},
	{"Sparrow",1000000},
	{"Patriot",50000},
	{"Quad",8000},
	{"Coastguard",4500},
	{"Dinghy",30000},
	{"Hermes",15000},
	{"Sabre",27000},
	{"Rustler",1000000},
	{"ZR-350",80000},
	{"Walton",5000},
	{"Regina",20000},
	{"Comet",60000},
	{"BMX",500},
	{"Burrito",10000},
	{"Camper",6500},
	{"Marquis",50000},
	{"Baggage",15000},
	{"Dozer",100000},
	{"Maverick",200000},
	{"News Chopper",185000},
	{"Rancher",30000},
	{"FBI Rancher",30000},
	{"Virgo",13500},
	{"Greenwood",20000},
	{"Jetmax",170000},
	{"Hotring",20000},
	{"Sandking",105000},
	{"Blista Compact",24000},
	{"Police Maverick",200000},
	{"Boxville",12500},
	{"Benson",8000},
	{"Mesa",30000},
	{"RC Goblin",5000},
	{"Hotring Racer A",100000}, //hotrina
	{"Hotring Racer B",100000}, //hotrinb
	{"Bloodring Banger",100000},
	{"Rancher",30000},
	{"Super GT",80000},
	{"Elegant",35000},
	{"Journey",80000},
	{"Bike",300},
	{"Mountain Bike",700},
	{"Beagle",1000000},
	{"Cropdust",1000000},
	{"Stunt",1000000},
	{"Tanker",50000}, //petro
	{"Roadtrain",50000},
	{"Nebula",17000},
	{"Majestic",15500},
	{"Buccaneer",22000},
	{"Shamal",2000000},
	{"Hydra",2000000},
	{"FCR-900",30000},
	{"NRG-500",50000},
	{"HPV1000",1000000},
	{"Cement Truck",50000},
	{"Tow Truck",1000000},
	{"Fortune",30000},
	{"Cadrona",32000},
	{"FBI Truck",30000},
	{"Willard",100000},
	{"Forklift",25000},
	{"Tractor",10000},
	{"Combine",20000},
	{"Feltzer",55000},
	{"Remington",27000},
	{"Slamvan",30000},
	{"Blade",25000},
	{"Freight",100000},
	{"Streak",100000},
	{"Vortex",100000},
	{"Vincent",31000},
	{"Bullet",100000},
	{"Clover",6000},
	{"Sadler",7000},
	{"Firetruck LA",35000}, //firela
	{"Hustler",70000},
	{"Intruder",28000},
	{"Primo",26000},
	{"Cargobob",100000},
	{"Tampa",18000},
	{"Sunrise",29500},
	{"Merit",31000},
	{"Utility",100000},
	{"Nevada",100000},
	{"Yosemite",37000},
	{"Windsor",40000},
	{"Monster A",150000}, //monstera
	{"Monster B",150000}, //monsterb
	{"Uranus",50000},
	{"Jester",55000},
	{"Sultan",57000},
	{"Stratum",50000},
	{"Elegy",70000},
	{"Raindance",100000},
	{"RC Tiger",100000},
	{"Flash",49000},
	{"Tahoma",28000},
	{"Savanna",24000},
	{"Bandito",100000},
	{"Freight Flat",100000}, //freiflat
	{"Streak Carriage",100000}, //streakc
	{"Kart",100000},
	{"Mower",100000},
	{"Duneride",100000},
	{"Sweeper",100000},
	{"Broadway",22000},
	{"Tornado",21000},
	{"AT-400",100000},
	{"DFT-30",40000},
	{"Huntley",50000},
	{"Stafford",55000},
	{"BF-400",12000},
	{"Newsvan",30000},
	{"Tug",100000},
	{"Trailer 3",100000}, //petrotr
	{"Emperor",27000},
	{"Wayfarer",18000},
	{"Euros",65000},
	{"Hotdog",29000},
	{"Club",45000},
	{"Freight Carriage",100000}, //freibox
	{"Trailer 3",100000}, //artict3
	{"Andromada",100000},
	{"Dodo",100000},
	{"RC Cam",100000},
	{"Launch",100000},
	{"Police Car (LSPD)",100000},
	{"Police Car (SFPD)",100000},
	{"Police Car (LVPD)",100000},
	{"Police Ranger",100000},
	{"Picador",17500},
	{"S.W.A.T. Van",100000},
	{"Alpha",75000},
	{"Phoenix",4800},
	{"Glendale",100000},
	{"Sadler",100000},
	{"Luggage Trailer A",100000}, //bagboxa
	{"Luggage Trailer B",100000}, //bagboxb
	{"Stair Trailer",100000}, //tugstair
	{"Boxville",100000},
	{"Farm Plow",100000}, //farmtr1
	{"Utility Trailer",100000} //utiltr1
};

//------------------------------------

main()
{
    print("\n----------------------------------");
	print(" Vehicles.inc has been included");
	print("----------------------------------\n");

#if    defined    main_vehicles
    main_vehicles();
#endif
    return 1;
}

#if    defined    _ALS_main
    #undef    main
#else
    #define    _ALS_main
#endif
#define    main    main_vehicles
#if    defined    main_vehicles
main_vehicles();
#endif

//------------------------------------

public OnGameModeInit()
{
    CreateVehicle(520, -2006.9498,139.4659,27.5391,56.8183, 0, 1, 300);
    CreateVehicle(562, 1733.4902,-1945.5057,13.5627,89.7020, 0, 1, 300);
    //����
    CreateVehicle(497, 1548.6921,-1609.7402,13.0418,269.7786, 0, 1, 300);
    CreateVehicle(601, 1526.5408,-1645.0892,5.5492,179.9826, 0, 1, 300);
    CreateVehicle(427, 1529.2847,-1688.2317,5.5494,269.9951, 0, 1, 300);
    CreateVehicle(427, 1529.2957,-1683.6537,5.5494,270.6222, 0, 1, 300);
    CreateVehicle(596, 1545.4128,-1651.1219,5.5500,90.2143, 0, 1, 300);
    CreateVehicle(596, 1544.5812,-1658.9806,5.5503,90.8224, 0, 1, 300);
    CreateVehicle(596, 1558.9824,-1711.5728,5.5495,358.9444, 0, 1, 300);
    CreateVehicle(596, 1578.6608,-1711.2073,5.5494,179.4566, 0, 1, 300);
    CreateVehicle(596, 1601.9247,-1704.5219,5.5499,91.3003, 0, 1, 300);
    CreateVehicle(596, 1602.0278,-1692.2095,5.5495,269.3591, 0, 1, 300);
    CreateVehicle(596, 1535.3322,-1678.1329,13.0417,327.8306, 0, 1, 300);
    CreateVehicle(596, 1535.3153,-1667.2216,13.0422,330.5543, 0, 1, 300);
    
    new g_Object[5];
	new g_Vehicle[1];
	g_Object[0] = CreateObject(1001, 1713.2460, -1944.0019, 14.0696, -1.2999, -0.1000, 93.4999); //spl_b_bab_m
	g_Object[1] = CreateObject(1140, 1689.4443, -1834.2148, 13.4954, 0.0000, 0.0000, 5.2000); //rbmp_c_s
	SetObjectMaterial(g_Object[1], 0, 14668, "711c", "forumstand1_LAe", 0xFF86446E);
	SetObjectMaterial(g_Object[1], 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF86446E);
	g_Object[2] = CreateObject(19086, 1685.9615, -1829.3847, 11.3674, 0.0000, 0.0000, 0.0000); //ChainsawDildo1
	g_Object[3] = CreateObject(1153, 1690.2669, -1830.4359, 11.8309, 0.0000, 0.0000, 0.0000); //fbmp_a_f
	SetObjectMaterial(g_Object[3], 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF86446E);
	g_Object[4] = CreateObject(1425, 1709.1494, -1880.4896, 12.3510, 0.0000, 0.0000, 0.0000); //DYN_ROADBARRIER_3
	SetObjectMaterial(g_Object[4], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0xFF86446E);
	SetObjectMaterial(g_Object[4], 1, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0xFF86446E);
	SetObjectMaterial(g_Object[4], 2, 10101, "2notherbuildsfe", "Bow_church_grass_alt", 0xFF86446E);
	SetObjectMaterial(g_Object[4], 3, 10101, "2notherbuildsfe", "gz_vicdoor1", 0xFF86446E);
	AddVehicleComponent(g_Vehicle[0], 1087);
	g_Vehicle[0] = CreateVehicle(478, 1720.7080, -1861.3923, 13.5633, 359.4626, 146, 27, -1); //Walton
	AttachObjectToVehicle(g_Object[0], g_Vehicle[0], 0.0000, -2.5999, 0.5000, 0.0000, 0.0000, 0.0000);
	AttachObjectToVehicle(g_Object[1], g_Vehicle[0], -1.1000, -2.0000, -0.2000, 0.0000, 0.0000, 0.0000);
	AttachObjectToVehicle(g_Object[2], g_Vehicle[0], 0.0000, 2.0999, 0.5000, 0.0000, 0.0000, 90.0000);
	AttachObjectToVehicle(g_Object[3], g_Vehicle[0], 0.9499, 1.7999, -0.3000, 0.0000, 0.0000, 0.0000);
	AttachObjectToVehicle(g_Object[4], g_Vehicle[0], 0.0000, 2.5999, -0.5000, -90.0000, 180.0000, 180.0000);
    
    ManualVehicleEngineAndLights();
    EnableStuntBonusForAll(0);
    format(strIOText,sizeof(strIOText), "Vehicles %d has been loaded", 2);
	print(strIOText);
#if    defined    OnGameModeInit_vehicles
    OnGameModeInit_vehicles();
#endif
	return 1;
}

#if    defined    _ALS_OnGameModeInit
    #undef    OnGameModeInit
#else
    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit    OnGameModeInit_vehicles
#if    defined    OnGameModeInit_vehicles
forward OnGameModeInit_vehicles();
#endif

//------------------------------------

public OnVehicleMod(playerid, vehicleid, componentid)
{
    RemoveVehicleComponent(vehicleid,componentid);
#if    defined    OnVehicleMod_vehicles
    OnVehicleMod_vehicles(playerid, vehicleid, componentid);
#endif
	return 1;
}

#if    defined    _ALS_OnVehicleMod
    #undef    OnVehicleMod
#else
    #define    _ALS_OnVehicleMod
#endif
#define    OnVehicleMod    OnVehicleMod_vehicles
#if    defined    OnVehicleMod_vehicles
forward OnVehicleMod_vehicles(playerid, vehicleid, componentid);
#endif

//------------------------------------

public OnPlayerUpdate(playerid)
{
    if(IsPlayerInAnyVehicle(playerid))
	{
	    new Float:vhealth;
	    GetVehicleHealth(GetPlayerVehicleID(playerid), vhealth);
	    if(vhealth < 650)
		{
		    new engine, lights, alarm, doors, bonnet, boot, objective;
	    	GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
	    	SetVehicleParamsEx(GetPlayerVehicleID(playerid), false, lights, alarm, doors, bonnet, boot, objective);
		}
	}
#if    defined    OnPlayerUpdate_vehicles
    OnPlayerUpdate_vehicles(playerid);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerUpdate
    #undef    OnPlayerUpdate
#else
    #define    _ALS_OnPlayerUpdate
#endif
#define    OnPlayerUpdate    OnPlayerUpdate_vehicles
#if    defined    OnPlayerUpdate_vehicles
forward OnPlayerUpdate_vehicles(playerid);
#endif
//------------------------------------

CMD:gps(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessageEx(playerid, CLR_ERROR,"�x�: {"#cOLOR_WHITE"}��� ������� �������� ������ � ����������");
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"");
	for(new i = 0; i < sizeof(NAVInfo);i++)
	{
	    format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s%i. %s\n", strTextPlayerDialog,i+1, NAVInfo[i][gpsName]);
	}
	Dialog_Show(playerid, Gps, DIALOG_STYLE_LIST, "{"#COLOR_DIALOG_HEAD"}���������", strTextPlayerDialog, "{"#COLOR_SUCCESS"}�����", "{"#COLOR_ERROR"}�����");
	return 1;
}

Dialog:Gps(playerid, response, listitem, inputtext[])
{
    if (response)
    {
		SetPlayerCheckpoint(playerid, NAVInfo[listitem][gpsX],NAVInfo[listitem][gpsY],NAVInfo[listitem][gpsZ], 3.0);
    }
    else
    {

    }
    return 1;
}

CMD:trail(playerid, params[])
{
	new veh1,veh2;
    if(sscanf(params,"ii",veh1,veh2)) return SendClientMessageEx(playerid, CLR_NOTE,"�i�: {"#cOLOR_WHITE"}����������� {"#COLOR_NOTE"}/trail [id �/� �1] [id �/� �2]");
    if(IsTrailerAttachedToVehicle(veh1) || IsTrailerAttachedToVehicle(veh2))
    {
        DetachTrailerFromVehicle(veh1);
        DetachTrailerFromVehicle(veh2);
    }
	AttachTrailerToVehicle(veh1,veh2);
	return 1;
}
CMD:vlock(playerid)
{
	new Float: x, Float: y, Float: z;
	for(new i = 0; i < MAX_VEHICLES; i++)
	{
	    GetVehiclePos(i, x, y, z);
	    if(!PlayerToPoint(4.0, playerid, x , y, z)) continue;
	    new engine, lights, alarm, doors, bonnet, boot, objective,vehid;
	    GetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, objective);
	    if(doors == 0)
	    {
	        doors = 1;
	        SendClientMessageEx(playerid, CLR_SUCCESS,"�v�: {"#cOLOR_WHITE"}����� �������. ����� ������� �� ����� ������� {"#COLOR_NOTE"}/vlock");
	    }
	    else
	    {
	        doors = 0;
	        SendClientMessageEx(playerid, CLR_SUCCESS,"�v�: {"#cOLOR_WHITE"}����� �������. ����� ������� �� ����� ������� {"#COLOR_NOTE"}/vlock");
	    }
	    SetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);
	    break;
	}
	return 1;
}

CMD:valarm(playerid)
{
	new Float: x, Float: y, Float: z;
	for(new i = 0; i < MAX_VEHICLES; i++)
	{
	    GetVehiclePos(i, x, y, z);
	    if(!PlayerToPoint(4.0, playerid, x , y, z)) continue;
	    new engine, lights, alarm, doors, bonnet, boot, objective,vehid;
	    GetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, objective);
	    if(alarm == 0)
	    {
	        alarm = 1;
	        SendClientMessageEx(playerid, CLR_SUCCESS,"�v�: {"#cOLOR_WHITE"}������������ ��������. ����� ��������� � ����� ������� {"#COLOR_NOTE"}/valarm");
	    }
	    else
	    {
	        alarm = 0;
         	SendClientMessageEx(playerid, CLR_SUCCESS,"�v�: {"#cOLOR_WHITE"}������������ ���������. ����� �������� � ����� ������� {"#COLOR_NOTE"}/valarm");
	    }
	    SetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);
	    break;
	}
	return 1;
}

CMD:vboot(playerid)
{
	new Float: x, Float: y, Float: z;
	for(new i = 0; i < MAX_VEHICLES; i++)
	{
	    GetVehiclePos(i, x, y, z);
	    if(!PlayerToPoint(4.0, playerid, x , y, z)) continue;
	    new engine, lights, alarm, doors, bonnet, boot, objective,vehid;
	    GetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, objective);
	    if(boot == 0)
	    {
	        boot = 1;
	        SendClientMessageEx(playerid, CLR_SUCCESS,"�v�: {"#cOLOR_WHITE"}�������� ������. ����� ������� ��� ����� ������� {"#COLOR_NOTE"}/vboot");
	    }
	    else
	    {
	        boot = 0;
         	SendClientMessageEx(playerid, CLR_SUCCESS,"�v�: {"#cOLOR_WHITE"}�������� ������. ����� ������� ��� ����� ������� {"#COLOR_NOTE"}/vboot");
	    }
	    SetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);
	    break;
	}
	return 1;
}

CMD:vbonnet(playerid)
{
	new Float: x, Float: y, Float: z;
	for(new i = 0; i < MAX_VEHICLES; i++)
	{
	    GetVehiclePos(i, x, y, z);
	    if(!PlayerToPoint(4.0, playerid, x , y, z)) continue;
	    new engine, lights, alarm, doors, bonnet, boot, objective,vehid;
	    GetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, objective);
	    if(bonnet == 0)
	    {
	        bonnet = 1;
	        SendClientMessageEx(playerid, CLR_SUCCESS,"�v�: {"#cOLOR_WHITE"}����� �������. ����� ������� ��� ����� ������� {"#COLOR_NOTE"}/vbonnet");
	    }
	    else
	    {
	        bonnet = 0;
	        SendClientMessageEx(playerid, CLR_SUCCESS,"�v�: {"#cOLOR_WHITE"}����� ������. ����� ������� ��� ����� ������� {"#COLOR_NOTE"}/vbonnet");
	    }
	    SetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);
	    break;
	}
	return 1;
}

CMD:en(playerid)
{
    if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessageEx(playerid,COLOR_RED,"������: {"#cOLOR_WHITE"}��� ������� �������� ������ � ����������");
    new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine == 0)
	{
	    engine = 1;
	    SendClientMessageEx(playerid,COLOR_GREEN,"���������: {"#cOLOR_WHITE"}��������� �������. ����� ��������� ��������� ����� ������� {"#cOLOR_GRAY"}/en{"#cOLOR_WHITE"}, ��� ������� �� {"#cOLOR_RED"}2");
	}
	else
	{
	    engine = 0;
	    SendClientMessageEx(playerid,COLOR_GREEN,"���������: {"#cOLOR_WHITE"}��������� ��������. ����� ������� ��������� ����� ������� {"#cOLOR_GRAY"}/en{"#cOLOR_WHITE"}, ��� ������� �� {"#cOLOR_GREEN"}2");
	}
	SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
    return 1;
}

CMD:lights(playerid)
{
    if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessageEx(playerid,COLOR_RED,"������: {"#cOLOR_WHITE"}��� ������� �������� ������ � ����������");
    new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
	if(lights == 0)
	{
	    lights = 1;
	    SendClientMessageEx(playerid,COLOR_GREEN,"���������: {"#cOLOR_WHITE"}���� ��������. ����� ��������� �� ����� ������� {"#cOLOR_GRAY"}/en{"#cOLOR_WHITE"}, ��� ������� �� {"#cOLOR_RED"}ALT");
	}
	else
	{
	    lights = 0;
	    SendClientMessageEx(playerid,COLOR_GREEN,"���������: {"#cOLOR_WHITE"}���� ���������. ����� �������� �� ����� ������� {"#cOLOR_GRAY"}/en{"#cOLOR_WHITE"}, ��� ������� �� {"#cOLOR_GREEN"}ALT");
	}
	SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
    return 1;
}
