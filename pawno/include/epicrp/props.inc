// Нажми ctrl+h и замени все "props" на название инклюда
// Название должно быть уникальным
//Коммит через андроид

#define MAX_PROPS		   8

#define PLAYER_PROP_TYPE    0
#define GROUP_PROP_TYPE     1
#define STATE_PROP_TYPE     2

enum Prop
{
	ID,
	Float: x,
	Float: y,
	Float: z,
	interiorid,
	vw,
	interior,
	ownerid,
	ownertype,
	startprice,
	price,
	mapicon
};

new Props[MAX_PROPS][Prop];

main()
{
    print("\n----------------------------------");
	print(" Props.inc has been included");
	
	
	print("----------------------------------\n");

#if    defined    main_props
    main_props();
#endif
    return 1;
}
#if    defined    _ALS_main
    #undef    main
#else
    #define    _ALS_main
#endif
#define    main    main_props
#if    defined    main_props
main_props();
#endif


public OnGameModeInit()
{	mysql_query(MySQL, "SELECT * FROM `props`");
	for(new i = 0; i < cache_num_rows(); i++)
	{
	    Props[i][ID] = cache_get_field_content_int(i, "id", MySQL);
	    Props[i][x] = cache_get_field_content_float(i, "x", MySQL);
	    Props[i][y] = cache_get_field_content_float(i, "y", MySQL);
	    Props[i][z] = cache_get_field_content_float(i, "z", MySQL);
	    Props[i][interiorid] = cache_get_field_content_int(i, "interiorid", MySQL);
	    Props[i][vw] = cache_get_field_content_int(i, "vw", MySQL);
	    Props[i][interior] = cache_get_field_content_int(i, "interior", MySQL);
	    Props[i][ownerid] = cache_get_field_content_int(i, "ownerid", MySQL);
	    Props[i][ownertype] = cache_get_field_content_int(i, "ownertype", MySQL); // 0 - игрок, 1 - группа, 2 - государственное епт
	    Props[i][startprice] = cache_get_field_content_int(i, "startprice", MySQL);
	    Props[i][price] = cache_get_field_content_int(i, "price", MySQL);
	    
	    switch(Props[i][ownertype])
	    {
	        case PLAYER_PROP_TYPE:
	        {
	            Props[i][mapicon] = CreateDynamicMapIcon(Props[i][x], Props[i][y], Props[i][z], 27, 0, Props[i][vw], Props[i][interior], -1, 250.0);
	        }
	        case GROUP_PROP_TYPE:
	        {
	            Props[i][mapicon] = CreateDynamicMapIcon(Props[i][x], Props[i][y], Props[i][z], 27, 0, Props[i][vw], Props[i][interior], -1, 250.0);
	        }
	        case STATE_PROP_TYPE:
	        {
	            Props[i][mapicon] = CreateDynamicMapIcon(Props[i][x], Props[i][y], Props[i][z], 27, 0, Props[i][vw], Props[i][interior], -1, 250.0);
	        }
		}
	}
#if    defined    OnGameModeInit_props
    OnGameModeInit_props();
#endif
	return 1;
}
#if    defined    _ALS_OnGameModeInit
    #undef    OnGameModeInit
#else
    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit    OnGameModeInit_props
#if    defined    OnGameModeInit_props
forward OnGameModeInit_props();
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys==KEY_WALK)
	{
		for(new i = 0; i < MAX_PROPS; i++)
		{
			if(!PlayerToPoint(2.0,playerid,Props[i][x],Props[i][y],Props[i][z])) continue;
			SetPlayerPos(playerid, Interiors[Props[i][interiorid]][x], Interiors[Props[i][interiorid]][y], Interiors[Props[i][interiorid]][z]);
			SetPlayerVirtualWorld(playerid, i);
			SetPlayerInterior(playerid, Interiors[Props[i][interiorid]][interior]);
		}
	}
#if    defined    OnPlayerKeyStateChange_props
    OnPlayerKeyStateChange_props(playerid, newkeys, oldkeys);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerKeyStateChange
    #undef    OnPlayerKeyStateChange
#else
    #define    _ALS_OnPlayerKeyStateChange
#endif
#define    OnPlayerKeyStateChange    OnPlayerKeyStateChange_props
#if    defined    OnPlayerKeyStateChange_props
forward OnPlayerKeyStateChange_props(playerid, newkeys, oldkeys);
#endif
