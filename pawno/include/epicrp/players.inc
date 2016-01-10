#define IsValidRpName(%1) \
regex_match(%1, "([A-Z]{1,1})[a-z]{2,9}+_([A-Z]{1,1})[a-z]{2,9}")
#define IsValidEmail(%1) \
	regex_match(%1, "[a-zA-Z0-9_\\.]+@([a-zA-Z0-9\\-]+\\.)+[a-zA-Z]{2,4}")

//------------------------------------

enum pInfo
{
	pID,
	pName[MAX_PLAYER_NAME],
	pPass[32],
	pEMail[64],
	pBanned,
	pMuted,
	pKicks,
	pBans,
	pMutes,
	pWarns,
	pSex,
	pExp,
	pLvl,
	//Не сохраняемые
	pLogged,
	pKick,
	pWrongPassEnter
};

new PlayerInfo[MAX_PLAYERS][pInfo];

#define MAX_PERMISSIONS 27
enum perInfo
{
	perName[60],
	perDesc[128]
};

new permissionInfo[MAX_PERMISSIONS][perInfo] =
{
	{"Управлять разрешениями", "/setperm"},
	{"Удалять аккаунты", "Недоступно"},//1
	{"Изменять аккаунты", "Недоступно"},
	{"Блокировать аккаунты", "/ban"},
	{"Блокировать чат", "/mute"},
	{"Выкидывать с сервера", "/kick"},//5
	{"Выдавать предупреждения", "/warn"},
	{"Удалять персонажей", "Недоступно"},
	{"Изменять персонажей", "Недоступно"},
	{"Управлять инвентарем", "Недоступно"},
	{"Удалять фракции", "/delfaction"},//10
	{"Создавать фракции", "/createfaction"},
	{"Изменять фракции", "/setfactionname"},
	{"Управлять фракциями", "/setleader"},
	{"Удалять недвижимость", "/delhouse"},
	{"Создавать недвижимость", "/createhouse"},//15
	{"Изменять недвижимость", "/hname, /hdesc"},
	{"Управлять недвижимостью", "/lock"},
	{"Удалять транспорт", "Недоступно"},
	{"Создавать транспорт", "Недоступно"},
	{"Изменять транспорт", "Недоступно"},//20
	{"Управлять транспортом", "Недоступно"},
	{"Разблокировать аккаунты", "/unban"},
	{"Выдавать временный скин", "/setskin"},
	{"Телепортироваться к игрокам", "/teleport"},
	{"Просматривать интерьеры", "/showint"},//25
	{"Перезапускать сервер", "/restart"}
};
//------------------------------------
main()
{
    print("\n----------------------------------");
	print(" Players.inc has been included");
	print("----------------------------------\n");

#if    defined    main_players
    main_players();
#endif
    return 1;
}

#if    defined    _ALS_main
    #undef    main
#else
    #define    _ALS_main
#endif
#define    main    main_players
#if    defined    main_players
main_players();
#endif

//------------------------------------

public OnPlayerConnect(playerid)
{
	{
		new name_players[MAX_PLAYER_NAME];
	    GetPlayerName(playerid, name_players, sizeof(name_players));
		if(!IsValidRpName(name_players))
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Имя должно иметь формать Firstname_Secondname");
		}
		if(select)
		{
		    Dialog_Show(playerid, Log, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Авторизация: Введите пароль", "{"#cOLOR_GRAY"}Введите пароль от вашего игрового аккаунта:", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
		}
		else
		{
		    Dialog_Show(playerid, RegPassEnter, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Регистрация: Ввод пароля", "{"#cOLOR_GRAY"}Придумайте сложный пароль для своего аккаунта.\nНикому {"#cOLOR_AQUA"}не говорите{"#cOLOR_GRAY"}его!", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
		}
	}
    DC_CMD(playerid, "/cc");
#if    defined    OnPlayerConnect_players
    OnPlayerConnect_players(playerid);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerConnect
    #undef    OnPlayerConnect
#else
    #define    _ALS_OnPlayerConnect
#endif
#define    OnPlayerConnect    OnPlayerConnect_players
#if    defined    OnPlayerConnect_players
forward OnPlayerConnect_players(playerid);
#endif

//------------------------------------

Dialog:Log(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if(strlen(inputtext))
        {
            if(select)
            {
                PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
                SpawnPlayer(playerid);
            }
            else
            {
                PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
                Dialog_Show(playerid, Log, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Авторизация: Введите {"#cOLOR_RED"}верный {"#cOLOR_ORANGE"}пароль!", "{"#cOLOR_GRAY"}Введите пароль от вашего игрового аккаунта:", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
            }
			
        }
        else
        {
            PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
            Dialog_Show(playerid, Log, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Авторизация: Введите пароль", "{"#cOLOR_GRAY"}Введите пароль от вашего игрового аккаунта:", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
        }
        
    }
    else
    {
    
    }
    return 1;
}

Dialog:RegPassEnter(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if(strlen(inputtext))
        {
            PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
            Dialog_Show(playerid, RegEMailEnter, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Регистрация: Ввод EMail", "{"#cOLOR_GRAY"}Введите свой точный адрес электронной почты.\nНапример: {"#cOLOR_AQUA"}ch3rkasov@gmail.com{"#cOLOR_GRAY"}\nБез него не получится восстановить доступ к аккаунту в случае утери пароля:", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
        }
        else
        {
            PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
            Dialog_Show(playerid, RegPassEnter, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Регистрация: Ввод пароля", "{"#cOLOR_GRAY"}Придумайте сложный пароль для своего аккаунта.\nНикому {"#cOLOR_AQUA"}не говорите{"#cOLOR_GRAY"}его!", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
		}
	}
	else
    {
        PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
        Kick(playerid);
    }
    return 1;
}

Dialog:RegEMailEnter(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if(strlen(inputtext))
        {
	        if(IsValidEmail(inputtext))
	        {
                PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
	            Dialog_Show(playerid, RegEMailVerification, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Регистрация: Подтверждение EMail", "{"#cOLOR_GRAY"}На ваш почтовый адрес был отправлен код подтверждения регистрации:", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
	        }
	        else
	        {
	            PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	            Dialog_Show(playerid, RegEMailEnter, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Регистрация: Ввод EMail", "{"#cOLOR_GRAY"}Введите свой точный адрес электронной почты.\nНапример: {"#cOLOR_AQUA"}ch3rkasov@gmail.com{"#cOLOR_GRAY"}\nБез него не получится восстановить доступ к аккаунту в случае утери пароля:", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
	        }
        }
        else
        {
            PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
            Dialog_Show(playerid, RegEMailEnter, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Регистрация: Ввод EMail", "{"#cOLOR_GRAY"}Введите свой точный адрес электронной почты.\nНапример: {"#cOLOR_AQUA"}ch3rkasov@gmail.com{"#cOLOR_GRAY"}\nБез него не получится восстановить доступ к аккаунту в случае утери пароля:", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
        }
    }
    else
    {
        PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
        Kick(playerid);
    }
    return 1;
}

Dialog:RegEMailVerification(playerid, response, listitem, inputtext[])
{
    if (response)
    {
		if(strlen(inputtext))
		{
			PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
		    Dialog_Show(playerid, RegSexSelect, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Регистрация: Выбор пола персонажа", "{"#cOLOR_GRAY"}Выберите пол вашего персонажа", "{"#cOLOR_GREEN"}Мужской", "{"#cOLOR_RED"}Женский");
		}
		else
		{
		    PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
		    Dialog_Show(playerid, RegEMailVerification, DIALOG_STYLE_LIST, "{"#cOLOR_ORANGE"}Регистрация: Подтверждение EMail", "{"#cOLOR_GRAY"}На ваш почтовый адрес был отправлен код подтверждения регистрации:", "{"#cOLOR_GREEN"}Ввод", "{"#cOLOR_RED"}Выход");
		}
    }
    else
    {
        PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
        Kick(playerid);
    }
    return 1;
}

Dialog:RegSexSelect(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        PlayerInfo[playerid][pSex] = 0;
    }
    else
    {
        PlayerInfo[playerid][pSex] = 1;
    }
    PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
    SpawnPlayer(playerid);
    return 1;
}

//------------------------------------

public OnPlayerSpawn(playerid)
{
    DC_CMD(playerid, "/cc");
#if    defined    OnPlayerSpawn_players
    OnPlayerSpawn_players(playerid);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerSpawn
    #undef    OnPlayerSpawn
#else
    #define    _ALS_OnPlayerSpawn
#endif
#define    OnPlayerSpawn    OnPlayerSpawn_players
#if    defined    OnPlayerSpawn_players
forward OnPlayerSpawn_players(playerid);
#endif

//------------------------------------

public OnPlayerDisconnect(playerid, reason)
{
	printf("Player has been disconnected");
#if    defined    OnPlayerDisconnect_players
    OnPlayerDisconnect_players(playerid, reason);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerDisconnect
    #undef    OnPlayerDisconnect
#else
    #define    _ALS_OnPlayerDisconnect
#endif
#define    OnPlayerDisconnect    OnPlayerDisconnect_players
#if    defined    OnPlayerDisconnect_players
forward OnPlayerDisconnect_players(playerid, reason);
#endif

//------------------------------------

public OnGameModeInit()
{
    PlayersPayDay();
    AddPlayerClass( 0, -1976.0231,137.8876,27.6875, 0.0, 0, 0, 0, 0, 0, 0);
	SetNameTagDrawDistance(5);
	LimitGlobalChatRadius(20);
	ShowPlayerMarkers(0);
#if    defined    OnGameModeInit_players
    OnGameModeInit_players();
#endif
	return 1;
}

#if    defined    _ALS_OnGameModeInit
    #undef    OnGameModeInit
#else
    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit    OnGameModeInit_players
#if    defined    OnGameModeInit_players
forward OnGameModeInit_players();
#endif

//------------------------------------

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
#if    defined    OnPlayerRequestClass_players
    OnPlayerRequestClass_players(playerid, classid);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerRequestClass
    #undef    OnPlayerRequestClass
#else
    #define    _ALS_OnPlayerRequestClass
#endif
#define    OnPlayerRequestClass    OnPlayerRequestClass_players
#if    defined    OnPlayerRequestClass_players
forward OnPlayerRequestClass_players(playerid, classid);
#endif

//------------------------------------
new PlayersPayDayTimer;

forward PlayersPayDay();

public PlayersPayDay()
{
    foreach(Player, i)
	{
	    PlayerPlaySound(i, S_MISSIONCOMPLETE, 0.0, 0.0, 10.0);
	}
	new hour,minute,second;
	gettime(hour,minute,second);
	SetWorldTime(hour);
	SetWeather(random(5));

	KillTimer(PlayersPayDayTimer);
	PlayersPayDayTimer = SetTimer("payDay", 3600000-minute*59*1000, 1);
	printf("PayDay через: ", 3600000-minute*60*1000);
	return 1;
}
//------------------------------------
stock SendClientMessageEx(playerid, color, text[])
{
	if(strlen(text) > 128)
	{
		new text2[128];
		strmid(text2,text,65,strlen(text),strlen(text));
		strdel(text, 65, strlen(text));
		format(text, 128,"%s ...", text);
		format(text2, 128, "... %s", text2);
	    SendClientMessage(playerid, color, text);
   	    SendClientMessage(playerid, color, text2);
	}
	else
	{
	    SendClientMessage(playerid, color, text);
	}
	return 1;
}

#define SendClientMessage SendClientMessageEx

//------------------------------------

stock ProxDetectorNew(playerid,Float:Radi=10.0,color,text[])
{
    new Float:pos[3];
    GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
    foreach(Player, i)
    {
    	if(IsPlayerInRangeOfPoint(i,Radi,pos[0],pos[1],pos[2]))
     	{
			if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid) && GetPlayerInterior(playerid) == GetPlayerInterior(i)) SendClientMessageEx(i,color,text);
		}
    }
}

//------------------------------------

public OnPlayerText(playerid, text[])
{
	{
	new text_players[256];
	new name_players[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name_players, sizeof(name_players));
	format(text_players, sizeof(text_players), "%s: %s", name_players, text);
	ProxDetectorNew(playerid,20.0, COLOR_WHITE, text_players);
	}
#if    defined    OnPlayerText_players
    OnPlayerText_players(playerid, text);
#endif
	return 0;
}

#if    defined    _ALS_OnPlayerText
    #undef    OnPlayerText
#else
    #define    _ALS_OnPlayerText
#endif
#define    OnPlayerText    OnPlayerText_players
#if    defined    OnPlayerText_players
forward OnPlayerText_players(playerid, text[]);
#endif

//------------------------------------

CMD:b(playerid,params[])
{
    if(sscanf(params,"s[128]",params)) return SendClientMessageEx(playerid,COLOR_YELLOW,"Подсказка: {"#cOLOR_WHITE"}Используйте {"#cOLOR_GRAY"}/b [сообщение]");
    new name_players[MAX_PLAYER_NAME], text_players[256];
    GetPlayerName(playerid, name_players, sizeof(name_players));
	format(text_players, sizeof(text_players), "(( %s: %s ))", name_players,params);
	ProxDetectorNew(playerid,5.0,COLOR_GRAY,text_players);
	return 1;
}

CMD:try(playerid,params[])
{
    if(sscanf(params,"s[128]",params)) return SendClientMessageEx(playerid,COLOR_YELLOW,"Подсказка: {"#cOLOR_WHITE"}Используйте {"#cOLOR_GRAY"}/try [сообщение]");
    new name_players[MAX_PLAYER_NAME], text_players[256];
    GetPlayerName(playerid, name_players, sizeof(name_players));
	format(text_players,sizeof(text_players),"%s %s {"#cOLOR_GRAY"}(( %s ))",name_players,params[0],random(2) == 1 ? ("Удачно") : ("Неудачно"));
	ProxDetectorNew(playerid,5.0,COLOR_PINK,text_players);
	return 1;
}

CMD:do(playerid,params[])
{
    if(sscanf(params,"s[128]",params)) return SendClientMessageEx(playerid,COLOR_YELLOW,"Подсказка: {"#cOLOR_WHITE"}Используйте {"#cOLOR_GRAY"}/do [сообщение]");
    new name_players[MAX_PLAYER_NAME], text_players[256];
    GetPlayerName(playerid, name_players, sizeof(name_players));
	format(text_players, sizeof(text_players), "%s {"#cOLOR_GRAY"}(( %s ))",params,name_players);
	ProxDetectorNew(playerid,5.0, COLOR_PINK,text_players);
	return 1;
}

CMD:low(playerid,params[])
{
    if(sscanf(params,"s[128]",params)) return SendClientMessageEx(playerid,COLOR_YELLOW,"Подсказка: {"#cOLOR_WHITE"}Используйте {"#cOLOR_GRAY"}/low [сообщение]");
    new name_players[MAX_PLAYER_NAME], text_players[256];
    GetPlayerName(playerid, name_players, sizeof(name_players));
	format(text_players, sizeof(text_players), "%s тихо произнес: %s", name_players,params);
	ProxDetectorNew(playerid,2.0,COLOR_WHITE,text_players);
	return 1;
}

CMD:s(playerid,params[])
{
    if(sscanf(params,"s[128]",params)) return SendClientMessageEx(playerid,COLOR_YELLOW,"Подсказка: {"#cOLOR_WHITE"}Используйте {"#cOLOR_GRAY"}/s [сообщение]");
    new name_players[MAX_PLAYER_NAME], text_players[256];
    GetPlayerName(playerid, name_players, sizeof(name_players));
	format(text_players, sizeof(text_players), "%s крикнул: %s", name_players,params);
	ProxDetectorNew(playerid,50.0,COLOR_WHITE,text_players);
	ApplyAnimationEx(playerid,"ON_LOOKERS","shout_01",4.1,0,0,0,0,0,0);
	return 1;
}

CMD:me(playerid,params[])
{
    if(sscanf(params,"s[128]",params)) return SendClientMessageEx(playerid,COLOR_YELLOW,"Подсказка: {"#cOLOR_WHITE"}Используйте {"#cOLOR_GRAY"}/me [сообщение]");
    new name_players[MAX_PLAYER_NAME], text_players[256];
    GetPlayerName(playerid, name_players, sizeof(name_players));
	format(text_players, sizeof(text_players), "%s %s", name_players,params);
	ProxDetectorNew(playerid,5.0,COLOR_PINK,text_players);
	return 1;
}

//------------------------------------

forward PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
public PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) &&
		((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
	}
	return 0;
}

//------------------------------------

CMD:cc(playerid)
{
    for(new i=0; i<20; i++) SendClientMessageEx(playerid,COLOR_WHITE," ");
    return 1;
}

//------------------------------------

stock ApplyAnimationEx(playerid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync)
{
    ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
    ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
    ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
    return 1;
}

CMD:rap(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
	    case 1: ApplyAnimationEx(playerid,"RAPPING","Laugh_01",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimationEx(playerid,"RAPPING","RAP_A_Loop",4.1,1,1,1,1,1,1);
	    case 3: ApplyAnimationEx(playerid,"RAPPING","RAP_A_OUT",4.1,1,1,1,1,1,1);
	    case 4: ApplyAnimationEx(playerid,"RAPPING","RAP_B_IN",4.1,1,1,1,1,1,1);
	    case 5: ApplyAnimationEx(playerid,"RAPPING","RAP_B_Loop",4.1,1,1,1,1,1,1);
	    case 6: ApplyAnimationEx(playerid,"RAPPING","RAP_B_OUT",4.1,1,1,1,1,1,1);
	    case 7: ApplyAnimationEx(playerid,"RAPPING","RAP_C_Loop",4.1,1,1,1,1,1,1);
	    default: GameTextForPlayer(playerid,"~r~~k~/rap ~w~[1-7]",2000,6);
	}
	return 1;
}
CMD:smoke(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SMOKING", "F_smklean_loop",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid, "SMOKING", "M_smklean_loop",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid, "SMOKING", "M_smkstnd_loop",4.1,1,1,1,1,1,1);
		case 4: ApplyAnimationEx(playerid, "SMOKING", "M_smk_drag",4.1,1,1,1,1,1,1);
		case 5: ApplyAnimationEx(playerid, "SMOKING", "M_smk_in",4.1,1,1,1,1,1,1);
		case 6: ApplyAnimationEx(playerid, "SMOKING", "M_smk_loop",4.1,1,1,1,1,1,1);
		case 7: ApplyAnimationEx(playerid, "SMOKING", "M_smk_out",4.1,1,1,1,1,1,1);
		case 8: ApplyAnimationEx(playerid, "SMOKING", "M_smk_tap",4.1,1,1,1,1,1,1);
		default: GameTextForPlayer(playerid,"~r~~k~/smoke ~w~[1-8]",2000,6);
	}
	return 1;
}

CMD:crack(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CRACK", "Bbalbat_Idle_01",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid, "CRACK", "Bbalbat_Idle_02",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid, "CRACK", "crckdeth1",4.1,1,1,1,1,1,1);
		case 4: ApplyAnimationEx(playerid, "CRACK", "crckdeth2",4.1,1,1,1,1,1,1);
		case 5: ApplyAnimationEx(playerid, "CRACK", "crckdeth3",4.1,1,1,1,1,1,1);
		case 6: ApplyAnimationEx(playerid, "CRACK", "crckdeth4",4.1,1,1,1,1,1,1);
		case 7: ApplyAnimationEx(playerid, "CRACK", "crckidle1",4.1,1,1,1,1,1,1);
		case 8: ApplyAnimationEx(playerid, "CRACK", "crckidle2",4.1,1,1,1,1,1,1);
		case 9: ApplyAnimationEx(playerid, "CRACK", "crckidle3",4.1,1,1,1,1,1,1);
		case 10: ApplyAnimationEx(playerid, "CRACK", "crckidle4",4.1,1,1,1,1,1,1);
		default: GameTextForPlayer(playerid,"~r~~k~/crack ~w~[1-10]",2000,6);
	}
	return 1;
}

CMD:walk(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
    switch(animid)
	{
	    case 1: ApplyAnimationEx(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimationEx(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1,1);
	    case 3: ApplyAnimationEx(playerid,"PED","WALK_old",4.1,1,1,1,1,1,1);
	    case 4: ApplyAnimationEx(playerid,"PED","WALK_player",4.1,1,1,1,1,1,1);
	    case 5: ApplyAnimationEx(playerid,"PED","WALK_shuffle",4.1,1,1,1,1,1,1);
	    case 6: ApplyAnimationEx(playerid,"PED","Walk_Wuzi",4.1,1,1,1,1,1,1);
	    case 7: ApplyAnimationEx(playerid,"PED","WALK_DRUNK",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/walk ~w~[1-7]",2000,6);
	}
	return 1;
}

CMD:ped(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"PED","BIKE_fallR",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"PED","BIKE_fall_off",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"PED","FLOOR_hit",4.1,1,1,1,1,1,1);
		case 4: ApplyAnimationEx(playerid,"PED","FLOOR_hit_f",4.1,1,1,1,1,1,1);
		case 5: ApplyAnimationEx(playerid,"PED","IDLE_taxi",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/ped ~w~[1-5]",2000,6);
	}
	return 1;
}

CMD:sign(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
    switch (animid)
	{
	    case 1: ApplyAnimationEx(playerid,"GHANDS","gsign1",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimationEx(playerid,"GHANDS","gsign2",4.1,1,1,1,1,1,1);
	    case 3: ApplyAnimationEx(playerid,"GHANDS","gsign3",4.1,1,1,1,1,1,1);
	    case 4: ApplyAnimationEx(playerid,"GHANDS","gsign4",4.1,1,1,1,1,1,1);
	    case 5: ApplyAnimationEx(playerid,"GHANDS","gsign5",4.1,1,1,1,1,1,1);
	    default : GameTextForPlayer(playerid,"~r~~k~/sign ~w~[1-5]",2000,6);
	}
	return 1;
}

CMD:pool(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
	    case 1: ApplyAnimationEx(playerid,"POOL","POOL_ChalkCue",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimationEx(playerid,"POOL","POOL_Idle_Stance",4.1,1,1,1,1,1,1);
	    case 3: ApplyAnimationEx(playerid,"POOL","POOL_Long_Shot",4.1,1,1,1,1,1,1);
	    case 4: ApplyAnimationEx(playerid,"POOL","POOL_Long_Shot_O",4.1,1,1,1,1,1,1);
	    case 5: ApplyAnimationEx(playerid,"POOL","POOL_Long_Start",4.1,1,1,1,1,1,1);
	    case 6: ApplyAnimationEx(playerid,"POOL","POOL_Long_Start_O",4.1,1,1,1,1,1,1);
	    case 7: ApplyAnimationEx(playerid,"POOL","POOL_Med_Shot",4.1,1,1,1,1,1,1);
	    case 8: ApplyAnimationEx(playerid,"POOL","POOL_Med_Shot_O",4.1,1,1,1,1,1,1);
	    case 9: ApplyAnimationEx(playerid,"POOL","POOL_Med_Start",4.1,1,1,1,1,1,1);
	    case 10: ApplyAnimationEx(playerid,"POOL","POOL_Med_Start_O",4.1,1,1,1,1,1,1);
	    case 11: ApplyAnimationEx(playerid,"POOL","POOL_Place_White",4.1,1,1,1,1,1,1);
	    case 12: ApplyAnimationEx(playerid,"POOL","POOL_Short_Shot",4.1,1,1,1,1,1,1);
	    case 13: ApplyAnimationEx(playerid,"POOL","POOL_Short_Shot_O",4.1,1,1,1,1,1,1);
	    case 14: ApplyAnimationEx(playerid,"POOL","POOL_Short_Start",4.1,1,1,1,1,1,1);
	    case 15: ApplyAnimationEx(playerid,"POOL","POOL_Short_Start_O",4.1,1,1,1,1,1,1);
	    case 16: ApplyAnimationEx(playerid,"POOL","POOL_Walk",4.1,1,1,1,1,1,1);
	    case 17: ApplyAnimationEx(playerid,"POOL","POOL_Walk_Start",4.1,1,1,1,1,1,1);
	    case 18: ApplyAnimationEx(playerid,"POOL","POOL_XLong_Shot",4.1,1,1,1,1,1,1);
	    case 19: ApplyAnimationEx(playerid,"POOL","POOL_XLong_Shot_O",4.1,1,1,1,1,1,1);
	    case 20: ApplyAnimationEx(playerid,"POOL","POOL_XLong_Start",4.1,1,1,1,1,1,1);
	    case 21: ApplyAnimationEx(playerid,"POOL","POOL_XLong_Start_O",4.1,1,1,1,1,1,1);
	    default : GameTextForPlayer(playerid,"~r~~k~/pool ~w~[1-21]",2000,6);
	}
	return 1;
}

CMD:paul(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
    switch(animid)
	{
	    case 1: ApplyAnimationEx(playerid,"PAULNMAC","Piss_in",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimationEx(playerid,"PAULNMAC","Piss_out",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"PAULNMAC","wank_in",4.1,1,1,1,1,1,1);
		case 4: ApplyAnimationEx(playerid,"PAULNMAC","wank_out",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/paul ~w~[1-4]",2000,6);
	}
	return 1;
}

CMD:taxi(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"MISC","Hiker_Pose",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"MISC","Hiker_Pose_L",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/taxi ~w~[1-2]",2000,6);
	}
	return 1;
}

CMD:chase(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
    switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll_F",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"MD_CHASE","MD_HANG_Lnd_Roll",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/chase ~w~[1-3]",2000,6);
	}
	return 1;
}

CMD:kiss(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"KISSING","BD_GF_Wave",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"KISSING","gfwave2",4.1,1,1,1,1,1,1);
	    case 3: ApplyAnimationEx(playerid,"KISSING","Grlfrd_Kiss_01",4.1,1,1,1,1,1,1);
	    case 4: ApplyAnimationEx(playerid,"KISSING","Grlfrd_Kiss_02",4.1,1,1,1,1,1,1);
	    case 5: ApplyAnimationEx(playerid,"KISSING","Grlfrd_Kiss_03",4.1,1,1,1,1,1,1);
	    case 6: ApplyAnimationEx(playerid,"KISSING","Playa_Kiss_01",4.1,1,1,1,1,1,1);
	    case 7: ApplyAnimationEx(playerid,"KISSING","Playa_Kiss_02",4.1,1,1,1,1,1,1);
	    default : GameTextForPlayer(playerid,"~r~~k~/kiss ~w~[1-7]",2000,6);
	}
	return 1;
}

CMD:riot(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
	    case 1: ApplyAnimationEx(playerid,"RIOT","RIOT_ANGRY",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimationEx(playerid,"RIOT","RIOT_ANGRY_B",4.1,1,1,1,1,1,1);
	    case 3: ApplyAnimationEx(playerid,"RIOT","RIOT_challenge",4.1,1,1,1,1,1,1);
	    case 4: ApplyAnimationEx(playerid,"RIOT","RIOT_CHANT",4.1,1,1,1,1,1,1);
	    case 5: ApplyAnimationEx(playerid,"RIOT","RIOT_FUKU",4.1,1,1,1,1,1,1);
	    case 6: ApplyAnimationEx(playerid,"RIOT","RIOT_PUNCHES",4.1,1,1,1,1,1,1);
	    case 7: ApplyAnimationEx(playerid,"RIOT","RIOT_shout",4.1,1,1,1,1,1,1);
	    default : GameTextForPlayer(playerid,"~r~~k~/riot ~w~[1-7]",2000,6);
	}
	return 1;
}

CMD:lowrider(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
    switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"LOWRIDER","F_smklean_loop",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"LOWRIDER","prtial_gngtlkH",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/lowrider ~w~[1-2]",2000,6);
	}
	return 1;
}

CMD:knife(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"KNIFE","KILL_Knife_Ped_Die",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"KNIFE","knife_hit_3",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/knife ~w~[1-2]",2000,6);
	}
	return 1;
}

CMD:seat(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"PED","SEAT_down",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"INT_HOUSE","LOU_In",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"BEACH", "ParkSit_M_loop",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/seat ~w~[1-3]",2000,6);
	}
	return 1;
}

CMD:dance(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
		case 2: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
		case 3: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
		case 4: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
		default : GameTextForPlayer(playerid,"~r~~k~/dance ~w~[1-4]",2000,6);
	}
	return 1;
}

CMD:sex(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"SNM","SPANKING_IDLEW",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"SNM","SPANKING_IDLEP",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"SNM","SPANKINGW",4.1,1,1,1,1,1,1);
		case 4: ApplyAnimationEx(playerid,"SNM","SPANKINGP",4.1,1,1,1,1,1,1);
		case 5: ApplyAnimationEx(playerid,"SNM","SPANKEDW",4.1,1,1,1,1,1,1);
		case 6: ApplyAnimationEx(playerid,"SNM","SPANKEDP",4.1,1,1,1,1,1,1);
		case 7: ApplyAnimationEx(playerid,"SNM","SPANKING_ENDW",4.1,1,1,1,1,1,1);
		case 8: ApplyAnimationEx(playerid,"SNM","SPANKING_ENDP",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/sex ~w~[1-8]",2000,6);
	}
	return 1;
}

CMD:office(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
	    case 1: ApplyAnimationEx(playerid,"INT_OFFICE","FF_Dam_Fwd",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimationEx(playerid,"INT_OFFICE","OFF_Sit_2Idle_180",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"INT_OFFICE","OFF_Sit_Bored_Loop",4.1,1,1,1,1,1,1);
		case 4: ApplyAnimationEx(playerid,"INT_OFFICE","OFF_Sit_Crash",4.1,1,1,1,1,1,1);
		case 5: ApplyAnimationEx(playerid,"INT_OFFICE","OFF_Sit_Drink",4.1,1,1,1,1,1,1);
		case 6: ApplyAnimationEx(playerid,"INT_OFFICE","OFF_Sit_Idle_Loop",4.1,1,1,1,1,1,1);
	    case 7: ApplyAnimationEx(playerid,"INT_OFFICE","OFF_Sit_In",4.1,1,1,1,1,1,1);
	    case 8: ApplyAnimationEx(playerid,"INT_OFFICE","OFF_Sit_Read",4.1,1,1,1,1,1,1);
		case 9: ApplyAnimationEx(playerid,"INT_OFFICE","OFF_Sit_Type_Loop",4.1,1,1,1,1,1,1);
		case 10: ApplyAnimationEx(playerid,"INT_OFFICE","OFF_Sit_Watch",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/office ~w~[1-10]",2000,6);
	}
	return 1;
}

CMD:gang(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
    switch(animid)
	{
	    case 1: ApplyAnimationEx(playerid,"GANGS","hndshkaa",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimationEx(playerid,"GANGS","hndshkba",4.1,1,1,1,1,1,1);
	    case 3: ApplyAnimationEx(playerid,"GANGS","hndshkda",4.1,1,1,1,1,1,1);
		case 4: ApplyAnimationEx(playerid,"GANGS","hndshkea",4.1,1,1,1,1,1,1);
		case 5: ApplyAnimationEx(playerid,"GANGS","hndshkfa",4.1,1,1,1,1,1,1);
	    case 6: ApplyAnimationEx(playerid,"GANGS","hndshkfa_swt",4.1,1,1,1,1,1,1);
	    case 7: ApplyAnimationEx(playerid,"GANGS","prtial_gngtlkA",4.1,1,1,1,1,1,1);
	    case 8: ApplyAnimationEx(playerid,"GANGS","prtial_gngtlkB",4.1,1,1,1,1,1,1);
	    case 9: ApplyAnimationEx(playerid,"GANGS","prtial_gngtlkCt",4.1,1,1,1,1,1,1);
	    case 10: ApplyAnimationEx(playerid,"GANGS","prtial_gngtlkD",4.1,1,1,1,1,1,1);
	    case 11: ApplyAnimationEx(playerid,"GANGS","prtial_gngtlkE",4.1,1,1,1,1,1,1);
	    case 12: ApplyAnimationEx(playerid,"GANGS","prtial_gngtlkF",4.1,1,1,1,1,1,1);
	    case 13: ApplyAnimationEx(playerid,"GANGS","prtial_gngtlkG",4.1,1,1,1,1,1,1);
	    case 14: ApplyAnimationEx(playerid,"GANGS","prtial_gngtlkH",4.1,1,1,1,1,1,1);
	    case 15: ApplyAnimationEx(playerid,"GANGS","prtial_hndshk_01",4.1,1,1,1,1,1,1);
	    default : GameTextForPlayer(playerid,"~r~~k~/gangs ~w~[1-15]",2000,6);
	}
	return 1;
}

CMD:eat(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"FOOD","FF_Dam_Bkw",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"FOOD","FF_Die_Bkw",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"FOOD","FF_Die_Fwd",4.1,1,1,1,1,1,1);
		case 4: ApplyAnimationEx(playerid,"FOOD","FF_Die_Left",4.1,1,1,1,1,1,1);
		case 5: ApplyAnimationEx(playerid,"FOOD","FF_Die_Right",4.1,1,1,1,1,1,1);
		case 6: ApplyAnimationEx(playerid,"FOOD","FF_Sit_Eat1",4.1,1,1,1,1,1,1);
		case 7: ApplyAnimationEx(playerid,"FOOD","FF_Sit_Look",4.1,1,1,1,1,1,1);
		case 8: ApplyAnimationEx(playerid,"FOOD", "EAT_Burger",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/eat ~w~[1-8]",2000,6);
	}
	return 1;
}

CMD:casino(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
	    case 1: ApplyAnimationEx(playerid,"CASINO","cards_lose",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimationEx(playerid,"CASINO","cards_pick_01",4.1,1,1,1,1,1,1);
	    case 3: ApplyAnimationEx(playerid,"CASINO","manwinb",4.1,1,1,1,1,1,1);
	    case 4: ApplyAnimationEx(playerid,"CASINO","Roulette_bet",4.1,1,1,1,1,1,1);
	    default : GameTextForPlayer(playerid,"~r~~k~/casino ~w~[1-4]",2000,6);
	}
	return 1;
}

CMD:bar(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"BAR","Barcustom_get",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"BAR","Barcustom_order",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"BAR","Barserve_bottle",4.1,1,1,1,1,1,1);
		case 4: ApplyAnimationEx(playerid,"BAR","Barserve_give",4.1,1,1,1,1,1,1);
		case 5: ApplyAnimationEx(playerid,"BAR","Barserve_glass",4.1,1,1,1,1,1,1);
		case 6: ApplyAnimationEx(playerid,"BAR","Barserve_in",4.1,1,1,1,1,1,1);
		case 7: ApplyAnimationEx(playerid,"BAR","Barserve_loop",4.1,1,1,1,1,1,1);
		case 8: ApplyAnimationEx(playerid,"BAR","Barserve_order",4.1,1,1,1,1,1,1);
		case 9: ApplyAnimationEx(playerid,"BAR","dnk_stndF_loop",4.1,1,1,1,1,1,1);
		case 10: ApplyAnimationEx(playerid,"BAR","BARman_idle",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/bar ~w~[1-10]",2000,6);
	}
	return 1;
}

CMD:fire(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
    switch(animid)
	{
		case 1: ApplyAnimationEx(playerid,"BD_FIRE","BD_GF_Wave",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"BD_FIRE","BD_Panic_01",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"BD_FIRE","BD_Panic_03",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/fire ~w~[1-3]",2000,6);
	}
	return 1;
}

CMD:beach(playerid, params[])
{
    new animid;
	sscanf(params,"i",animid);
    switch(animid)
    {
		case 1: ApplyAnimationEx(playerid,"BEACH","Lay_Bac_Loop",4.1,1,1,1,1,1,1);
		case 2: ApplyAnimationEx(playerid,"BEACH","ParkSit_W_loop",4.1,1,1,1,1,1,1);
		case 3: ApplyAnimationEx(playerid,"BEACH","SitnWait_loop_W",4.1,1,1,1,1,1,1);
		default : GameTextForPlayer(playerid,"~r~~k~/beach ~w~[1-3]",2000,6);
	}
	return 1;
}

CMD:handsup(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
CMD:pee(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
CMD:lookout(playerid) return ApplyAnimationEx(playerid,"SHOP", "ROB_Shifty",4.1,1,1,1,1,1,1);
CMD:crossarms(playerid) return ApplyAnimationEx(playerid,"COP_AMBIENT", "Coplook_loop",4.1,1,1,1,1,1,1);
CMD:lay(playerid) return ApplyAnimationEx(playerid,"BEACH", "bather",4.1,1,1,1,1,1,1);
CMD:hide(playerid) return ApplyAnimationEx(playerid,"ped", "cower",4.1,1,1,1,1,1,1);
CMD:vomit(playerid) return ApplyAnimationEx(playerid,"FOOD", "EAT_Vomit_P",4.1,1,1,1,1,1,1);
CMD:wave(playerid) return ApplyAnimationEx(playerid,"ON_LOOKERS", "wave_loop",4.1,1,1,1,1,1,1);
CMD:deal(playerid) return ApplyAnimationEx(playerid,"DEALER", "DEALER_DEAL",4.1,1,1,1,1,1,1);
CMD:chat(playerid) return ApplyAnimationEx(playerid,"PED","IDLE_CHAT",4.1,1,1,1,1,1,1);
CMD:fucku(playerid) return ApplyAnimationEx(playerid,"PED","fucku",4.1,1,1,1,1,1,1);
CMD:taichi(playerid) return ApplyAnimationEx(playerid,"PARK","Tai_Chi_Loop",4.1,1,1,1,1,1,1);
CMD:police(playerid) return ApplyAnimationEx(playerid,"POLICE","CopTraf_Stop",4.1,1,1,1,1,1,1);
CMD:lock(playerid) return ApplyAnimationEx(playerid,"ON_LOOKERS","shout_02",4.1,1,1,1,1,1,1);
CMD:misc(playerid) return ApplyAnimationEx(playerid,"MISC","Plyrlean_loop",4.1,1,1,1,1,1,1);
CMD:medic(playerid) return ApplyAnimationEx(playerid,"MEDIC","CPR",4.1,1,1,1,1,1,1);
CMD:slapass(playerid) return ApplyAnimationEx(playerid,"SWEET","sweet_ass_slap",4.1,1,1,1,1,1,1);
CMD:wuzi(playerid) return ApplyAnimationEx(playerid,"WUZI","CS_Dead_Guy",4.1,1,1,1,1,1,1);
CMD:off(playerid) return ApplyAnimationEx(playerid,"BASEBALL","Bat_Hit_3",4.1,1,1,1,1,1,1);
CMD:bomb(playerid) return ApplyAnimationEx(playerid,"BOMBER", "BOM_Plant",4.1,1,1,1,1,1,1);
CMD:robman(playerid) return ApplyAnimationEx(playerid,"SHOP", "ROB_Loop_Threat",4.1,1,1,1,1,1,1);
CMD:carry(playerid) return ApplyAnimationEx(playerid,"CARRY","crry_prtial",4.1,1,1,1,1,1,1);
CMD:press(playerid) return ApplyAnimationEx(playerid,"benchpress","gym_bp_celebrate",4.1,1,1,1,1,1,1);


CMD:animlist(playerid, params[])
{
	new pageid;
	sscanf(params,"i",pageid);
	switch(pageid)
	{
		case 1:
		{
			SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [2 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animanimairport");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animattractors [1 - 3]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animanimbar [1 - 12]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbeer");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbaseball [1 - 11]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbdfire [1 - 13]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbeach [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbenchpress [1 - 7]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbfinj [1 - 4]");
		}
		case 2:
		{
			SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [3 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbiked [1 - 19]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbikeh [1 - 18]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbikeleap [1 - 9]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbikes [1 - 20]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbikev [1 - 18]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbikedbz [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbmx [1 - 18]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbomber [1 - 6]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbox [1 - 10]");
		}
		case 3:
		{
			SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [4 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbsktball [1 - 41]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbuddy [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbus [1 - 9]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcamera [1 - 14]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcar [1 - 11]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcarry [1 - 7]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcarchat [1 - 21]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcasino [1 - 25]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcellin");
		}
		case 4:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [5 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcellout");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsaw [1 - 11]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animchoppa [1 - 18]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animclothes [1 - 13]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcoach [1 - 6]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcolt [1 - 7]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcopa [1 - 12]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcopdvb [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcrack[1 - 10]");
		}
		case 5:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [6 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animcrib [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animdamjump [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animdance [1 - 17]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animdealer [1 - 7]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animdildo [1 - 9]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animdodge [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animdozer [1 - 10]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animdrivebys [1 - 8]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animduck");
		}
		case 6:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [7 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animenterveh");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animexitveh");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animfat [1 - 18]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animfightb [1 - 10]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animfightc [1 - 12]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animfightd [1 - 10]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animfighte [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animfinale [1 - 16]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animfinale2 [1 - 8]");
		}
		case 7:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [8 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animflame");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animflowers [1 - 3]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animfood [1 - 33]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animfw [1 - 9]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animgangs [1 - 33]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animghands [1 - 20]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animghettodb [1 - 7]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animgog");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animgraffity [1 - 2]");
		}
		case 8:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [9 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animgreya [1 - 3]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animgren [1 - 3]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animgym [1 - 24]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animhaircut [1 - 13]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animhandsup");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animheist [1 - 10]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animmedic");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animinthouse [1 - 10]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animintoffice [1 - 10]");
		}
		case 9:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [10 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animintshop [1 - 8]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animjetpack");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animjst [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animkart [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animkissing [1 - 15]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animlapdan1 [1 - 2]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animlapdan2 [1 - 2]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animlapdan3 [1 - 2]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animlowrider [1 - 39]");
		}
		case 10:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [11 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animmdchase [1 - 25]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animmddend [1 - 8]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animms [1 - 41]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animmtb [1 - 18]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animmusculcar [1 - 17]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animnevada [1 - 2]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animlookers [1 - 29]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animotb [1 - 11]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animparachute [1 - 22]");
		}
		case 11:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [12 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animpark [1 - 3]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animpaulnmac [1 - 12]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animpee");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animped [1 - 295]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animplayerdvbys [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animplayidles [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animpolice [1 - 10]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animpool [1 - 21]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animpoor [1 - 2]");
		}
		case 12:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [13 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animpython [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animquad [1 - 17]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animquadbz [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animrapping [1 - 8]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animrifle [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animriot [1 - 7]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animrobbank [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animrocket [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animrustler [1 - 5]");
		}
		case 13:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [14 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animryder [1 - 16]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animscratching [1 - 12]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsit");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animshamal [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animshop [1 - 26]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animshotgun [1 - 3]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsilenced [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animskate [1 - 3]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsmoking [1 - 9]");
		}
		case 14:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [15 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsniper");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animspraycan [1 - 2]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsprunk");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animstrip [1 - 20]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animbath [1 - 18]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animswat [1 - 24]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsweet [1 - 7]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animswim [1 - 7]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsword [1 - 10]");
		}
		case 15:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [16 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animtank [1 - 6]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animtattoos [1 - 57]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animtec [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animtrain [1 - 4]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animtruck [1 - 17]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animuzi [1 - 5]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animvan [1 - 8]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animvending [1 - 6]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animvortex [1 - 4]");
		}
		case 16:
		{
		    SendClientMessageEx(playerid,COLOR_WHITE,"Анимации [17 / 17]:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animway [1 - 18]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animweap [1 - 17]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animwine");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animwuzi [1 - 12]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsnm [1 - 8]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animblowjob [1 - 12]");
			SendClientMessageEx(playerid,COLOR_WHITE,"/animsex [1 - 20]");
		}
		default :
		{
			SendClientMessageEx(playerid,COLOR_WHITE,"Анимации:");
			SendClientMessageEx(playerid,COLOR_WHITE,"/bar /beach /bomb /casino /carry /chase /chat /crack /crossarms /dance");
			SendClientMessageEx(playerid,COLOR_WHITE,"/deal /eat /fire /fucku /gang /handsup /hide /kiss /knife /lay /lock");
			SendClientMessageEx(playerid,COLOR_WHITE,"/lowrider /medic /misc /office /off /paul /ped /pee /police /pool /press");
			SendClientMessageEx(playerid,COLOR_WHITE,"/rap /riot /robman /sex /sign /slapass /smoke /taichi /taxi /vomit /walk /wave /wuzi");
		}
	}

	return 1;
}


CMD:animattractor(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "Attractors", "Stepsit_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "Attractors", "Stepsit_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "Attractors", "Stepsit_out", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animattractors [1 - 3]");
	}
	return 1;
}

CMD:animbar(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BAR", "Barcustom_get", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BAR", "Barcustom_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BAR", "Barcustom_order", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BAR", "Barserve_bottle", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BAR", "Barserve_give", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BAR", "Barserve_glass", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BAR", "Barserve_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BAR", "Barserve_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BAR", "Barserve_order", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BAR", "dnk_stndF_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BAR", "dnk_stndM_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "BAR", "BARman_idle", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbar [1 - 12]");
	}
	return 1;
}


CMD:animbaseball(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BASEBALL", "Bat_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BASEBALL", "Bat_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BASEBALL", "Bat_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BASEBALL", "Bat_4", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BASEBALL", "Bat_block", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BASEBALL", "Bat_Hit_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BASEBALL", "Bat_Hit_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BASEBALL", "Bat_Hit_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BASEBALL", "Bat_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BASEBALL", "Bat_M", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BASEBALL", "BAT_PART", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbaseball [1 - 11]");
	}
	return 1;
}


CMD:animbdfire(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BD_FIRE", "BD_Fire1", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BD_FIRE", "BD_Fire2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BD_FIRE", "BD_Fire3", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BD_FIRE", "BD_GF_Wave", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BD_FIRE", "BD_Panic_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BD_FIRE", "BD_Panic_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BD_FIRE", "BD_Panic_03", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BD_FIRE", "BD_Panic_04", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BD_FIRE", "BD_Panic_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BD_FIRE", "M_smklean_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BD_FIRE", "M_smklean_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "BD_FIRE", "Playa_Kiss_03", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbdfire [1 - 13]");
	}
	return 1;
}


CMD:animbeach(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BEACH", "bather", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BEACH", "Lay_Bac_Loop", 4.1, 0, 1, 1, 1, 1, 1);
 		case 3: ApplyAnimationEx(playerid, "BEACH", "BD_Fire3", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BEACH", "ParkSit_W_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BEACH", "SitnWait_loop_W", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbeach [1 - 5]");
	}
	return 1;
}

CMD:animbenchpress(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "benchpress", "gym_bp_celebrate", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "benchpress", "gym_bp_down", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "benchpress", "gym_bp_getoff", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "benchpress", "gym_bp_geton", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_smooth", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbenchpress [1 - 7]");
	}
	return 1;
}

CMD:animbfinj(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BF_injection", "BF_getin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BF_injection", "BF_getin_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BF_injection", "BF_getout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BF_injection", "BF_getout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbfinj [1 - 4]");
	}
	return 1;
}

CMD:animbiked(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BIKED", "BIKEd_Back", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BIKED", "BIKEd_drivebyFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BIKED", "BIKEd_drivebyLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BIKED", "BIKEd_drivebyRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BIKED", "BIKEd_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BIKED", "BIKEd_getoffBACK", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BIKED", "BIKEd_getoffLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BIKED", "BIKEd_getoffRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BIKED", "BIKEd_hit", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BIKED", "BIKEd_jumponL", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BIKED", "BIKEd_jumponR", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "BIKED", "BIKEd_kick", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "BIKED", "BIKEd_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "BIKED", "BIKEd_passenger", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "BIKED", "BIKEd_pushes", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "BIKED", "BIKEd_Ride", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "BIKED", "BIKEd_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "BIKED", "BIKEd_shuffle", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "BIKED", "BIKEd_Still", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbiked [1 - 19]");
	}
	return 1;
}

CMD:animbikeh(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_Back", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_drivebyFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_drivebyLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_drivebyRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_getoffBACK", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_getoffLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_getoffRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_hit", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_jumponL", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_jumponR", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_kick", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_passenger", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_pushes", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_Ride", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "BIKEH", "BIKEh_Still", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbikeh [1 - 18]");
	}
	return 1;
}
CMD:animbikeleap(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BIKELEAP", "bk_blnce_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BIKELEAP", "bk_blnce_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BIKELEAP", "bk_jmp", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BIKELEAP", "bk_rdy_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BIKELEAP", "bk_rdy_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BIKELEAP", "struggle_cesar", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BIKELEAP", "struggle_driver", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BIKELEAP", "truck_driver", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BIKELEAP", "truck_getin", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbikeleap [1 - 9]");
	}
	return 1;
}

CMD:animbikes(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BIKES", "BIKEs_Back", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BIKES", "BIKEs_drivebyFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BIKES", "BIKEs_drivebyLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BIKES", "BIKEs_drivebyRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BIKES", "BIKEs_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BIKES", "BIKEs_getoffBACK", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BIKES", "BIKEs_getoffLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BIKES", "BIKEs_getoffRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BIKES", "BIKEs_hit", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BIKES", "BIKEs_jumponL", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BIKES", "BIKEs_jumponR", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "BIKES", "BIKEs_kick", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "BIKES", "BIKEs_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "BIKES", "BIKEs_passenger", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "BIKES", "BIKEs_pushes", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "BIKES", "BIKEs_Ride", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "BIKES", "BIKEs_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "BIKES", "BIKEs_Snatch_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "BIKES", "BIKEs_Snatch_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "BIKES", "BIKEs_Still", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbikes [1 - 20]");
	}
	return 1;
}

CMD:animbikev(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_Back", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_drivebyFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_drivebyLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_drivebyRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_getoffBACK", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_getoffLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_getoffRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_hit", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_jumponL", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_jumponR", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_kick", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_passenger", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_pushes", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_Ride", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "BIKEV", "BIKEv_Still", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbikev [1 - 18]");
	}
	return 1;
}

CMD:animbikedbz(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BIKE_DBZ", "Pass_Driveby_BWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BIKE_DBZ", "Pass_Driveby_FWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BIKE_DBZ", "Pass_Driveby_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BIKE_DBZ", "Pass_Driveby_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbikedbz [1 - 4]");
	}
	return 1;
}

CMD:animbmx(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BMX", "BMX_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BMX", "BMX_bunnyhop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BMX", "BMX_drivebyFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BMX", "BMX_driveby_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BMX", "BMX_driveby_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BMX", "BMX_fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BMX", "BMX_getoffBACK", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BMX", "BMX_pushes", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BMX", "BMX_getoffLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BMX", "BMX_getoffRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BMX", "BMX_jumponL", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "BMX", "BMX_jumponR", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "BMX", "BMX_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "BMX", "BMX_pedal", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "BMX", "BMX_Ride", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "BMX", "BMX_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "BMX", "BMX_sprint", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "BMX", "BMX_still", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbmx [1 - 18]");
	}
	return 1;
}

CMD:animbomber(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant_2Idle", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant_Crouch_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant_Crouch_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbomber [1 - 6]");
	}
	return 1;
}

CMD:animbox(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BOX", "boxhipin", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BOX", "boxhipup", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BOX", "boxshdwn", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BOX", "boxshup", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BOX", "bxhipwlk", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BOX", "bxhwlki", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BOX", "bxshwlk", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BOX", "bxshwlki", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BOX", "bxwlko", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BOX", "catch_box", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbox [1 - 10]");
	}
	return 1;
}

CMD:animbsktball(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_def_jump_shot", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_def_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_def_stepL", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_def_stepR", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Dnk", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Dnk_Gli", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Dnk_Gli_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Dnk_Lnch", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Dnk_Lnch_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Dnk_Lnd", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Dnk_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_idle", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_idle2", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_idle2_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_idleloop", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_idleloop_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_idle_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Jump_Cancel", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Jump_Cancel_0", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Jump_End", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Jump_Shot", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Jump_Shot_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Net_Dnk_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_pickup", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_pickup_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 26: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_react_miss", 4.1, 0, 1, 1, 1, 1, 1);
		case 27: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_react_score", 4.1, 0, 1, 1, 1, 1, 1);
		case 28: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_run", 4.1, 0, 1, 1, 1, 1, 1);
		case 29: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_run_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 30: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_SkidStop_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 31: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_SkidStop_L_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 32: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_SkidStop_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 33: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_SkidStop_R_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 34: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_walk", 4.1, 0, 1, 1, 1, 1, 1);
		case 35: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_WalkStop_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 36: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_WalkStop_L_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 37: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_WalkStop_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 38: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_WalkStop_R_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 39: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_walk_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 40: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_walk_start", 4.1, 0, 1, 1, 1, 1, 1);
		case 41: ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_walk_start_O", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbsktball [1 - 41]");
	}
	return 1;
}

CMD:animbuddy(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BUDDY", "buddy_crouchfire", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BUDDY", "buddy_crouchreload", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BUDDY", "buddy_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BUDDY", "buddy_fire_poor", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BUDDY", "buddy_reload", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbuddy [1 - 5]");
	}
	return 1;
}
CMD:animbus(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BUS", "BUS_close", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BUS", "BUS_getin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BUS", "BUS_getin_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BUS", "BUS_getout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BUS", "BUS_getout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BUS", "BUS_jacked_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BUS", "BUS_open", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BUS", "BUS_open_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BUS", "BUS_pullout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbus [1 - 9]");
	}
	return 1;
}
CMD:animcamera(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CAMERA", "camcrch_cmon", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CAMERA", "camcrch_idleloop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CAMERA", "camcrch_stay", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CAMERA", "camcrch_to_camstnd", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CAMERA", "camstnd_cmon", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "CAMERA", "camstnd_idleloop", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "CAMERA", "camstnd_lkabt", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "CAMERA", "camstnd_to_camcrch", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "CAMERA", "piccrch_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "CAMERA", "piccrch_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "CAMERA", "piccrch_take", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "CAMERA", "picstnd_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "CAMERA", "picstnd_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "CAMERA", "picstnd_take", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcamera [1 - 14]");
	}
	return 1;
}
CMD:animcar(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CAR", "Fixn_Car_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CAR", "Fixn_Car_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CAR", "flag_drop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CAR", "Sit_relaxed", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CAR", "Tap_hand", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "CAR", "Tyd2car_bump", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "CAR", "Tyd2car_high", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "CAR", "Tyd2car_low", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "CAR", "Tyd2car_med", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "CAR", "Tyd2car_TurnL", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "CAR", "Tyd2car_TurnR", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcar [1 - 11]");
	}
	return 1;
}
CMD:animcarry(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CARRY", "crry_prtial", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CARRY", "liftup", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CARRY", "liftup05", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CARRY", "liftup105", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CARRY", "putdwn", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "CARRY", "putdwn05", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "CARRY", "putdwn105", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcarry [1 - 7]");
	}
	return 1;
}
CMD:animcarchat(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CAR_CHAT", "carfone_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CAR_CHAT", "carfone_loopA", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CAR_CHAT", "carfone_loopA_to_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CAR_CHAT", "carfone_loopB", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CAR_CHAT", "carfone_loopB_to_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "CAR_CHAT", "carfone_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc1_BL", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc1_BR", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc1_FL", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc1_FR", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc2_FL", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc3_BR", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc3_FL", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc3_FR", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc4_BL", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc4_BR", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc4_FL", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "CAR_CHAT", "CAR_Sc4_FR", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "CAR_CHAT", "car_talkm_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "CAR_CHAT", "car_talkm_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "CAR_CHAT", "car_talkm_out", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcarchat [1 - 21]");
	}
	return 1;
}
CMD:animcasino(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CASINO", "cards_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CASINO", "cards_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CASINO", "cards_lose", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CASINO", "cards_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CASINO", "cards_pick_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "CASINO", "cards_pick_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "CASINO", "cards_raise", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "CASINO", "cards_win", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "CASINO", "dealone", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "CASINO", "manwinb", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "CASINO", "manwind", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "CASINO", "Roulette_bet", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "CASINO", "Roulette_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "CASINO", "Roulette_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "CASINO", "Roulette_lose", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "CASINO", "Roulette_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "CASINO", "Roulette_win", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "CASINO", "Slot_bet_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "CASINO", "Slot_bet_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "CASINO", "Slot_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "CASINO", "Slot_lose_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "CASINO", "Slot_Plyr", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "CASINO", "Slot_wait", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "CASINO", "Slot_win_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "CASINO", "wof", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcasino [1 - 25]");
	}
	return 1;
}
CMD:animchainsaw(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CHAINSAW", "CSAW_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CHAINSAW", "CSAW_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CHAINSAW", "CSAW_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CHAINSAW", "CSAW_G", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CHAINSAW", "CSAW_Hit_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "CHAINSAW", "CSAW_Hit_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "CHAINSAW", "CSAW_Hit_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "CHAINSAW", "csaw_part", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "CHAINSAW", "IDLE_csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "CHAINSAW", "WEAPON_csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "CHAINSAW", "WEAPON_csawlo", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animsaw [1 - 11]");
	}
	return 1;
}
CMD:animchoppa(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_bunnyhop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_drivebyFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_driveby_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_driveby_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_getoffBACK", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_getoffLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_getoffRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_jumponL", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_jumponR", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_pedal", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_Pushes", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_ride", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_sprint", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "CHOPPA", "CHOPPA_Still", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animchoppa [1 - 18]");
	}
	return 1;
}
CMD:animclothes(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Buy", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CLOTHES", "CLO_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_Hat", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_In_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_Legs", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_Out_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_Shoes", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_Torso", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_Watch", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animclothes [1 - 13]");
	}
	return 1;
}
CMD:animcoach(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "COACH", "COACH_inL", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "COACH", "COACH_inR", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "COACH", "COACH_opnL", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "COACH", "COACH_opnR", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "COACH", "COACH_outL", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "COACH", "COACH_outR", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcoach [1 - 6]");
	}
	return 1;
}
CMD:animcolt(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "COLT45", "2guns_crouchfire", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "COLT45", "colt45_crouchfire", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "COLT45", "colt45_crouchreload", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "COLT45", "colt45_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "COLT45", "colt45_fire_2hands", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "COLT45", "colt45_reload", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "COLT45", "sawnoff_reload", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcolt [1 - 7]");
	}
	return 1;
}
CMD:animcopambient(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "COP_AMBIENT", "Copbrowse_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "COP_AMBIENT", "Copbrowse_nod", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "COP_AMBIENT", "Copbrowse_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "COP_AMBIENT", "Copbrowse_shake", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_nod", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_shake", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_think", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_watch", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcopa [1 - 12]");
	}
	return 1;
}
CMD:animcopdvbyz(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "COP_DVBYZ", "COP_Dvby_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "COP_DVBYZ", "COP_Dvby_FT", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "COP_DVBYZ", "COP_Dvby_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "COP_DVBYZ", "COP_Dvby_R", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcopdvb [1 - 4]");
	}
	return 1;
}
CMD:animcrack(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CRACK", "Bbalbat_Idle_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CRACK", "Bbalbat_Idle_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CRACK", "crckdeth1", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CRACK", "crckdeth2", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CRACK", "crckdeth3", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "CRACK", "crckidle1", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "CRACK", "crckidle2", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "CRACK", "crckidle3", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "CRACK", "crckidle4", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcrack[1 - 10]");
	}
	return 1;
}
CMD:animcrib(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "CRIB", "CRIB_Console_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "CRIB", "CRIB_Use_Switch", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "CRIB", "PED_Console_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "CRIB", "PED_Console_Loose", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "CRIB", "PED_Console_Win", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animcrib [1 - 5]");
	}
	return 1;
}
CMD:animdamjump(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "DAM_JUMP", "DAM_Dive_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "DAM_JUMP", "DAM_Land", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "DAM_JUMP", "DAM_Launch", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "DAM_JUMP", "Jump_Roll", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "DAM_JUMP", "SF_JumpWall", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animdamjump [1 - 5]");
	}
	return 1;
}
CMD:animdancing(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "DANCING", "bd_clap", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "DANCING", "bd_clap1", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "DANCING", "dance_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "DANCING", "DAN_Down_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "DANCING", "DAN_Left_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "DANCING", "DAN_Loop_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "DANCING", "DAN_Right_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "DANCING", "DAN_Up_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "DANCING", "dnce_M_a", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "DANCING", "dnce_M_b", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "DANCING", "dnce_M_c", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "DANCING", "dnce_M_d", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "DANCING", "dnce_M_e", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
		case 15: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
		case 16: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
		case 17: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE4);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animdance [1 - 17]");
	}
	return 1;
}
CMD:animdealer(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "DEALER", "DEALER_DEAL", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE_03", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "DEALER", "DRUGS_BUY", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "DEALER", "shop_pay", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animdealer [1 - 7]");
	}
	return 1;
}
CMD:animdildo(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "DILDO", "DILDO_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "DILDO", "DILDO_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "DILDO", "DILDO_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "DILDO", "DILDO_block", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "DILDO", "DILDO_G", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "DILDO", "DILDO_Hit_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "DILDO", "DILDO_Hit_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "DILDO", "DILDO_Hit_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "DILDO", "DILDO_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animdildo [1 - 9]");
	}
	return 1;
}
CMD:animdodje(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "DODGE", "Cover_Dive_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "DODGE", "Cover_Dive_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "DODGE", "Crushed", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "DODGE", "Crush_Jump", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animdodge [1 - 4]");
	}
	return 1;
}
CMD:animdozer(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "DOZER", "DOZER_Align_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "DOZER", "DOZER_Align_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "DOZER", "DOZER_getin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "DOZER", "DOZER_getin_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "DOZER", "DOZER_getout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "DOZER", "DOZER_getout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "DOZER", "DOZER_Jacked_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "DOZER", "DOZER_Jacked_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "DOZER", "DOZER_pullout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "DOZER", "DOZER_pullout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animdozer [1 - 10]");
	}
	return 1;
}
CMD:animdrivebys(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "DRIVEBYS", "Gang_DrivebyLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "DRIVEBYS", "Gang_DrivebyLHS_Bwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "DRIVEBYS", "Gang_DrivebyLHS_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "DRIVEBYS", "Gang_DrivebyRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "DRIVEBYS", "Gang_DrivebyRHS_Bwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "DRIVEBYS", "Gang_DrivebyRHS_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "DRIVEBYS", "Gang_DrivebyTop_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "DRIVEBYS", "Gang_DrivebyTop_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animdrivebys [1 - 8]");
	}
	return 1;
}
CMD:animfat(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "FAT", "FatIdle", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "FAT", "FatIdle_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "FAT", "FatIdle_Csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "FAT", "FatIdle_Rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "FAT", "FatRun", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "FAT", "FatRun_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "FAT", "FatRun_Csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "FAT", "FatRun_Rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "FAT", "FatSprint", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "FAT", "FatWalk", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "FAT", "FatWalkstart", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "FAT", "FatWalkstart_Csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "FAT", "FatWalkSt_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "FAT", "FatWalkSt_Rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "FAT", "FatWalk_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "FAT", "FatWalk_Csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "FAT", "FatWalk_Rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "FAT", "IDLE_tired", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animfat [1 - 18]");
	}
	return 1;
}
CMD:animfightb(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "FIGHT_B", "FightB_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "FIGHT_B", "FightB_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "FIGHT_B", "FightB_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "FIGHT_B", "FightB_block", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "FIGHT_B", "FightB_G", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "FIGHT_B", "FightB_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "FIGHT_B", "FightB_M", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "FIGHT_B", "HitB_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "FIGHT_B", "HitB_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "FIGHT_B", "HitB_3", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animfightb [1 - 10]");
	}
	return 1;
}
CMD:animfightc(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "FIGHT_C", "FightC_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "FIGHT_C", "FightC_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "FIGHT_C", "FightC_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "FIGHT_C", "FightC_block", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "FIGHT_C", "FightC_blocking", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "FIGHT_C", "FightC_G", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "FIGHT_C", "FightC_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "FIGHT_C", "FightC_M", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "FIGHT_C", "FightC_Spar", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "FIGHT_C", "HitC_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "FIGHT_C", "HitC_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "FIGHT_C", "HitC_3", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animfightc [1 - 12]");
	}
	return 1;
}
CMD:animfightd(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "FIGHT_D", "FightD_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "FIGHT_D", "FightD_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "FIGHT_D", "FightD_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "FIGHT_D", "FightD_block", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "FIGHT_D", "FightD_G", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "FIGHT_D", "FightD_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "FIGHT_D", "FightD_M", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "FIGHT_D", "HitD_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "FIGHT_D", "HitD_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "FIGHT_D", "HitD_3", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animfightd [1 - 10]");
	}
	return 1;
}
CMD:animfighte(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "FIGHT_E", "FightKick", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "FIGHT_E", "FightKick_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "FIGHT_E", "Hit_fightkick", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "FIGHT_E", "Hit_fightkick_B", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animfighte [1 - 4]");
	}
	return 1;
}
CMD:animfinale(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "FINALE", "FIN_Climb_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "FINALE", "FIN_Cop1_ClimbOut2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "FINALE", "FIN_Cop1_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "FINALE", "FIN_Cop1_Stomp", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "FINALE", "FIN_Hang_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "FINALE", "FIN_Hang_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "FINALE", "FIN_Hang_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "FINALE", "FIN_Hang_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "FINALE", "FIN_Jump_On", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "FINALE", "FIN_Land_Car", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "FINALE", "FIN_Land_Die", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "FINALE", "FIN_LegsUp", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "FINALE", "FIN_LegsUp_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "FINALE", "FIN_LegsUp_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "FINALE", "FIN_LegsUp_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "FINALE", "FIN_Let_Go", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animfinale [1 - 16]");
	}
	return 1;
}
CMD:animfinale2(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "FINALE2", "FIN_Cop1_ClimbOut", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "FINALE2", "FIN_Cop1_Fall", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "FINALE2", "FIN_Cop1_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "FINALE2", "FIN_Cop1_Shot", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "FINALE2", "FIN_Cop1_Swing", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "FINALE2", "FIN_Cop2_ClimbOut", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "FINALE2", "FIN_Switch_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "FINALE2", "FIN_Switch_S", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animfinale2 [1 - 8]");
	}
	return 1;
}
CMD:animflowers(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "Flowers", "Flower_attack", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "Flowers", "Flower_attack_M", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "Flowers", "Flower_Hit", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animflowers [1 - 3]");
	}
	return 1;
}
CMD:animfood(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "FOOD", "EAT_Chicken", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "FOOD", "EAT_Pizza", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "FOOD", "EAT_Vomit_SK", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "FOOD", "FF_Dam_Bkw", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "FOOD", "FF_Dam_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "FOOD", "FF_Dam_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "FOOD", "FF_Dam_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "FOOD", "FF_Die_Bkw", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "FOOD", "FF_Die_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "FOOD", "FF_Die_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "FOOD", "FF_Die_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_Eat1", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_Eat2", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_Eat3", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_In_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_In_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_Look", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_Out_180", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_Out_L_180", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "FOOD", "FF_Sit_Out_R_180", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "FOOD", "SHP_Thank", 4.1, 0, 1, 1, 1, 1, 1);
		case 26: ApplyAnimationEx(playerid, "FOOD", "SHP_Tray_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 27: ApplyAnimationEx(playerid, "FOOD", "SHP_Tray_Lift", 4.1, 0, 1, 1, 1, 1, 1);
		case 28: ApplyAnimationEx(playerid, "FOOD", "SHP_Tray_Lift_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 29: ApplyAnimationEx(playerid, "FOOD", "SHP_Tray_Lift_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 30: ApplyAnimationEx(playerid, "FOOD", "SHP_Tray_Lift_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 31: ApplyAnimationEx(playerid, "FOOD", "SHP_Tray_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 32: ApplyAnimationEx(playerid, "FOOD", "SHP_Tray_Pose", 4.1, 0, 1, 1, 1, 1, 1);
		case 33: ApplyAnimationEx(playerid, "FOOD", "SHP_Tray_Return", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animfood [1 - 33]");
	}
	return 1;
}
CMD:animfreeweights(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "Freeweights", "gym_barbell", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "Freeweights", "gym_free_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "Freeweights", "gym_free_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "Freeweights", "gym_free_celebrate", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "Freeweights", "gym_free_down", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "Freeweights", "gym_free_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "Freeweights", "gym_free_pickup", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "Freeweights", "gym_free_putdown", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "Freeweights", "gym_free_up_smooth", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animfw [1 - 9]");
	}
	return 1;
}
CMD:animgangs(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "GANGS", "DEALER_DEAL", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "GANGS", "DEALER_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "GANGS", "drnkbr_prtl", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "GANGS", "drnkbr_prtl_F", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "GANGS", "DRUGS_BUY", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "GANGS", "hndshkaa", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "GANGS", "hndshkba", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "GANGS", "hndshkca", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "GANGS", "hndshkcb", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "GANGS", "hndshkda", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "GANGS", "hndshkea", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "GANGS", "hndshkfa", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "GANGS", "hndshkfa_swt", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "GANGS", "Invite_No", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "GANGS", "Invite_Yes", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "GANGS", "leanIDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "GANGS", "leanIN", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "GANGS", "leanOUT", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkA", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkB", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkCt", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkD", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkE", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkF", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkG", 4.1, 0, 1, 1, 1, 1, 1);
		case 26: ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkH", 4.1, 0, 1, 1, 1, 1, 1);
		case 27: ApplyAnimationEx(playerid, "GANGS", "prtial_hndshk_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 28: ApplyAnimationEx(playerid, "GANGS", "prtial_hndshk_biz_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 29: ApplyAnimationEx(playerid, "GANGS", "shake_cara", 4.1, 0, 1, 1, 1, 1, 1);
		case 30: ApplyAnimationEx(playerid, "GANGS", "shake_carK", 4.1, 0, 1, 1, 1, 1, 1);
		case 31: ApplyAnimationEx(playerid, "GANGS", "shake_carSH", 4.1, 0, 1, 1, 1, 1, 1);
		case 32: ApplyAnimationEx(playerid, "GANGS", "smkcig_prtl", 4.1, 0, 1, 1, 1, 1, 1);
		case 33: ApplyAnimationEx(playerid, "GANGS", "smkcig_prtl_F", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animgangs [1 - 33]");
	}
	return 1;
}
CMD:animghands(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "GHANDS", "gsign1", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "GHANDS", "gsign1LH", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "GHANDS", "gsign2", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "GHANDS", "gsign2LH", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "GHANDS", "gsign3", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "GHANDS", "gsign3LH", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "GHANDS", "gsign4", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "GHANDS", "gsign4LH", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "GHANDS", "gsign5", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "GHANDS", "gsign5LH", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "GHANDS", "LHGsign1", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "GHANDS", "LHGsign2", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "GHANDS", "LHGsign3", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "GHANDS", "LHGsign4", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "GHANDS", "LHGsign5", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "GHANDS", "RHGsign1", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "GHANDS", "RHGsign2", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "GHANDS", "RHGsign3", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "GHANDS", "RHGsign4", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "GHANDS", "RHGsign5", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animghands [1 - 20]");
	}
	return 1;
}
CMD:animghettodb(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "GHETTO_DB", "GDB_Car2_PLY", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "GHETTO_DB", "GDB_Car2_SMO", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "GHETTO_DB", "GDB_Car2_SWE", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "GHETTO_DB", "GDB_Car_PLY", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "GHETTO_DB", "GDB_Car_RYD", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "GHETTO_DB", "GDB_Car_SMO", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "GHETTO_DB", "GDB_Car_SWE", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animghettodb [1 - 7]");
	}
	return 1;
}
CMD:animgraffity(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "GRAFFITI", "graffiti_Chkout", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "GRAFFITI", "spraycan_fire", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animgraffity [1 - 2]");
	}
	return 1;
}
CMD:animgraveyard(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "GRAVEYARD", "mrnF_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "GRAVEYARD", "mrnM_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "GRAVEYARD", "prst_loopa", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animgreya [1 - 3]");
	}
	return 1;
}
CMD:animgren(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "GRENADE", "WEAPON_start_throw", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "GRENADE", "WEAPON_throw", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animgren [1 - 3]");
	}
	return 1;
}
CMD:animgym(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "GYMNASIUM", "GYMshadowbox", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_bike_celebrate", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_bike_fast", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_bike_faster", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_bike_getoff", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_bike_geton", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_bike_pedal", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_bike_slow", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_bike_still", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_jog_falloff", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_shadowbox", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_tread_celebrate", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_tread_falloff", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_tread_getoff", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_tread_geton", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_tread_jog", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_tread_sprint", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_tread_tired", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_tread_walk", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "GYMNASIUM", "gym_walk_falloff", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "GYMNASIUM", "Pedals_fast", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "GYMNASIUM", "Pedals_med", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "GYMNASIUM", "Pedals_slow", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "GYMNASIUM", "Pedals_still", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animgym [1 - 24]");
	}
	return 1;
}
CMD:animhaircuts(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Beard_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Buy", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Cut", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Cut_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Cut_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Hair_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Hair_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Sit_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Sit_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Sit_Out", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animhaircut [1 - 13]");
	}
	return 1;
}
CMD:animheists(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "HEIST9", "CAS_G2_GasKO", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "HEIST9", "swt_wllpk_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "HEIST9", "swt_wllpk_L_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "HEIST9", "swt_wllpk_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "HEIST9", "swt_wllpk_R_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "HEIST9", "swt_wllshoot_in_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "HEIST9", "swt_wllshoot_in_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "HEIST9", "swt_wllshoot_out_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "HEIST9", "swt_wllshoot_out_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animheist [1 - 10]");
	}
	return 1;
}
CMD:animinthouse(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "INT_HOUSE", "BED_In_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "INT_HOUSE", "BED_In_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "INT_HOUSE", "BED_Loop_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "INT_HOUSE", "BED_Loop_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "INT_HOUSE", "BED_Out_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "INT_HOUSE", "BED_Out_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "INT_HOUSE", "LOU_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "INT_HOUSE", "LOU_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "INT_HOUSE", "LOU_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animinthouse [1 - 10]");
	}
	return 1;
}
CMD:animintoffice(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "INT_OFFICE", "FF_Dam_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_2Idle_180", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Bored_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Crash", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Drink", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Idle_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Read", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Type_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Watch", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animintoffice [1 - 10]");
	}
	return 1;
}
CMD:animintshop(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "INT_SHOP", "shop_cashier", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "INT_SHOP", "shop_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "INT_SHOP", "shop_lookA", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "INT_SHOP", "shop_lookB", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "INT_SHOP", "shop_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "INT_SHOP", "shop_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "INT_SHOP", "shop_pay", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "INT_SHOP", "shop_shelf", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animintshop [1 - 8]");
	}
	return 1;
}
CMD:animjst(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "JST_BUISNESS", "girl_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "JST_BUISNESS", "girl_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "JST_BUISNESS", "player_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "JST_BUISNESS", "smoke_01", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animjst [1 - 4]");
	}
	return 1;
}
CMD:animkart(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "KART", "KART_getin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "KART", "KART_getin_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "KART", "KART_getout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "KART", "KART_getout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animkart [1 - 4]");
	}
	return 1;
}
CMD:animkissing(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "KISSING", "BD_GF_Wave", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "KISSING", "gfwave2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "KISSING", "GF_CarArgue_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "KISSING", "GF_CarArgue_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "KISSING", "GF_CarSpot", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "KISSING", "GF_StreetArgue_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "KISSING", "GF_StreetArgue_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "KISSING", "gift_get", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "KISSING", "gift_give", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "KISSING", "Grlfrd_Kiss_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "KISSING", "Grlfrd_Kiss_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "KISSING", "Grlfrd_Kiss_03", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "KISSING", "Playa_Kiss_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "KISSING", "Playa_Kiss_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "KISSING", "Playa_Kiss_03", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animkissing [1 - 15]");
	}
	return 1;
}
CMD:animknife(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "KNIFE", "KILL_Knife_Ped_Damage", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "KNIFE", "KILL_Knife_Ped_Die", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "KNIFE", "KILL_Knife_Player", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "KNIFE", "KILL_Partial", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "KNIFE", "knife_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "KNIFE", "knife_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "KNIFE", "knife_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "KNIFE", "knife_4", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "KNIFE", "knife_block", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "KNIFE", "Knife_G", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "KNIFE", "knife_hit_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "KNIFE", "knife_hit_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "KNIFE", "knife_hit_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "KNIFE", "knife_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "KNIFE", "knife_part", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "KNIFE", "WEAPON_knifeidle", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animknife [1 - 16]");
	}
	return 1;
}
CMD:animlapdan1(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "LAPDAN1", "LAPDAN_D", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "LAPDAN1", "LAPDAN_P", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animlapdan1 [1 - 2]");
	}
	return 1;
}
CMD:animlapdan2(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "LAPDAN2", "LAPDAN_D", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "LAPDAN2", "LAPDAN_P", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animlapdan2 [1 - 2]");
	}
	return 1;
}
CMD:animlapdan3(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "LAPDAN3", "LAPDAN_D", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "LAPDAN3", "LAPDAN_P", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animlapdan3 [1 - 2]");
	}
	return 1;
}
CMD:animlowrider(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "LOWRIDER", "F_smklean_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_bdbnce", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_hair", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_hurry", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_idleloop", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_idle_to_l0", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l0_bnce", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l0_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l0_to_l1", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l12_to_l0", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l1_bnce", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l1_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l1_to_l2", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l2_bnce", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l2_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l2_to_l3", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l345_to_l1", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l3_bnce", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l3_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l3_to_l4", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l4_bnce", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l4_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l4_to_l5", 4.1, 0, 1, 1, 1, 1, 1);
                case 24: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l5_bnce", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l5_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 26: ApplyAnimationEx(playerid, "LOWRIDER", "M_smklean_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 27: ApplyAnimationEx(playerid, "LOWRIDER", "M_smkstnd_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 28: ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkB", 4.1, 0, 1, 1, 1, 1, 1);
		case 29: ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkC", 4.1, 0, 1, 1, 1, 1, 1);
		case 30: ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkD", 4.1, 0, 1, 1, 1, 1, 1);
		case 31: ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkE", 4.1, 0, 1, 1, 1, 1, 1);
		case 32: ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkF", 4.1, 0, 1, 1, 1, 1, 1);
		case 33: ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkG", 4.1, 0, 1, 1, 1, 1, 1);
		case 34: ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkH", 4.1, 0, 1, 1, 1, 1, 1);
		case 35: ApplyAnimationEx(playerid, "LOWRIDER", "RAP_A_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 36: ApplyAnimationEx(playerid, "LOWRIDER", "RAP_B_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 37: ApplyAnimationEx(playerid, "LOWRIDER", "RAP_C_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 38: ApplyAnimationEx(playerid, "LOWRIDER", "Sit_relaxed", 4.1, 0, 1, 1, 1, 1, 1);
		case 39: ApplyAnimationEx(playerid, "LOWRIDER", "Tap_hand", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animlowrider [1 - 39]");
	}
	return 1;
}
CMD:animchase(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "MD_CHASE", "Carhit_Hangon", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "MD_CHASE", "Carhit_Tumble", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "MD_CHASE", "donutdrop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "MD_CHASE", "Fen_Choppa_L1", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "MD_CHASE", "Fen_Choppa_L2", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "MD_CHASE", "Fen_Choppa_L3", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "MD_CHASE", "Fen_Choppa_R1", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "MD_CHASE", "Fen_Choppa_R2", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "MD_CHASE", "Fen_Choppa_R3", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "MD_CHASE", "Hangon_Stun_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "MD_CHASE", "Hangon_Stun_Turn", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_2_HANG", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Jmp_BL", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Jmp_F", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Lnd_BL", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Lnd_Die_BL", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Lnd_Die_F", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Lnd_F", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Lnd_Roll", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Lnd_Roll_F", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Punch", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Punch_F", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Shot_F", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "MD_CHASE", "MD_HANG_Lnd_Roll", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "MD_CHASE", "MD_HANG_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animmdchase [1 - 25]");
	}
	return 1;
}
CMD:animmdend(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "MD_END", "END_SC1_PLY", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "MD_END", "END_SC1_RYD", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "MD_END", "END_SC1_SMO", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "MD_END", "END_SC1_SWE", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "MD_END", "END_SC2_PLY", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "MD_END", "END_SC2_RYD", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "MD_END", "END_SC2_SMO", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "MD_END", "END_SC2_SWE", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animmddend [1 - 8]");
	}
	return 1;
}
CMD:animms(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "MISC", "bitchslap", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "MISC", "BMX_celebrate", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "MISC", "BMX_comeon", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "MISC", "bmx_idleloop_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "MISC", "bmx_idleloop_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "MISC", "bmx_talkleft_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "MISC", "bmx_talkleft_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "MISC", "bmx_talkleft_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "MISC", "bmx_talkright_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "MISC", "bmx_talkright_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "MISC", "bmx_talkright_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "MISC", "bng_wndw", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "MISC", "bng_wndw_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "MISC", "Case_pickup", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "MISC", "door_jet", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "MISC", "GRAB_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "MISC", "GRAB_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "MISC", "Hiker_Pose", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "MISC", "Hiker_Pose_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "MISC", "Idle_Chat_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "MISC", "KAT_Throw_K", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "MISC", "KAT_Throw_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "MISC", "KAT_Throw_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "MISC", "PASS_Rifle_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "MISC", "PASS_Rifle_Ped", 4.1, 0, 1, 1, 1, 1, 1);
		case 26: ApplyAnimationEx(playerid, "MISC", "PASS_Rifle_Ply", 4.1, 0, 1, 1, 1, 1, 1);
		case 27: ApplyAnimationEx(playerid, "MISC", "pickup_box", 4.1, 0, 1, 1, 1, 1, 1);
		case 28: ApplyAnimationEx(playerid, "MISC", "Plane_door", 4.1, 0, 1, 1, 1, 1, 1);
		case 29: ApplyAnimationEx(playerid, "MISC", "Plane_exit", 4.1, 0, 1, 1, 1, 1, 1);
		case 30: ApplyAnimationEx(playerid, "MISC", "Plane_hijack", 4.1, 0, 1, 1, 1, 1, 1);
		case 31: ApplyAnimationEx(playerid, "MISC", "Plunger_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 32: ApplyAnimationEx(playerid, "MISC", "Plyrlean_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 33: ApplyAnimationEx(playerid, "MISC", "plyr_shkhead", 4.1, 0, 1, 1, 1, 1, 1);
		case 34: ApplyAnimationEx(playerid, "MISC", "Run_Dive", 4.1, 0, 1, 1, 1, 1, 1);
		case 35: ApplyAnimationEx(playerid, "MISC", "Scratchballs_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 36: ApplyAnimationEx(playerid, "MISC", "SEAT_LR", 4.1, 0, 1, 1, 1, 1, 1);
		case 37: ApplyAnimationEx(playerid, "MISC", "Seat_talk_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 38: ApplyAnimationEx(playerid, "MISC", "Seat_talk_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 39: ApplyAnimationEx(playerid, "MISC", "SEAT_watch", 4.1, 0, 1, 1, 1, 1, 1);
		case 40: ApplyAnimationEx(playerid, "MISC", "smalplane_door", 4.1, 0, 1, 1, 1, 1, 1);
		case 41: ApplyAnimationEx(playerid, "MISC", "smlplane_door", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animms [1 - 41]");
	}
	return 1;
}
CMD:animmtb(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "MTB", "MTB_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "MTB", "MTB_bunnyhop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "MTB", "MTB_drivebyFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "MTB", "MTB_driveby_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "MTB", "MTB_driveby_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "MTB", "MTB_fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "MTB", "MTB_getoffBACK", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "MTB", "MTB_pushes", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "MTB", "MTB_getoffLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "MTB", "MTB_getoffRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "MTB", "MTB_jumponL", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "MTB", "MTB_jumponR", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "MTB", "MTB_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "MTB", "MTB_pedal", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "MTB", "MTB_Ride", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "MTB", "MTB_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "MTB", "MTB_sprint", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "MTB", "MTB_still", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animmtb [1 - 18]");
	}
	return 1;
}
CMD:animmuscular(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "MUSCULAR", "MscleWalkst_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "MUSCULAR", "MscleWalkst_Csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "MUSCULAR", "Mscle_rckt_run", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "MUSCULAR", "Mscle_rckt_walkst", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "MUSCULAR", "Mscle_run_Csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleIdle", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleIdle_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleIdle_Csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleIdle_rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleRun", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleRun_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleSprint", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleWalk", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleWalkstart", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleWalk_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "MUSCULAR", "Musclewalk_Csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "MUSCULAR", "Musclewalk_rocket", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animmusculcar [1 - 17]");
	}
	return 1;
}
CMD:animnevada(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "NEVADA", "NEVADA_getin", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "NEVADA", "NEVADA_getout", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animnevada [1 - 2]");
	}
	return 1;
}
CMD:animonlookers(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "ON_LOOKERS", "lkaround_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "ON_LOOKERS", "lkaround_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "ON_LOOKERS", "lkaround_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "ON_LOOKERS", "lkup_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "ON_LOOKERS", "lkup_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "ON_LOOKERS", "lkup_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "ON_LOOKERS", "lkup_point", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_cower", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_hide", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_point", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_shout", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "ON_LOOKERS", "Pointup_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "ON_LOOKERS", "Pointup_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "ON_LOOKERS", "Pointup_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "ON_LOOKERS", "Pointup_shout", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "ON_LOOKERS", "point_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "ON_LOOKERS", "point_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "ON_LOOKERS", "point_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "ON_LOOKERS", "shout_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "ON_LOOKERS", "shout_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "ON_LOOKERS", "shout_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "ON_LOOKERS", "shout_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 26: ApplyAnimationEx(playerid, "ON_LOOKERS", "shout_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 27: ApplyAnimationEx(playerid, "ON_LOOKERS", "wave_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 28: ApplyAnimationEx(playerid, "ON_LOOKERS", "wave_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 29: ApplyAnimationEx(playerid, "ON_LOOKERS", "wave_out", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animlookers [1 - 29]");
	}
	return 1;
}
CMD:animotb(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "OTB", "betslp_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "OTB", "betslp_lkabt", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "OTB", "betslp_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "OTB", "betslp_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "OTB", "betslp_tnk", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "OTB", "wtchrace_cmon", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "OTB", "wtchrace_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "OTB", "wtchrace_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "OTB", "wtchrace_lose", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "OTB", "wtchrace_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "OTB", "wtchrace_win", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animotb [1 - 11]");
	}
	return 1;
}
CMD:animparachute(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "PARACHUTE", "FALL_skyDive", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "PARACHUTE", "FALL_SkyDive_Accel", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "PARACHUTE", "FALL_skyDive_DIE", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "PARACHUTE", "FALL_SkyDive_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "PARACHUTE", "FALL_SkyDive_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_decel", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_decel_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_float", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_float_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_Land", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_Land_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_Land_Water", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_Land_Water_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_open", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_open_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_Rip_Land_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_Rip_Loop_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_Rip_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_steerL", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_steerL_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_steerR", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "PARACHUTE", "PARA_steerR_O", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animparachute [1 - 22]");
	}
	return 1;
}
CMD:animpark(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "PARK", "Tai_Chi_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "PARK", "Tai_Chi_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "PARK", "Tai_Chi_Out", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animpark [1 - 3]");
	}
	return 1;
}
CMD:animpaulnmac(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "PAULNMAC", "Piss_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "PAULNMAC", "Piss_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "PAULNMAC", "Piss_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "PAULNMAC", "PnM_Argue1_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "PAULNMAC", "PnM_Argue1_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "PAULNMAC", "PnM_Argue2_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "PAULNMAC", "PnM_Argue2_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "PAULNMAC", "PnM_Loop_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "PAULNMAC", "PnM_Loop_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "PAULNMAC", "wank_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "PAULNMAC", "wank_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "PAULNMAC", "wank_out", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animpaulnmac [1 - 12]");
	}
	return 1;
}
CMD:animped(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "PED", "abseil", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "PED", "ATM", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "PED", "BIKE_elbowL", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "PED", "BIKE_elbowR", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "PED", "BIKE_fallR", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "PED", "BIKE_fall_off", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "PED", "BIKE_pickupL", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "PED", "BIKE_pickupR", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "PED", "BIKE_pullupL", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "PED", "BIKE_pullupR", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "PED", "bomber", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "PED", "CAR_alignHI_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "PED", "CAR_alignHI_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "PED", "CAR_align_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "PED", "CAR_align_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "PED", "CAR_closedoorL_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "PED", "CAR_closedoorL_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "PED", "CAR_closedoor_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "PED", "CAR_closedoor_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "PED", "CAR_close_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "PED", "CAR_close_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "PED", "CAR_crawloutRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "PED", "CAR_dead_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "PED", "CAR_dead_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 26: ApplyAnimationEx(playerid, "PED", "CAR_doorlocked_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 27: ApplyAnimationEx(playerid, "PED", "CAR_doorlocked_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 28: ApplyAnimationEx(playerid, "PED", "CAR_fallout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 29: ApplyAnimationEx(playerid, "PED", "CAR_fallout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 30: ApplyAnimationEx(playerid, "PED", "CAR_getinL_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 31: ApplyAnimationEx(playerid, "PED", "CAR_getinL_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 32: ApplyAnimationEx(playerid, "PED", "CAR_getin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 33: ApplyAnimationEx(playerid, "PED", "CAR_getin_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 34: ApplyAnimationEx(playerid, "PED", "CAR_getoutL_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 35: ApplyAnimationEx(playerid, "PED", "CAR_getoutL_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 36: ApplyAnimationEx(playerid, "PED", "CAR_getout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 37: ApplyAnimationEx(playerid, "PED", "CAR_getout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 38: ApplyAnimationEx(playerid, "PED", "car_hookertalk", 4.1, 0, 1, 1, 1, 1, 1);
		case 39: ApplyAnimationEx(playerid, "PED", "CAR_jackedLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 40: ApplyAnimationEx(playerid, "PED", "CAR_jackedRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 41: ApplyAnimationEx(playerid, "PED", "CAR_jumpin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 42: ApplyAnimationEx(playerid, "PED", "CAR_LB", 4.1, 0, 1, 1, 1, 1, 1);
		case 43: ApplyAnimationEx(playerid, "PED", "CAR_LB_pro", 4.1, 0, 1, 1, 1, 1, 1);
		case 44: ApplyAnimationEx(playerid, "PED", "CAR_LB_weak", 4.1, 0, 1, 1, 1, 1, 1);
		case 45: ApplyAnimationEx(playerid, "PED", "CAR_LjackedLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 46: ApplyAnimationEx(playerid, "PED", "CAR_LjackedRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 47: ApplyAnimationEx(playerid, "PED", "CAR_Lshuffle_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 48: ApplyAnimationEx(playerid, "PED", "CAR_Lsit", 4.1, 0, 1, 1, 1, 1, 1);
		case 49: ApplyAnimationEx(playerid, "PED", "CAR_open_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 50: ApplyAnimationEx(playerid, "PED", "CAR_open_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 51: ApplyAnimationEx(playerid, "PED", "CAR_pulloutL_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 52: ApplyAnimationEx(playerid, "PED", "CAR_pulloutL_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 53: ApplyAnimationEx(playerid, "PED", "CAR_pullout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 54: ApplyAnimationEx(playerid, "PED", "CAR_pullout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 55: ApplyAnimationEx(playerid, "PED", "CAR_Qjacked", 4.1, 0, 1, 1, 1, 1, 1);
		case 56: ApplyAnimationEx(playerid, "PED", "CAR_rolldoor", 4.1, 0, 1, 1, 1, 1, 1);
		case 57: ApplyAnimationEx(playerid, "PED", "CAR_rolldoorLO", 4.1, 0, 1, 1, 1, 1, 1);
		case 58: ApplyAnimationEx(playerid, "PED", "CAR_rollout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 59: ApplyAnimationEx(playerid, "PED", "CAR_rollout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 60: ApplyAnimationEx(playerid, "PED", "CAR_shuffle_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 61: ApplyAnimationEx(playerid, "PED", "CAR_sit", 4.1, 0, 1, 1, 1, 1, 1);
		case 62: ApplyAnimationEx(playerid, "PED", "CAR_sitp", 4.1, 0, 1, 1, 1, 1, 1);
		case 63: ApplyAnimationEx(playerid, "PED", "CAR_sitpLO", 4.1, 0, 1, 1, 1, 1, 1);
		case 64: ApplyAnimationEx(playerid, "PED", "CAR_sit_pro", 4.1, 0, 1, 1, 1, 1, 1);
		case 65: ApplyAnimationEx(playerid, "PED", "CAR_sit_weak", 4.1, 0, 1, 1, 1, 1, 1);
		case 66: ApplyAnimationEx(playerid, "PED", "CAR_tune_radio", 4.1, 0, 1, 1, 1, 1, 1);
		case 67: ApplyAnimationEx(playerid, "PED", "CLIMB_idle", 4.1, 0, 1, 1, 1, 1, 1);
		case 68: ApplyAnimationEx(playerid, "PED", "CLIMB_jump", 4.1, 0, 1, 1, 1, 1, 1);
		case 69: ApplyAnimationEx(playerid, "PED", "CLIMB_jump2fall", 4.1, 0, 1, 1, 1, 1, 1);
		case 70: ApplyAnimationEx(playerid, "PED", "CLIMB_jump_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 71: ApplyAnimationEx(playerid, "PED", "CLIMB_Pull", 4.1, 0, 1, 1, 1, 1, 1);
		case 72: ApplyAnimationEx(playerid, "PED", "CLIMB_Stand", 4.1, 0, 1, 1, 1, 1, 1);
		case 73: ApplyAnimationEx(playerid, "PED", "CLIMB_Stand_finish", 4.1, 0, 1, 1, 1, 1, 1);
		case 74: ApplyAnimationEx(playerid, "PED", "cower", 4.1, 0, 1, 1, 1, 1, 1);
		case 75: ApplyAnimationEx(playerid, "PED", "Crouch_Roll_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 76: ApplyAnimationEx(playerid, "PED", "Crouch_Roll_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 77: ApplyAnimationEx(playerid, "PED", "DAM_armL_frmBK", 4.1, 0, 1, 1, 1, 1, 1);
		case 78: ApplyAnimationEx(playerid, "PED", "DAM_armL_frmFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 79: ApplyAnimationEx(playerid, "PED", "DAM_armL_frmLT", 4.1, 0, 1, 1, 1, 1, 1);
		case 80: ApplyAnimationEx(playerid, "PED", "DAM_armR_frmBK", 4.1, 0, 1, 1, 1, 1, 1);
		case 81: ApplyAnimationEx(playerid, "PED", "DAM_armR_frmFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 82: ApplyAnimationEx(playerid, "PED", "DAM_armR_frmRT", 4.1, 0, 1, 1, 1, 1, 1);
		case 83: ApplyAnimationEx(playerid, "PED", "DAM_LegL_frmBK", 4.1, 0, 1, 1, 1, 1, 1);
		case 84: ApplyAnimationEx(playerid, "PED", "DAM_LegL_frmFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 85: ApplyAnimationEx(playerid, "PED", "DAM_LegL_frmLT", 4.1, 0, 1, 1, 1, 1, 1);
		case 86: ApplyAnimationEx(playerid, "PED", "DAM_LegR_frmBK", 4.1, 0, 1, 1, 1, 1, 1);
		case 87: ApplyAnimationEx(playerid, "PED", "DAM_LegR_frmFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 88: ApplyAnimationEx(playerid, "PED", "DAM_LegR_frmRT", 4.1, 0, 1, 1, 1, 1, 1);
		case 89: ApplyAnimationEx(playerid, "PED", "DAM_stomach_frmBK", 4.1, 0, 1, 1, 1, 1, 1);
		case 90: ApplyAnimationEx(playerid, "PED", "DAM_stomach_frmFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 91: ApplyAnimationEx(playerid, "PED", "DAM_stomach_frmLT", 4.1, 0, 1, 1, 1, 1, 1);
		case 92: ApplyAnimationEx(playerid, "PED", "DAM_stomach_frmRT", 4.1, 0, 1, 1, 1, 1, 1);
		case 93: ApplyAnimationEx(playerid, "PED", "DOOR_LHinge_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 94: ApplyAnimationEx(playerid, "PED", "DOOR_RHinge_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 95: ApplyAnimationEx(playerid, "PED", "DrivebyL_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 96: ApplyAnimationEx(playerid, "PED", "DrivebyL_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 97: ApplyAnimationEx(playerid, "PED", "Driveby_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 98: ApplyAnimationEx(playerid, "PED", "Driveby_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 99: ApplyAnimationEx(playerid, "PED", "DRIVE_BOAT", 4.1, 0, 1, 1, 1, 1, 1);
		case 100: ApplyAnimationEx(playerid, "PED", "DRIVE_BOAT_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 101: ApplyAnimationEx(playerid, "PED", "DRIVE_BOAT_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 102: ApplyAnimationEx(playerid, "PED", "DRIVE_BOAT_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 103: ApplyAnimationEx(playerid, "PED", "Drive_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 104: ApplyAnimationEx(playerid, "PED", "Drive_LO_l", 4.1, 0, 1, 1, 1, 1, 1);
		case 105: ApplyAnimationEx(playerid, "PED", "Drive_LO_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 106: ApplyAnimationEx(playerid, "PED", "Drive_L_pro", 4.1, 0, 1, 1, 1, 1, 1);
		case 107: ApplyAnimationEx(playerid, "PED", "Drive_L_pro_slow", 4.1, 0, 1, 1, 1, 1, 1);
		case 108: ApplyAnimationEx(playerid, "PED", "Drive_L_slow", 4.1, 0, 1, 1, 1, 1, 1);
		case 109: ApplyAnimationEx(playerid, "PED", "Drive_L_weak", 4.1, 0, 1, 1, 1, 1, 1);
		case 110: ApplyAnimationEx(playerid, "PED", "Drive_L_weak_slow", 4.1, 0, 1, 1, 1, 1, 1);
		case 111: ApplyAnimationEx(playerid, "PED", "Drive_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 112: ApplyAnimationEx(playerid, "PED", "Drive_R_pro", 4.1, 0, 1, 1, 1, 1, 1);
		case 113: ApplyAnimationEx(playerid, "PED", "Drive_R_pro_slow", 4.1, 0, 1, 1, 1, 1, 1);
		case 114: ApplyAnimationEx(playerid, "PED", "Drive_R_slow", 4.1, 0, 1, 1, 1, 1, 1);
		case 115: ApplyAnimationEx(playerid, "PED", "Drive_R_weak", 4.1, 0, 1, 1, 1, 1, 1);
		case 116: ApplyAnimationEx(playerid, "PED", "Drive_R_weak_slow", 4.1, 0, 1, 1, 1, 1, 1);
		case 117: ApplyAnimationEx(playerid, "PED", "Drive_truck", 4.1, 0, 1, 1, 1, 1, 1);
		case 118: ApplyAnimationEx(playerid, "PED", "DRIVE_truck_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 119: ApplyAnimationEx(playerid, "PED", "DRIVE_truck_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 120: ApplyAnimationEx(playerid, "PED", "DRIVE_truck_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 121: ApplyAnimationEx(playerid, "PED", "Drown", 4.1, 0, 1, 1, 1, 1, 1);
		case 122: ApplyAnimationEx(playerid, "PED", "DUCK_cower", 4.1, 0, 1, 1, 1, 1, 1);
		case 123: ApplyAnimationEx(playerid, "PED", "endchat_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 124: ApplyAnimationEx(playerid, "PED", "endchat_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 125: ApplyAnimationEx(playerid, "PED", "endchat_03", 4.1, 0, 1, 1, 1, 1, 1);
		case 126: ApplyAnimationEx(playerid, "PED", "EV_dive", 4.1, 0, 1, 1, 1, 1, 1);
		case 127: ApplyAnimationEx(playerid, "PED", "EV_step", 4.1, 0, 1, 1, 1, 1, 1);
		case 128: ApplyAnimationEx(playerid, "PED", "facanger", 4.1, 0, 1, 1, 1, 1, 1);
		case 129: ApplyAnimationEx(playerid, "PED", "facanger", 4.1, 0, 1, 1, 1, 1, 1);
		case 130: ApplyAnimationEx(playerid, "PED", "facgum", 4.1, 0, 1, 1, 1, 1, 1);
		case 131: ApplyAnimationEx(playerid, "PED", "facsurp", 4.1, 0, 1, 1, 1, 1, 1);
		case 132: ApplyAnimationEx(playerid, "PED", "facsurpm", 4.1, 0, 1, 1, 1, 1, 1);
		case 133: ApplyAnimationEx(playerid, "PED", "factalk", 4.1, 0, 1, 1, 1, 1, 1);
		case 134: ApplyAnimationEx(playerid, "PED", "facurios", 4.1, 0, 1, 1, 1, 1, 1);
		case 135: ApplyAnimationEx(playerid, "PED", "FALL_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 136: ApplyAnimationEx(playerid, "PED", "FALL_collapse", 4.1, 0, 1, 1, 1, 1, 1);
		case 137: ApplyAnimationEx(playerid, "PED", "FALL_fall", 4.1, 0, 1, 1, 1, 1, 1);
		case 138: ApplyAnimationEx(playerid, "PED", "FALL_front", 4.1, 0, 1, 1, 1, 1, 1);
		case 139: ApplyAnimationEx(playerid, "PED", "FALL_glide", 4.1, 0, 1, 1, 1, 1, 1);
		case 140: ApplyAnimationEx(playerid, "PED", "FALL_land", 4.1, 0, 1, 1, 1, 1, 1);
		case 141: ApplyAnimationEx(playerid, "PED", "FALL_skyDive", 4.1, 0, 1, 1, 1, 1, 1);
		case 142: ApplyAnimationEx(playerid, "PED", "Fight2Idle", 4.1, 0, 1, 1, 1, 1, 1);
		case 143: ApplyAnimationEx(playerid, "PED", "FightA_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 144: ApplyAnimationEx(playerid, "PED", "FightA_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 145: ApplyAnimationEx(playerid, "PED", "FightA_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 146: ApplyAnimationEx(playerid, "PED", "FightA_block", 4.1, 0, 1, 1, 1, 1, 1);
		case 147: ApplyAnimationEx(playerid, "PED", "FightA_G", 4.1, 0, 1, 1, 1, 1, 1);
		case 148: ApplyAnimationEx(playerid, "PED", "FightA_M", 4.1, 0, 1, 1, 1, 1, 1);
		case 149: ApplyAnimationEx(playerid, "PED", "FIGHTIDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 150: ApplyAnimationEx(playerid, "PED", "FightShB", 4.1, 0, 1, 1, 1, 1, 1);
		case 151: ApplyAnimationEx(playerid, "PED", "FightShF", 4.1, 0, 1, 1, 1, 1, 1);
		case 152: ApplyAnimationEx(playerid, "PED", "FightSh_BWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 153: ApplyAnimationEx(playerid, "PED", "FightSh_FWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 154: ApplyAnimationEx(playerid, "PED", "FightSh_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 155: ApplyAnimationEx(playerid, "PED", "FightSh_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 156: ApplyAnimationEx(playerid, "PED", "flee_lkaround_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 157: ApplyAnimationEx(playerid, "PED", "FLOOR_hit", 4.1, 0, 1, 1, 1, 1, 1);
		case 158: ApplyAnimationEx(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 1, 1);
		case 159: ApplyAnimationEx(playerid, "PED", "fucku", 4.1, 0, 1, 1, 1, 1, 1);
		case 160: ApplyAnimationEx(playerid, "PED", "gang_gunstand", 4.1, 0, 1, 1, 1, 1, 1);
		case 161: ApplyAnimationEx(playerid, "PED", "gas_cwr", 4.1, 0, 1, 1, 1, 1, 1);
		case 162: ApplyAnimationEx(playerid, "PED", "getup", 4.1, 0, 1, 1, 1, 1, 1);
		case 163: ApplyAnimationEx(playerid, "PED", "getup_front", 4.1, 0, 1, 1, 1, 1, 1);
		case 164: ApplyAnimationEx(playerid, "PED", "gum_eat", 4.1, 0, 1, 1, 1, 1, 1);
		case 165: ApplyAnimationEx(playerid, "PED", "GunCrouchBwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 166: ApplyAnimationEx(playerid, "PED", "GunCrouchFwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 167: ApplyAnimationEx(playerid, "PED", "GunMove_BWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 168: ApplyAnimationEx(playerid, "PED", "GunMove_FWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 169: ApplyAnimationEx(playerid, "PED", "GunMove_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 170: ApplyAnimationEx(playerid, "PED", "GunMove_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 171: ApplyAnimationEx(playerid, "PED", "Gun_2_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 172: ApplyAnimationEx(playerid, "PED", "GUN_BUTT", 4.1, 0, 1, 1, 1, 1, 1);
		case 173: ApplyAnimationEx(playerid, "PED", "GUN_BUTT_crouch", 4.1, 0, 1, 1, 1, 1, 1);
		case 174: ApplyAnimationEx(playerid, "PED", "Gun_stand", 4.1, 0, 1, 1, 1, 1, 1);
		case 175: ApplyAnimationEx(playerid, "PED", "handscower", 4.1, 0, 1, 1, 1, 1, 1);
		case 176: ApplyAnimationEx(playerid, "PED", "handsup", 4.1, 0, 1, 1, 1, 1, 1);
		case 177: ApplyAnimationEx(playerid, "PED", "HitA_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 178: ApplyAnimationEx(playerid, "PED", "HitA_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 179: ApplyAnimationEx(playerid, "PED", "HitA_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 180: ApplyAnimationEx(playerid, "PED", "HIT_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 181: ApplyAnimationEx(playerid, "PED", "HIT_behind", 4.1, 0, 1, 1, 1, 1, 1);
		case 182: ApplyAnimationEx(playerid, "PED", "HIT_front", 4.1, 0, 1, 1, 1, 1, 1);
		case 183: ApplyAnimationEx(playerid, "PED", "HIT_GUN_BUTT", 4.1, 0, 1, 1, 1, 1, 1);
		case 184: ApplyAnimationEx(playerid, "PED", "HIT_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 185: ApplyAnimationEx(playerid, "PED", "HIT_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 186: ApplyAnimationEx(playerid, "PED", "HIT_walk", 4.1, 0, 1, 1, 1, 1, 1);
		case 187: ApplyAnimationEx(playerid, "PED", "HIT_wall", 4.1, 0, 1, 1, 1, 1, 1);
		case 188: ApplyAnimationEx(playerid, "PED", "Idlestance_fat", 4.1, 0, 1, 1, 1, 1, 1);
		case 189: ApplyAnimationEx(playerid, "PED", "idlestance_old", 4.1, 0, 1, 1, 1, 1, 1);
		case 190: ApplyAnimationEx(playerid, "PED", "IDLE_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 191: ApplyAnimationEx(playerid, "PED", "IDLE_chat", 4.1, 0, 1, 1, 1, 1, 1);
		case 192: ApplyAnimationEx(playerid, "PED", "IDLE_csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 193: ApplyAnimationEx(playerid, "PED", "Idle_Gang1", 4.1, 0, 1, 1, 1, 1, 1);
		case 194: ApplyAnimationEx(playerid, "PED", "IDLE_HBHB", 4.1, 0, 1, 1, 1, 1, 1);
		case 195: ApplyAnimationEx(playerid, "PED", "IDLE_ROCKET", 4.1, 0, 1, 1, 1, 1, 1);
		case 196: ApplyAnimationEx(playerid, "PED", "IDLE_stance", 4.1, 0, 1, 1, 1, 1, 1);
		case 197: ApplyAnimationEx(playerid, "PED", "IDLE_taxi", 4.1, 0, 1, 1, 1, 1, 1);
		case 198: ApplyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 0, 1, 1, 1, 1, 1);
		case 199: ApplyAnimationEx(playerid, "PED", "Jetpack_Idle", 4.1, 0, 1, 1, 1, 1, 1);
		case 200: ApplyAnimationEx(playerid, "PED", "JOG_femaleA", 4.1, 0, 1, 1, 1, 1, 1);
		case 201: ApplyAnimationEx(playerid, "PED", "JOG_maleA", 4.1, 0, 1, 1, 1, 1, 1);
		case 202: ApplyAnimationEx(playerid, "PED", "JUMP_glide", 4.1, 0, 1, 1, 1, 1, 1);
		case 203: ApplyAnimationEx(playerid, "PED", "JUMP_land", 4.1, 0, 1, 1, 1, 1, 1);
		case 204: ApplyAnimationEx(playerid, "PED", "JUMP_launch", 4.1, 0, 1, 1, 1, 1, 1);
		case 205: ApplyAnimationEx(playerid, "PED", "JUMP_launch_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 206: ApplyAnimationEx(playerid, "PED", "KART_drive", 4.1, 0, 1, 1, 1, 1, 1);
		case 207: ApplyAnimationEx(playerid, "PED", "KART_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 208: ApplyAnimationEx(playerid, "PED", "KART_LB", 4.1, 0, 1, 1, 1, 1, 1);
		case 209: ApplyAnimationEx(playerid, "PED", "KART_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 210: ApplyAnimationEx(playerid, "PED", "KD_left", 4.1, 0, 1, 1, 1, 1, 1);
		case 211: ApplyAnimationEx(playerid, "PED", "KD_right", 4.1, 0, 1, 1, 1, 1, 1);
		case 212: ApplyAnimationEx(playerid, "PED", "KO_shot_face", 4.1, 0, 1, 1, 1, 1, 1);
		case 213: ApplyAnimationEx(playerid, "PED", "KO_shot_front", 4.1, 0, 1, 1, 1, 1, 1);
		case 214: ApplyAnimationEx(playerid, "PED", "KO_shot_stom", 4.1, 0, 1, 1, 1, 1, 1);
		case 215: ApplyAnimationEx(playerid, "PED", "KO_skid_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 216: ApplyAnimationEx(playerid, "PED", "KO_skid_front", 4.1, 0, 1, 1, 1, 1, 1);
		case 217: ApplyAnimationEx(playerid, "PED", "KO_spin_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 218: ApplyAnimationEx(playerid, "PED", "KO_spin_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 219: ApplyAnimationEx(playerid, "PED", "pass_Smoke_in_car", 4.1, 0, 1, 1, 1, 1, 1);
		case 220: ApplyAnimationEx(playerid, "PED", "phone_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 221: ApplyAnimationEx(playerid, "PED", "phone_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 222: ApplyAnimationEx(playerid, "PED", "phone_talk", 4.1, 0, 1, 1, 1, 1, 1);
		case 223: ApplyAnimationEx(playerid, "PED", "Player_Sneak", 4.1, 0, 1, 1, 1, 1, 1);
		case 224: ApplyAnimationEx(playerid, "PED", "Player_Sneak_walkstart", 4.1, 0, 1, 1, 1, 1, 1);
		case 225: ApplyAnimationEx(playerid, "PED", "roadcross", 4.1, 0, 1, 1, 1, 1, 1);
		case 226: ApplyAnimationEx(playerid, "PED", "roadcross_female", 4.1, 0, 1, 1, 1, 1, 1);
		case 227: ApplyAnimationEx(playerid, "PED", "roadcross_gang", 4.1, 0, 1, 1, 1, 1, 1);
		case 228: ApplyAnimationEx(playerid, "PED", "roadcross_old", 4.1, 0, 1, 1, 1, 1, 1);
		case 229: ApplyAnimationEx(playerid, "PED", "run_1armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 230: ApplyAnimationEx(playerid, "PED", "run_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 231: ApplyAnimationEx(playerid, "PED", "run_civi", 4.1, 0, 1, 1, 1, 1, 1);
		case 232: ApplyAnimationEx(playerid, "PED", "run_csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 233: ApplyAnimationEx(playerid, "PED", "run_fat", 4.1, 0, 1, 1, 1, 1, 1);
		case 234: ApplyAnimationEx(playerid, "PED", "run_fatold", 4.1, 0, 1, 1, 1, 1, 1);
		case 235: ApplyAnimationEx(playerid, "PED", "run_gang1", 4.1, 0, 1, 1, 1, 1, 1);
		case 236: ApplyAnimationEx(playerid, "PED", "run_left", 4.1, 0, 1, 1, 1, 1, 1);
		case 237: ApplyAnimationEx(playerid, "PED", "run_old", 4.1, 0, 1, 1, 1, 1, 1);
		case 238: ApplyAnimationEx(playerid, "PED", "run_player", 4.1, 0, 1, 1, 1, 1, 1);
		case 239: ApplyAnimationEx(playerid, "PED", "run_right", 4.1, 0, 1, 1, 1, 1, 1);
		case 240: ApplyAnimationEx(playerid, "PED", "run_rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 241: ApplyAnimationEx(playerid, "PED", "Run_stop", 4.1, 0, 1, 1, 1, 1, 1);
		case 242: ApplyAnimationEx(playerid, "PED", "Run_stopR", 4.1, 0, 1, 1, 1, 1, 1);
		case 243: ApplyAnimationEx(playerid, "PED", "Run_Wuzi", 4.1, 0, 1, 1, 1, 1, 1);
		case 244: ApplyAnimationEx(playerid, "PED", "SEAT_down", 4.1, 0, 1, 1, 1, 1, 1);
		case 245: ApplyAnimationEx(playerid, "PED", "SEAT_idle", 4.1, 0, 1, 1, 1, 1, 1);
		case 246: ApplyAnimationEx(playerid, "PED", "SEAT_up", 4.1, 0, 1, 1, 1, 1, 1);
		case 247: ApplyAnimationEx(playerid, "PED", "SHOT_leftP", 4.1, 0, 1, 1, 1, 1, 1);
		case 248: ApplyAnimationEx(playerid, "PED", "SHOT_partial", 4.1, 0, 1, 1, 1, 1, 1);
		case 249: ApplyAnimationEx(playerid, "PED", "SHOT_partial_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 250: ApplyAnimationEx(playerid, "PED", "SHOT_rightP", 4.1, 0, 1, 1, 1, 1, 1);
		case 251: ApplyAnimationEx(playerid, "PED", "Shove_Partial", 4.1, 0, 1, 1, 1, 1, 1);
		case 252: ApplyAnimationEx(playerid, "PED", "Smoke_in_car", 4.1, 0, 1, 1, 1, 1, 1);
		case 253: ApplyAnimationEx(playerid, "PED", "sprint_civi", 4.1, 0, 1, 1, 1, 1, 1);
		case 254: ApplyAnimationEx(playerid, "PED", "sprint_panic", 4.1, 0, 1, 1, 1, 1, 1);
		case 255: ApplyAnimationEx(playerid, "PED", "Sprint_Wuzi", 4.1, 0, 1, 1, 1, 1, 1);
		case 256: ApplyAnimationEx(playerid, "PED", "swat_run", 4.1, 0, 1, 1, 1, 1, 1);
		case 257: ApplyAnimationEx(playerid, "PED", "Swim_Tread", 4.1, 0, 1, 1, 1, 1, 1);
		case 258: ApplyAnimationEx(playerid, "PED", "Tap_hand", 4.1, 0, 1, 1, 1, 1, 1);
		case 259: ApplyAnimationEx(playerid, "PED", "Tap_handP", 4.1, 0, 1, 1, 1, 1, 1);
		case 260: ApplyAnimationEx(playerid, "PED", "turn_180", 4.1, 0, 1, 1, 1, 1, 1);
		case 261: ApplyAnimationEx(playerid, "PED", "Turn_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 262: ApplyAnimationEx(playerid, "PED", "Turn_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 263: ApplyAnimationEx(playerid, "PED", "WALK_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 264: ApplyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 0, 1, 1, 1, 1, 1);
		case 265: ApplyAnimationEx(playerid, "PED", "WALK_csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 266: ApplyAnimationEx(playerid, "PED", "Walk_DoorPartial", 4.1, 0, 1, 1, 1, 1, 1);
		case 267: ApplyAnimationEx(playerid, "PED", "WALK_drunk", 4.1, 0, 1, 1, 1, 1, 1);
		case 268: ApplyAnimationEx(playerid, "PED", "WALK_fat", 4.1, 0, 1, 1, 1, 1, 1);
		case 269: ApplyAnimationEx(playerid, "PED", "WALK_fatold", 4.1, 0, 1, 1, 1, 1, 1);
		case 270: ApplyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 0, 1, 1, 1, 1, 1);
		case 271: ApplyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 0, 1, 1, 1, 1, 1);
		case 272: ApplyAnimationEx(playerid, "PED", "WALK_old", 4.1, 0, 1, 1, 1, 1, 1);
		case 273: ApplyAnimationEx(playerid, "PED", "WALK_player", 4.1, 0, 1, 1, 1, 1, 1);
		case 274: ApplyAnimationEx(playerid, "PED", "WALK_rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 275: ApplyAnimationEx(playerid, "PED", "WALK_shuffle", 4.1, 0, 1, 1, 1, 1, 1);
		case 276: ApplyAnimationEx(playerid, "PED", "WALK_start", 4.1, 0, 1, 1, 1, 1, 1);
		case 277: ApplyAnimationEx(playerid, "PED", "WALK_start_armed", 4.1, 0, 1, 1, 1, 1, 1);
		case 278: ApplyAnimationEx(playerid, "PED", "WALK_start_csaw", 4.1, 0, 1, 1, 1, 1, 1);
		case 279: ApplyAnimationEx(playerid, "PED", "WALK_start_rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 280: ApplyAnimationEx(playerid, "PED", "Walk_Wuzi", 4.1, 0, 1, 1, 1, 1, 1);
		case 281: ApplyAnimationEx(playerid, "PED", "WEAPON_crouch", 4.1, 0, 1, 1, 1, 1, 1);
		case 282: ApplyAnimationEx(playerid, "PED", "woman_idlestance", 4.1, 0, 1, 1, 1, 1, 1);
		case 283: ApplyAnimationEx(playerid, "PED", "woman_run", 4.1, 0, 1, 1, 1, 1, 1);
		case 284: ApplyAnimationEx(playerid, "PED", "WOMAN_runbusy", 4.1, 0, 1, 1, 1, 1, 1);
		case 285: ApplyAnimationEx(playerid, "PED", "WOMAN_runfatold", 4.1, 0, 1, 1, 1, 1, 1);
		case 286: ApplyAnimationEx(playerid, "PED", "woman_runpanic", 4.1, 0, 1, 1, 1, 1, 1);
		case 287: ApplyAnimationEx(playerid, "PED", "WOMAN_runsexy", 4.1, 0, 1, 1, 1, 1, 1);
		case 288: ApplyAnimationEx(playerid, "PED", "WOMAN_walkbusy", 4.1, 0, 1, 1, 1, 1, 1);
		case 289: ApplyAnimationEx(playerid, "PED", "WOMAN_walkfatold", 4.1, 0, 1, 1, 1, 1, 1);
		case 290: ApplyAnimationEx(playerid, "PED", "WOMAN_walknorm", 4.1, 0, 1, 1, 1, 1, 1);
		case 291: ApplyAnimationEx(playerid, "PED", "WOMAN_walkold", 4.1, 0, 1, 1, 1, 1, 1);
		case 292: ApplyAnimationEx(playerid, "PED", "WOMAN_walkpro", 4.1, 0, 1, 1, 1, 1, 1);
		case 293: ApplyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 0, 1, 1, 1, 1, 1);
		case 294: ApplyAnimationEx(playerid, "PED", "WOMAN_walkshop", 4.1, 0, 1, 1, 1, 1, 1);
		case 295: ApplyAnimationEx(playerid, "PED", "XPRESSscratch", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animped [1 - 295]");
	}
	return 1;
}
CMD:animplayerdvbys(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "PLAYER_DVBYS", "Plyr_DrivebyBwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "PLAYER_DVBYS", "Plyr_DrivebyFwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "PLAYER_DVBYS", "Plyr_DrivebyLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "PLAYER_DVBYS", "Plyr_DrivebyRHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animplayerdvbys [1 - 4]");
	}
	return 1;
}
CMD:animplayidles(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "PLAYIDLES", "shift", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "PLAYIDLES", "shldr", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "PLAYIDLES", "stretch", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "PLAYIDLES", "strleg", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "PLAYIDLES", "time", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animplayidles [1 - 5]");
	}
	return 1;
}
CMD:animpolice(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "POLICE", "CopTraf_Away", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "POLICE", "CopTraf_Come", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "POLICE", "CopTraf_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "POLICE", "CopTraf_Stop", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "POLICE", "COP_getoutcar_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "POLICE", "Cop_move_FWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "POLICE", "crm_drgbst_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "POLICE", "Door_Kick", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "POLICE", "plc_drgbst_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "POLICE", "plc_drgbst_02", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animpolice [1 - 10]");
	}
	return 1;
}
CMD:animpool(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "POOL", "POOL_ChalkCue", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "POOL", "POOL_Idle_Stance", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "POOL", "POOL_Long_Shot", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "POOL", "POOL_Long_Shot_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "POOL", "POOL_Long_Start", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "POOL", "POOL_Long_Start_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "POOL", "POOL_Med_Shot", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "POOL", "POOL_Med_Shot_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "POOL", "POOL_Med_Start", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "POOL", "POOL_Med_Start_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "POOL", "POOL_Place_White", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "POOL", "POOL_Short_Shot", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "POOL", "POOL_Short_Shot_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "POOL", "POOL_Short_Start", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "POOL", "POOL_Short_Start_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "POOL", "POOL_Walk", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "POOL", "POOL_Walk_Start", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "POOL", "POOL_XLong_Shot", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "POOL", "POOL_XLong_Shot_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "POOL", "POOL_XLong_Start", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "POOL", "POOL_XLong_Start_O", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animpool [1 - 21]");
	}
	return 1;
}
CMD:animpoor(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "POOR", "WINWASH_Start", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "POOR", "WINWASH_Wash2Beg", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animpoor [1 - 2]");
	}
	return 1;
}
CMD:animpython(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "PYTHON", "python_crouchfire", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "PYTHON", "python_crouchreload", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "PYTHON", "python_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "PYTHON", "python_fire_poor", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "PYTHON", "python_reload", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animpython [1 - 5]");
	}
	return 1;
}
CMD:animquad(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "QUAD", "QUAD_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "QUAD", "QUAD_driveby_FT", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "QUAD", "QUAD_driveby_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "QUAD", "QUAD_driveby_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "QUAD", "QUAD_FWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "QUAD", "QUAD_getoff_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "QUAD", "QUAD_getoff_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "QUAD", "QUAD_getoff_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "QUAD", "QUAD_geton_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "QUAD", "QUAD_geton_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "QUAD", "QUAD_hit", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "QUAD", "QUAD_kick", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "QUAD", "QUAD_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "QUAD", "QUAD_passenger", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "QUAD", "QUAD_reverse", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "QUAD", "QUAD_ride", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "QUAD", "QUAD_Right", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animquad [1 - 17]");
	}
	return 1;
}
CMD:animquaddbz(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "QUAD_DBZ", "Pass_Driveby_BWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "QUAD_DBZ", "Pass_Driveby_FWD", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "QUAD_DBZ", "Pass_Driveby_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "QUAD_DBZ", "Pass_Driveby_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animquadbz [1 - 4]");
	}
	return 1;
}
CMD:animrapping(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "RAPPING", "Laugh_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "RAPPING", "RAP_A_IN", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "RAPPING", "RAP_A_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "RAPPING", "RAP_A_OUT", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "RAPPING", "RAP_B_IN", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "RAPPING", "RAP_B_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "RAPPING", "RAP_B_OUT", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "RAPPING", "RAP_C_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animrapping [1 - 8]");
	}
	return 1;
}
CMD:animrifle(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "RIFLE", "RIFLE_crouchfire", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "RIFLE", "RIFLE_crouchload", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "RIFLE", "RIFLE_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "RIFLE", "RIFLE_fire_poor", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "RIFLE", "RIFLE_load", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animrifle [1 - 5]");
	}
	return 1;
}
CMD:animriot(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "RIOT", "RIOT_ANGRY", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "RIOT", "RIOT_challenge", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "RIOT", "RIOT_CHANT", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "RIOT", "RIOT_FUKU", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "RIOT", "RIOT_PUNCHES", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "RIOT", "RIOT_shout", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animriot [1 - 7]");
	}
	return 1;
}
CMD:animrobbank(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "ROB_BANK", "CAT_Safe_End", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "ROB_BANK", "CAT_Safe_Open", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "ROB_BANK", "CAT_Safe_Open_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "ROB_BANK", "CAT_Safe_Rob", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "ROB_BANK", "SHP_HandsUp_Scr", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animrobbank [1 - 5]");
	}
	return 1;
}
CMD:animrocket(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "ROCKET", "idle_rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "ROCKET", "RocketFire", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "ROCKET", "run_rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "ROCKET", "walk_rocket", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "ROCKET", "WALK_start_rocket", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animrocket [1 - 5]");
	}
	return 1;
}
CMD:animrustler(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "RUSTLER", "Plane_align_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "RUSTLER", "Plane_close", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "RUSTLER", "Plane_getin", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "RUSTLER", "Plane_getout", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "RUSTLER", "Plane_open", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animrustler [1 - 5]");
	}
	return 1;
}
CMD:animryder(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "RYDER", "RYD_Beckon_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "RYDER", "RYD_Beckon_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "RYDER", "RYD_Beckon_03", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "RYDER", "RYD_Die_PT1", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "RYDER", "RYD_Die_PT2", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "RYDER", "Van_Crate_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "RYDER", "Van_Crate_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "RYDER", "Van_Fall_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "RYDER", "Van_Fall_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "RYDER", "Van_Lean_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "RYDER", "Van_Lean_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "RYDER", "VAN_PickUp_E", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "RYDER", "VAN_PickUp_S", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "RYDER", "Van_Stand", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "RYDER", "Van_Stand_Crate", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "RYDER", "Van_Throw", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animryder [1 - 16]");
	}
	return 1;
}
CMD:animscrathching(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SCRATCHING", "scdldlp", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SCRATCHING", "scdlulp", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SCRATCHING", "scdrdlp", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SCRATCHING", "scdrulp", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SCRATCHING", "sclng_l", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SCRATCHING", "sclng_r", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SCRATCHING", "scmid_l", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "SCRATCHING", "scmid_r", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "SCRATCHING", "scshrtl", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "SCRATCHING", "scshrtr", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "SCRATCHING", "sc_ltor", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "SCRATCHING", "sc_rtol", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animscratching [1 - 12]");
	}
	return 1;
}
CMD:animshamal(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SHAMAL", "SHAMAL_align", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SHAMAL", "SHAMAL_getin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SHAMAL", "SHAMAL_getout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SHAMAL", "SHAMAL_open", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animshamal [1 - 4]");
	}
	return 1;
}
CMD:animshop(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SHOP", "ROB_2Idle", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SHOP", "ROB_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SHOP", "ROB_Loop_Threat", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SHOP", "ROB_Shifty", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SHOP", "ROB_StickUp_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SHOP", "SHP_Duck", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SHOP", "SHP_Duck_Aim", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "SHOP", "SHP_Duck_Fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "SHOP", "SHP_Gun_Aim", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "SHOP", "SHP_Gun_Duck", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "SHOP", "SHP_Gun_Fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "SHOP", "SHP_Gun_Grab", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "SHOP", "SHP_Gun_Threat", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "SHOP", "SHP_HandsUp_Scr", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "SHOP", "SHP_Jump_Glide", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "SHOP", "SHP_Jump_Land", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "SHOP", "SHP_Jump_Launch", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "SHOP", "SHP_Rob_GiveCash", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "SHOP", "SHP_Rob_HandsUp", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "SHOP", "SHP_Rob_React", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "SHOP", "SHP_Serve_End", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "SHOP", "SHP_Serve_Idle", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "SHOP", "SHP_Serve_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "SHOP", "SHP_Serve_Start", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "SHOP", "Smoke_RYD", 4.1, 0, 1, 1, 1, 1, 1);
		case 26: ApplyAnimationEx(playerid, "SHOP", "donutdrop", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animshop [1 - 26]");
	}
	return 1;
}
CMD:animshotgun(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SHOTGUN", "shotgun_crouchfire", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SHOTGUN", "shotgun_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SHOTGUN", "shotgun_fire_poor", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animshotgun [1 - 3]");
	}
	return 1;
}
CMD:animsilenced(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SILENCED", "CrouchReload", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SILENCED", "SilenceCrouchfire", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SILENCED", "Silence_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SILENCED", "Silence_reload", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animsilenced [1 - 4]");
	}
	return 1;
}
CMD:animskate(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SKATE", "skate_idle", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SKATE", "skate_run", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SKATE", "skate_sprint", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animskate [1 - 3]");
	}
	return 1;
}
CMD:animsmoking(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SMOKING", "F_smklean_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SMOKING", "M_smklean_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SMOKING", "M_smkstnd_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SMOKING", "M_smk_drag", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SMOKING", "M_smk_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SMOKING", "M_smk_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SMOKING", "M_smk_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "SMOKING", "M_smk_tap", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animsmoking [1 - 9]");
	}
	return 1;
}
CMD:animspraycan(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SPRAYCAN", "spraycan_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SPRAYCAN", "spraycan_full", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animspraycan [1 - 2]");
	}
	return 1;
}
CMD:animstrip(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "STRIP", "PLY_CASH", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "STRIP", "PUN_CASH", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "STRIP", "PUN_HOLLER", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "STRIP", "PUN_LOOP", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "STRIP", "strip_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "STRIP", "strip_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "STRIP", "strip_C", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "STRIP", "strip_D", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "STRIP", "strip_E", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "STRIP", "strip_F", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "STRIP", "strip_G", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "STRIP", "STR_A2B", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "STRIP", "STR_B2A", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "STRIP", "STR_B2C", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "STRIP", "STR_C1", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "STRIP", "STR_C2", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "STRIP", "STR_C2B", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "STRIP", "STR_Loop_A", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "STRIP", "STR_Loop_B", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "STRIP", "STR_Loop_C", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animstrip [1 - 20]");
	}
	return 1;
}
CMD:animsunbathe(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SUNBATHE", "batherdown", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SUNBATHE", "batherup", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SUNBATHE", "Lay_Bac_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SUNBATHE", "Lay_Bac_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_M_IdleA", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_M_IdleB", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_M_IdleC", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_M_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_M_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_W_idleA", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_W_idleB", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_W_idleC", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_W_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "SUNBATHE", "ParkSit_W_out", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "SUNBATHE", "SBATHE_F_LieB2Sit", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "SUNBATHE", "SBATHE_F_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "SUNBATHE", "SitnWait_in_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "SUNBATHE", "SitnWait_out_W", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animbath [1 - 18]");
	}
	return 1;
}
CMD:animswat(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SWAT", "gnstwall_injurd", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SWAT", "JMP_Wall1m_180", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SWAT", "Rail_fall", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SWAT", "Rail_fall_crawl", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SWAT", "swt_breach_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SWAT", "swt_breach_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SWAT", "swt_breach_03", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "SWAT", "swt_go", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "SWAT", "swt_lkt", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "SWAT", "swt_sty", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "SWAT", "swt_vent_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "SWAT", "swt_vent_02", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "SWAT", "swt_vnt_sht_die", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "SWAT", "swt_vnt_sht_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "SWAT", "swt_vnt_sht_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "SWAT", "swt_wllpk_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "SWAT", "swt_wllpk_L_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "SWAT", "swt_wllpk_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "SWAT", "swt_wllpk_R_back", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "SWAT", "swt_wllshoot_in_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "SWAT", "swt_wllshoot_in_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "SWAT", "swt_wllshoot_out_L", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "SWAT", "swt_wllshoot_out_R", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "SWAT", "cards_pick_02", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animswat [1 - 24]");
	}
	return 1;
}
CMD:animsweet(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SWEET", "ho_ass_slapped", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SWEET", "LaFin_Player", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SWEET", "LaFin_Sweet", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SWEET", "plyr_hndshldr_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SWEET", "sweet_ass_slap", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SWEET", "sweet_hndshldr_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SWEET", "Sweet_injuredloop", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animsweet [1 - 7]");
	}
	return 1;
}
CMD:animswim(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SWIM", "Swim_Breast", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SWIM", "SWIM_crawl", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SWIM", "Swim_Dive_Under", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SWIM", "Swim_Glide", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SWIM", "Swim_jumpout", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SWIM", "Swim_Tread", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SWIM", "Swim_Under", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animswim [1 - 7]");
	}
	return 1;
}
CMD:animsword(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SWORD", "sword_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SWORD", "sword_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SWORD", "sword_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SWORD", "sword_4", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SWORD", "sword_block", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SWORD", "Sword_Hit_1", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SWORD", "Sword_Hit_2", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "SWORD", "Sword_Hit_3", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "SWORD", "sword_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "SWORD", "sword_part", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animsword [1 - 10]");
	}
	return 1;
}
CMD:animtank(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "TANK", "TANK_align_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "TANK", "TANK_close_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "TANK", "TANK_doorlocked", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "TANK", "TANK_getin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "TANK", "TANK_getout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "TANK", "TANK_open_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animtank [1 - 6]");
	}
	return 1;
}
CMD:animtattoos(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmL_In_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmL_In_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmL_In_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmL_Out_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmL_Out_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmL_Out_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmL_Pose_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmL_Pose_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmL_Pose_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_In_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_In_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_In_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_Out_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_Out_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_Out_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_Pose_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_Pose_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_Pose_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_In_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_In_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 21: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_In_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 22: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_Out_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 23: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_Out_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 24: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_Out_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 25: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_Pose_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 26: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_Pose_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 27: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_Pose_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 28: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_Sit_In_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 29: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_Sit_Loop_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 30: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Back_Sit_Out_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 31: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Bel_In_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 32: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Bel_In_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 33: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Bel_Out_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 34: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Bel_Out_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 35: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Bel_Pose_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 36: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Bel_Pose_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 37: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Che_In_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 38: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Che_In_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 39: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Che_In_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 40: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Che_Out_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 41: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Che_Out_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 42: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Che_Out_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 43: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Che_Pose_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 44: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Che_Pose_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 45: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Che_Pose_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 46: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Drop_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 47: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Idle_Loop_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 48: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Idle_Loop_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 49: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Sit_In_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 50: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Sit_In_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 51: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Sit_In_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 52: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Sit_Loop_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 53: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Sit_Loop_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 54: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Sit_Loop_T", 4.1, 0, 1, 1, 1, 1, 1);
		case 55: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Sit_Out_O", 4.1, 0, 1, 1, 1, 1, 1);
		case 56: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Sit_Out_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 57: ApplyAnimationEx(playerid, "TATTOOS", "TAT_Sit_Out_T", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animtattoos [1 - 57]");
	}
	return 1;
}
CMD:animtec(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "TEC", "TEC_crouchfire", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "TEC", "TEC_crouchreload", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "TEC", "TEC_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "TEC", "TEC_reload", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animtec [1 - 4]");
	}
	return 1;
}
CMD:animtrain(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "TRAIN", "tran_gtup", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "TRAIN", "tran_hng", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "TRAIN", "tran_ouch", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "TRAIN", "tran_stmb", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animtrain [1 - 4]");
	}
	return 1;
}
CMD:animtruck(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_ALIGN_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_ALIGN_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_closedoor_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_closedoor_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_close_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_close_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_getin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_getin_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_getout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_getout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_jackedLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_jackedRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_open_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_open_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_pullout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_pullout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "TRUCK", "TRUCK_Shuffle", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animtruck [1 - 17]");
	}
	return 1;
}
CMD:animuzi(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "UZI", "UZI_crouchfire", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "UZI", "UZI_crouchreload", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "UZI", "UZI_fire", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "UZI", "UZI_fire_poor", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "UZI", "UZI_reload", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animuzi [1 - 5]");
	}
	return 1;
}
CMD:animvan(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "VAN", "VAN_close_back_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "VAN", "VAN_close_back_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "VAN", "VAN_getin_Back_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "VAN", "VAN_getin_Back_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "VAN", "VAN_getout_back_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "VAN", "VAN_getout_back_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "VAN", "VAN_open_back_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "VAN", "VAN_open_back_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animvan [1 - 8]");
	}
	return 1;
}
CMD:animvending(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "VENDING", "VEND_Drink2_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "VENDING", "VEND_Drink_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "VENDING", "vend_eat1_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "VENDING", "VEND_Eat_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "VENDING", "VEND_Use", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "VENDING", "VEND_Use_pt2", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animvending [1 - 6]");
	}
	return 1;
}
CMD:animvortex(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "VORTEX", "CAR_jumpin_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "VORTEX", "CAR_jumpin_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "VORTEX", "vortex_getout_LHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "VORTEX", "vortex_getout_RHS", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animvortex [1 - 4]");
	}
	return 1;
}
CMD:animwayfarer(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "WAYFARER", "WF_Back", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "WAYFARER", "WF_drivebyFT", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "WAYFARER", "WF_drivebyLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "WAYFARER", "WF_drivebyRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "WAYFARER", "WF_Fwd", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "WAYFARER", "WF_getoffBACK", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "WAYFARER", "WF_getoffLHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "WAYFARER", "WF_getoffRHS", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "WAYFARER", "WF_hit", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "WAYFARER", "WF_jumponL", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "WAYFARER", "WF_jumponR", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "WAYFARER", "WF_kick", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "WAYFARER", "WF_Left", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "WAYFARER", "WF_passenger", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "WAYFARER", "WF_pushes", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "WAYFARER", "WF_Ride", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "WAYFARER", "WF_Right", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "WAYFARER", "WF_Still", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animway [1 - 18]");
	}
	return 1;
}
CMD:animweap(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "WEAPONS", "SHP_1H_Lift", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "WEAPONS", "SHP_1H_Lift_End", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "WEAPONS", "SHP_1H_Ret", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "WEAPONS", "SHP_1H_Ret_S", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "WEAPONS", "SHP_2H_Lift", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "WEAPONS", "SHP_2H_Lift_End", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "WEAPONS", "SHP_2H_Ret", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "WEAPONS", "SHP_2H_Ret_S", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "WEAPONS", "SHP_Ar_Lift", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "WEAPONS", "SHP_Ar_Lift_End", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "WEAPONS", "SHP_Ar_Ret", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "WEAPONS", "SHP_Ar_Ret_S", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "WEAPONS", "SHP_G_Lift_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "WEAPONS", "SHP_G_Lift_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "WEAPONS", "SHP_Tray_In", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "WEAPONS", "SHP_Tray_Out", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "WEAPONS", "SHP_Tray_Pose", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animweap [1 - 17]");
	}
	return 1;
}
CMD:animwuzi(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "WUZI", "CS_Dead_Guy", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "WUZI", "CS_Plyr_pt1", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "WUZI", "CS_Plyr_pt2", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "WUZI", "CS_Wuzi_pt1", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "WUZI", "CS_Wuzi_pt2", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "WUZI", "Walkstart_Idle_01", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "WUZI", "Wuzi_follow", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "WUZI", "Wuzi_Greet_Plyr", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "WUZI", "Wuzi_Greet_Wuzi", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "WUZI", "Wuzi_grnd_chk", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "WUZI", "Wuzi_stand_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "WUZI", "Wuzi_Walk", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animwuzi [1 - 12]");
	}
	return 1;
}
CMD:animsnm(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SNM", "SPANKING_IDLEW", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SNM", "SPANKING_IDLEP", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SNM", "SPANKINGW", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SNM", "SPANKINGP", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SNM", "SPANKEDW", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SNM", "SPANKEDP", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SNM", "SPANKING_ENDW", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "SNM", "SPANKING_ENDP", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animsnm [1 - 8]");
	}
	return 1;
}
CMD:animblowjob(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_START_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_START_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_END_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_END_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_START_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_START_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_END_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_END_W", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animblowjob [1 - 12]");
	}
	return 1;
}
CMD:animsex(playerid, params[])
{
    new animid;
	if(sscanf(params,"i",animid)) return PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	switch(animid)
	{
		case 1: ApplyAnimationEx(playerid, "SEX", "SEX_1_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimationEx(playerid, "SEX", "SEX_1_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimationEx(playerid, "SEX", "SEX_2_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 4: ApplyAnimationEx(playerid, "SEX", "SEX_2_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 5: ApplyAnimationEx(playerid, "SEX", "SEX_3_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 6: ApplyAnimationEx(playerid, "SEX", "SEX_3_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 7: ApplyAnimationEx(playerid, "SEX", "SEX_1_CUM_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 8: ApplyAnimationEx(playerid, "SEX", "SEX_1_CUM_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 9: ApplyAnimationEx(playerid, "SEX", "SEX_1_FAIL_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 10: ApplyAnimationEx(playerid, "SEX", "SEX_1_FAIL_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 11: ApplyAnimationEx(playerid, "SEX", "SEX_2_FAIL_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 12: ApplyAnimationEx(playerid, "SEX", "SEX_2_FAIL_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 13: ApplyAnimationEx(playerid, "SEX", "SEX_3_FAIL_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 14: ApplyAnimationEx(playerid, "SEX", "SEX_3_FAIL_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 15: ApplyAnimationEx(playerid, "SEX", "SEX_1TO2_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 16: ApplyAnimationEx(playerid, "SEX", "SEX_1TO2_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 17: ApplyAnimationEx(playerid, "SEX", "SEX_2TO3_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 18: ApplyAnimationEx(playerid, "SEX", "SEX_2TO3_P", 4.1, 0, 1, 1, 1, 1, 1);
		case 19: ApplyAnimationEx(playerid, "SEX", "SEX_3TO1_W", 4.1, 0, 1, 1, 1, 1, 1);
		case 20: ApplyAnimationEx(playerid, "SEX", "SEX_3TO1_P", 4.1, 0, 1, 1, 1, 1, 1);
		default: SendClientMessage(playerid, COLOR_WHITE, "Syntax: /animsex [1 - 20]");
	}
	return 1;
}

CMD:animairport(playerid) return ApplyAnimationEx(playerid, "AIRPORT", "thrw_barl_thrw", 4.1, 0, 1, 1, 1, 1, 1);
CMD:animflame(playerid) return ApplyAnimationEx(playerid, "FLAME", "FLAME_fire", 4.1, 0, 1, 1, 1, 1, 1);
CMD:animgog(playerid) return ApplyAnimationEx(playerid, "goggles", "goggles_put_on", 4.1, 0, 1, 1, 1, 1, 1);
CMD:animmedic(playerid) return ApplyAnimationEx(playerid, "MEDIC", "CPR", 4.1, 0, 1, 1, 1, 1, 1);
CMD:animsniper(playerid) return ApplyAnimationEx(playerid, "SNIPER", "WEAPON_sniper", 4.1, 0, 1, 1, 1, 1, 1);

CMD:stopanim(playerid) return ClearAnimations(playerid);

CMD:beer(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
CMD:cellin(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
CMD:cellout(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
CMD:duck(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DUCK);
CMD:enterveh(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_ENTER_VEHICLE);
CMD:exitveh(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_EXIT_VEHICLE);
CMD:jetpack(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
CMD:sit(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SITTING);
CMD:sprunk(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
CMD:wine(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);

CMD:stopspac(playerid) return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
