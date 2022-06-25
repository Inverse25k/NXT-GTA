#include "common.hpp"
#include "BaseTab.hpp"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "nativeui.hpp"
#include "features.hpp"

static char* Boats1[] = {
    "DINGHY", "DINGHY2", "DINGHY3", "DINGHY4", "JETMAX",
    "MARQUIS", "PREDATOR", "SEASHARK", "SEASHARK2", "SEASHARK3",
    "SPEEDER", "SPEEDER2", "SQUALO", "SUBMERSIBLE", "SUBMERSIBLE2",
    "SUNTRAP", "TORO", "TORO2", "TROPIC", "TROPIC2",
    "TUG"
};
static char* Commercial1[] = {
    "BENSON", "BIFF", "HAULER", "MULE", "MULE2",
    "MULE3", "PACKER", "PHANTOM", "POUNDER", "STOCKADE",
    "STOCKADE3"
};
static char* Compacts1[] = {
    "BLISTA", "BRIOSO", "DILETTANTE", "DILETTANTE2", "ISSI2",
    "PANTO", "PRAIRIE", "RHAPSODY"
};
static char* Coupes1[] = {
    "COGCABRIO", "EXEMPLAR", "F620", "FELON", "FELON2",
    "JACKAL", "ORACLE", "ORACLE2", "SENTINEL", "SENTINEL2",
    "WINDSOR", "WINDSOR2", "ZION", "ZION2"
};
static char* Cycles1[] = {
    "BMX", "CRUISER", "FIXTER", "SCORCHER", "TRIBIKE",
    "TRIBIKE2", "TRIBIKE3"
};
static char* Emergency1[] = {
    "AMBULANCE", "FBI", "FBI2", "FIRETRUK", "LGUARD",
    "PBUS", "PRANGER", "POLICE", "POLICE2", "POLICE3",
    "POLICE4", "POLICEB", "POLICEOLD1", "POLICEOLD2", "POLICET",
    "SHERIFF", "SHERIFF2", "RIOT"
};
static char* Helicopters1[] = {
    "ANNIHILATOR", "BLIMP", "BLIMP2", "BUZZARD", "BUZZARD2",
    "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "CARGOBOB4", "FROGGER",
    "FROGGER2", "MAVERICK", "POLMAV", "SAVAGE", "SKYLIFT",
    "SUPERVOLITO", "SUPERVOLITO2", "SWIFT", "SWIFT2", "VALKYRIE",
    "VALKYRIE2", "VOLATUS"
};
static char* Industrial1[] = {
    "BULLDOZER", "CUTTER", "DUMP", "FLATBED", "GUARDIAN",
    "HANDLER", "MIXER", "MIXER2", "RUBBLE", "TIPTRUCK",
    "TIPTRUCK2"
};
static char* Military1[] = {
    "BARRACKS", "BARRACKS2", "BARRACKS3", "CRUSADER", "RHINO"
};
static char* Motorcycles1[] = {
    "AKUMA", "AVARUS", "BAGGER", "BATI", "BATI2",
    "BF400", "CARBONRS", "CHIMERA", "CLIFFHANGER", "DAEMON",
    "DAEMON2", "DEFILER", "DOUBLE", "ENDURO", "ESSKEY",
    "FAGGIO", "FAGGIO2", "FAGGIO3", "GARGOYLE", "HAKUCHOU",
    "HAKUCHOU2", "HEXER", "INNOVATION", "LECTRO", "MANCHEZ",
    "NEMESIS", "NIGHTBLADE", "PCJ", "RATBIKE", "RUFFIAN",
    "SANCHEZ", "SANCHEZ2", "SANCTUS", "SHOTARO", "SOVEREIGN",
    "THRUST", "VADER", "VINDICATOR", "VORTEX", "WOLFSBANE",
    "ZOMBIEA", "ZOMBIEB", "DIABLOUS", "DIABLOUS2", "FCR",
    "FCR2"
};
static char* Muscle1[] = {
    "BLADE", "BUCCANEER", "BUCCANEER2", "CHINO", "CHINO2",
    "COQUETTE3", "DOMINATOR", "DOMINATOR2", "DUKES", "DUKES2",
    "GAUNTLET", "GAUNTLET2", "FACTION", "FACTION2", "FACTION3",
    "HOTKNIFE", "LURCHER", "MOONBEAM", "MOONBEAM2", "NIGHTSHADE",
    "PHOENIX", "PICADOR", "RATLOADER", "RATLOADER2", "RUINER", "RUINER2", "RUINER3",
    "SABREGT", "SABREGT2", "SLAMVAN", "SLAMVAN2", "SLAMVAN3",
    "STALION", "STALION2", "TAMPA", "VIGERO", "VIRGO",
    "VIRGO2", "VIRGO3", "VOODOO", "VOODOO2"
};
static char* OffRoad1[] = {
    "BFINJECTION", "BIFTA", "BLAZER", "BLAZER2", "BLAZER3",
    "BLAZER4", "BODHI2", "BRAWLER", "DLOADER", "DUBSTA3",
    "DUNE", "DUNE2", "INSURGENT", "INSURGENT2", "KALAHARI",
    "MARSHALL", "MESA3", "MONSTER", "RANCHERXL", "RANCHERXL2",
    "REBEL", "REBEL2", "SANDKING", "SANDKING2", "TECHNICAL",
    "TROPHYTRUCK", "TROPHYTRUCK2", "TECHNICAL2", "DUNE4", "DUNE5",
    "BLAZER5"
};
static char* Planes1[] = {
    "BESRA", "CARGOPLANE", "CUBAN800", "DODO", "DUSTER",
    "HYDRA", "JET", "LAZER", "LUXOR", "LUXOR2",
    "MAMMATUS", "MILJET", "NIMBUS", "SHAMAL", "STUNT",
    "TITAN", "VELUM", "VELUM2", "VESTRA"
};
static char* Sedans1[] = {
    "ASEA", "ASEA2", "ASTEROPE", "COG55", "COG552",
    "COGNOSCENTI", "COGNOSCENTI2", "EMPEROR", "EMPEROR2", "EMPEROR3",
    "FUGITIVE", "GLENDALE", "INGOT", "INTRUDER", "LIMO2",
    "PREMIER", "PRIMO", "PRIMO2", "REGINA", "ROMERO",
    "SCHAFTER2", "SCHAFTER5", "SCHAFTER6", "STANIER", "STRATUM",
    "STRETCH", "SUPERD", "SURGE", "TAILGATER", "WARRENER",
    "WASHINGTON"
};
static char* Service1[] = {
    "AIRBUS", "BRICKADE", "BUS", "COACH", "RALLYTRUCK",
    "RENTALBUS", "TAXI", "TOURBUS", "TRASH", "TRASH2",
    "WASTELANDER",
};
static char* Sports1[] = {
    "ALPHA", "BANSHEE", "BESTIAGTS", "BLISTA2", "BLISTA3",
    "BUFFALO", "BUFFALO2", "BUFFALO3", "CARBONIZZARE", "COMET2",
    "COQUETTE", "ELEGY", "ELEGY2", "FELTZER2", "FUROREGT", "FUSILADE",
    "FUTO", "JESTER", "JESTER2", "KHAMELION", "KURUMA",
    "KURUMA2", "LYNX", "MASSACRO", "MASSACRO2", "NINEF",
    "NINEF2", "OMNIS", "PENUMBRA", "RAPIDGT", "RAPIDGT2",
    "RAPTOR", "SCHAFTER3", "SCHAFTER4", "SCHWARTZER", "SEVEN70",
    "SULTAN", "SURANO", "SPECTER", "SPECTER2", "TAMPA2", "TROPOS", "VERLIERER2",
    "RUINER2", "PHANTOM2", "RUSTON"
};
static char* SportsClassics1[] = {
    "BTYPE", "BTYPE2", "BTYPE3", "CASCO", "COQUETTE2",
    "FELTZER3", "JB700", "MAMBA", "MANANA", "MONROE",
    "PEYOTE", "PIGALLE", "STINGER", "STINGERGT", "TORNADO",
    "TORNADO2", "TORNADO3", "TORNADO4", "TORNADO5", "TORNADO6",
    "ZTYPE", "INFERNUS2", "TURISMO2",
};
static char* Super1[] = {
    "ADDER", "BANSHEE2", "BULLET", "CHEETAH", "ENTITYXF",
    "FMJ", "SHEAVA", "INFERNUS", "NERO", "NERO2","OSIRIS", "LE7B",
    "ITALIGTB", "ITALIGTB2", "PFISTER811", "PROTOTIPO", "REAPER", "SULTANRS", "T20",
    "TEMPESTA", "TURISMOR", "TYRUS", "VACCA", "VOLTIC", "ZENTORNO", "VOLTIC2", "PENETRATOR", "GP1"
};
static char* SUVs1[] = {
    "BALLER", "BALLER2", "BALLER3", "BALLER4", "BALLER5",
    "BALLER6", "BJXL", "CAVALCADE", "CAVALCADE2", "CONTENDER",
    "DUBSTA", "DUBSTA2", "FQ2", "GRANGER", "GRESLEY",
    "HABANERO", "HUNTLEY", "LANDSTALKER", "MESA", "MESA2",
    "PATRIOT", "RADI", "ROCOTO", "SEMINOLE", "SERRANO",
    "XLS", "XLS2"
};
static char* Trailer1[] = {
    "ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2", "BALETRAILER", "BOATTRAILER",
    "DOCKTRAILER", "FREIGHTTRAILER", "GRAINTRAILER", "PROPTRAILER", "RAKETRAILER",
    "TANKER", "TANKER2", "TR2", "TR3", "TR4",
    "TRAILERLOGS", "TRAILERS", "TRAILERS2", "TRAILERS3", "TRAILERSMALL",
    "TRFLAT", "TVTRAILER"
};
static char* Trains1[] = {
    "CABLECAR", "FREIGHT", "FREIGHTCAR", "FREIGHTCONT1", "FREIGHTCONT2",
    "FREIGHTGRAIN", "METROTRAIN", "TANKERCAR"
};
static char* Utility1[] = {
    "AIRTUG", "CADDY", "CADDY2", "DOCKTUG", "FORKLIFT",
    "MOWER", "RIPLEY", "SADLER", "SADLER2", "SCRAP",
    "TOWTRUCK", "TOWTRUCK2", "TRACTOR", "TRACTOR2", "TRACTOR3",
    "UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3"
};
static char* Vans1[] = {
    "BISON", "BISON2", "BISON3", "BOBCATXL", "BOXVILLE",
    "BOXVILLE2", "BOXVILLE3", "BOXVILLE4", "BURRITO", "BURRITO2",
    "BURRITO3", "BURRITO4", "BURRITO5", "CAMPER", "GBURRITO",
    "GBURRITO2", "JOURNEY", "MINIVAN", "MINIVAN2", "PARADISE",
    "PONY", "PONY2", "RUMPO", "RUMPO2", "RUMPO3",
    "SPEEDO", "SPEEDO2", "SURFER", "SURFER2", "TACO",
    "YOUGA", "YOUGA2"
};
char* pedModels[] = {
    "A_C_Boar","A_C_Chickenhawk","A_C_Chimp","A_C_Chop","A_C_Cormorant","A_C_Cow","A_C_Coyote","A_C_Crow","A_C_Deer","A_C_Fish","A_C_Hen","A_C_Husky","A_C_MtLion","A_C_Pig","A_C_Pigeon","A_C_Rat","A_C_Retriever",
    "A_C_Rhesus","A_C_Rottweiler","A_C_Seagull","A_C_SharkTiger","A_C_shepherd","A_F_M_Beach_01","A_F_M_BevHills_01","A_F_M_BevHills_02","A_F_M_BodyBuild_01","A_F_M_Business_02","A_F_M_Downtown_01","A_F_M_EastSA_01",
    "A_F_M_EastSA_02","A_F_M_FatBla_01","A_F_M_FatCult_01","A_F_M_FatWhite_01","A_F_M_KTown_01","A_F_M_KTown_02","A_F_M_ProlHost_01","A_F_M_Salton_01","A_F_M_SkidRow_01","A_F_M_SouCentMC_01","A_F_M_SouCent_01","A_F_M_SouCent_02",
    "A_F_M_Tourist_01","A_F_M_TrampBeac_01","A_F_M_Tramp_01","A_F_O_GenStreet_01","A_F_O_Indian_01","A_F_O_KTown_01","A_F_O_Salton_01","A_F_O_SouCent_01","A_F_O_SouCent_02","A_F_Y_Beach_01","A_F_Y_BevHills_01","A_F_Y_BevHills_02",
    "A_F_Y_BevHills_03","A_F_Y_BevHills_04","A_F_Y_Business_01","A_F_Y_Business_02","A_F_Y_Business_03","A_F_Y_Business_04","A_F_Y_EastSA_01","A_F_Y_EastSA_02","A_F_Y_EastSA_03","A_F_Y_Epsilon_01","A_F_Y_Fitness_01",
    "A_F_Y_Fitness_02","A_F_Y_GenHot_01","A_F_Y_Golfer_01","A_F_Y_Hiker_01","A_F_Y_Hippie_01","A_F_Y_Hipster_01","A_F_Y_Hipster_02","A_F_Y_Hipster_03","A_F_Y_Hipster_04","A_F_Y_Indian_01","A_F_Y_Juggalo_01","A_F_Y_Runner_01",
    "A_F_Y_RurMeth_01","A_F_Y_SCDressy_01","A_F_Y_Skater_01","A_F_Y_SouCent_01","A_F_Y_SouCent_02","A_F_Y_SouCent_03","A_F_Y_Tennis_01","A_F_Y_Topless_01","A_F_Y_Tourist_01","A_F_Y_Tourist_02","A_F_Y_Vinewood_01",
    "A_F_Y_Vinewood_02","A_F_Y_Vinewood_03","A_F_Y_Vinewood_04","A_F_Y_Yoga_01","A_M_M_ACult_01","A_M_M_AfriAmer_01","A_M_M_Beach_01","A_M_M_Beach_02","A_M_M_BevHills_01","A_M_M_BevHills_02","A_M_M_Business_01",
    "A_M_M_EastSA_01","A_M_M_EastSA_02","A_M_M_Farmer_01","A_M_M_FatLatin_01","A_M_M_GenFat_01","A_M_M_GenFat_02","A_M_M_Golfer_01","A_M_M_HasJew_01","A_M_M_Hillbilly_01","A_M_M_Hillbilly_02","A_M_M_Indian_01",
    "A_M_M_KTown_01","A_M_M_Malibu_01","A_M_M_MexCntry_01","A_M_M_MexLabor_01","A_M_M_OG_Boss_01","A_M_M_Paparazzi_01","A_M_M_Polynesian_01","A_M_M_ProlHost_01","A_M_M_RurMeth_01","A_M_M_Salton_01","A_M_M_Salton_02",
    "A_M_M_Salton_03","A_M_M_Salton_04","A_M_M_Skater_01","A_M_M_Skidrow_01","A_M_M_SoCenLat_01","A_M_M_SouCent_01","A_M_M_SouCent_02","A_M_M_SouCent_03","A_M_M_SouCent_04","A_M_M_StLat_02","A_M_M_Tennis_01",
    "A_M_M_Tourist_01","A_M_M_TrampBeac_01","A_M_M_Tramp_01","A_M_M_TranVest_01","A_M_M_TranVest_02","A_M_O_ACult_01","A_M_O_ACult_02","A_M_O_Beach_01","A_M_O_GenStreet_01","A_M_O_KTown_01","A_M_O_Salton_01",
    "A_M_O_SouCent_01","A_M_O_SouCent_02","A_M_O_SouCent_03","A_M_O_Tramp_01","A_M_Y_ACult_01","A_M_Y_ACult_02","A_M_Y_BeachVesp_01","A_M_Y_BeachVesp_02","A_M_Y_Beach_01","A_M_Y_Beach_02","A_M_Y_Beach_03","A_M_Y_BevHills_01",
    "A_M_Y_BevHills_02","A_M_Y_BreakDance_01","A_M_Y_BusiCas_01","A_M_Y_Business_01","A_M_Y_Business_02","A_M_Y_Business_03","A_M_Y_Cyclist_01","A_M_Y_DHill_01","A_M_Y_Downtown_01","A_M_Y_EastSA_01","A_M_Y_EastSA_02",
    "A_M_Y_Epsilon_01","A_M_Y_Epsilon_02","A_M_Y_Gay_01","A_M_Y_Gay_02","A_M_Y_GenStreet_01","A_M_Y_GenStreet_02","A_M_Y_Golfer_01","A_M_Y_HasJew_01","A_M_Y_Hiker_01","A_M_Y_Hippy_01","A_M_Y_Hipster_01","A_M_Y_Hipster_02",
    "A_M_Y_Hipster_03","A_M_Y_Indian_01","A_M_Y_Jetski_01","A_M_Y_Juggalo_01","A_M_Y_KTown_01","A_M_Y_KTown_02","A_M_Y_Latino_01","A_M_Y_MethHead_01","A_M_Y_MexThug_01","A_M_Y_MotoX_01","A_M_Y_MotoX_02","A_M_Y_MusclBeac_01",
    "A_M_Y_MusclBeac_02","A_M_Y_Polynesian_01","A_M_Y_RoadCyc_01","A_M_Y_Runner_01","A_M_Y_Runner_02","A_M_Y_Salton_01","A_M_Y_Skater_01","A_M_Y_Skater_02","A_M_Y_SouCent_01","A_M_Y_SouCent_02","A_M_Y_SouCent_03","A_M_Y_SouCent_04",
    "A_M_Y_StBla_01","A_M_Y_StBla_02","A_M_Y_StLat_01","A_M_Y_StWhi_01","A_M_Y_StWhi_02","A_M_Y_Sunbathe_01","A_M_Y_Surfer_01","A_M_Y_VinDouche_01","A_M_Y_Vinewood_01","A_M_Y_Vinewood_02","A_M_Y_Vinewood_03","A_M_Y_Vinewood_04",
    "A_M_Y_Yoga_01","CSB_Abigail","CSB_Anita","CSB_Anton","CSB_BallasOG","CSB_Bride","CSB_BurgerDrug","CSB_Car3guy1","CSB_Car3guy2","CSB_Chef","CSB_Chin_goon","CSB_Cletus","CSB_Cop","CSB_Customer","CSB_Denise_friend",
    "CSB_FOS_rep","CSB_G","CSB_Groom","CSB_Grove_str_dlr","CSB_Hao","CSB_Hugh","CSB_Imran","CSB_Janitor","CSB_Maude","CSB_MWeather","CSB_Ortega","CSB_Oscar","CSB_PornDudes","CSB_PrologueDriver","CSB_ProlSec","CSB_Ramp_gang",
    "CSB_Ramp_hic","CSB_Ramp_hipster","CSB_Ramp_marine","CSB_Ramp_mex","CSB_Reporter","CSB_RoccoPelosi","CSB_Screen_Writer","CSB_Stripper_01","CSB_Stripper_02","CSB_Tonya","CSB_TrafficWarden","CS_AmandaTownley","CS_Andreas",
    "cs_ashley","CS_Bankman","CS_Barry","CS_Beverly","CS_Brad","CS_BradCadaver","CS_Carbuyer","CS_Casey","CS_ChengSr","CS_ChrisFormage","CS_Clay","CS_Dale","CS_DaveNorton","cs_debra","cs_denise","CS_Devin","CS_Dom","CS_Dreyfuss",
    "CS_DrFriedlander","CS_Fabien","CS_FBISuit_01","CS_Floyd","CS_Guadalope","cs_gurk","CS_Hunter","CS_Janet","CS_JewelAss","CS_JimmyBoston","CS_JimmyDiSanto","CS_JoeMinuteMan","CS_JohnnyKlebitz","CS_Josef","CS_Josh","CS_LamarDavis",
    "CS_Lazlow","CS_LesterCrest","CS_LifeInvad_01","CS_Magenta","CS_Manuel","CS_Marnie","CS_MartinMadrazo","CS_MaryAnn","CS_Michelle","CS_Milton","CS_Molly","CS_MovPremF_01","CS_MovPremMale","CS_MRK","CS_MrsPhillips","CS_MRS_Thornhill",
    "CS_Natalia","CS_NervousRon","CS_Nigel","CS_Old_Man1A","CS_Old_Man2","CS_Omega","CS_Orleans","CS_Paper","CS_Patricia","CS_Priest","CS_ProlSec_02","CS_RussianDrunk","CS_SiemonYetarian","CS_Solomon","CS_SteveHains","CS_Stretch",
    "CS_Tanisha","CS_TaoCheng","CS_TaosTranslator","CS_TennisCoach","CS_Terry","CS_Tom","CS_TomEpsilon","CS_TracyDiSanto","CS_Wade","CS_Zimbor","G_F_Y_ballas_01","G_F_Y_Families_01","G_F_Y_Lost_01","G_F_Y_Vagos_01","G_M_M_ArmBoss_01",
    "G_M_M_ArmGoon_01","G_M_M_ArmLieut_01","G_M_M_ChemWork_01","G_M_M_ChiBoss_01","G_M_M_ChiCold_01","G_M_M_ChiGoon_01","G_M_M_ChiGoon_02","G_M_M_KorBoss_01","G_M_M_MexBoss_01","G_M_M_MexBoss_02","G_M_Y_ArmGoon_02","G_M_Y_Azteca_01",
    "G_M_Y_BallaEast_01","G_M_Y_BallaOrig_01","G_M_Y_BallaSout_01","G_M_Y_FamCA_01","G_M_Y_FamDNF_01","G_M_Y_FamFor_01","G_M_Y_Korean_01","G_M_Y_Korean_02","G_M_Y_KorLieut_01","G_M_Y_Lost_01","G_M_Y_Lost_02","G_M_Y_Lost_03",
    "G_M_Y_MexGang_01","G_M_Y_MexGoon_01","G_M_Y_MexGoon_02","G_M_Y_MexGoon_03","G_M_Y_PoloGoon_01","G_M_Y_PoloGoon_02","G_M_Y_SalvaBoss_01","G_M_Y_SalvaGoon_01","G_M_Y_SalvaGoon_02","G_M_Y_SalvaGoon_03","G_M_Y_StrPunk_01","G_M_Y_StrPunk_02",
    "HC_Driver","HC_Gunman","HC_Hacker","IG_Abigail","IG_AmandaTownley","IG_Andreas","IG_Ashley","IG_BallasOG","IG_Bankman","IG_Barry","IG_BestMen","IG_Beverly","IG_Brad","IG_Bride","IG_Car3guy1","IG_Car3guy2","IG_Casey",
    "IG_Chef","IG_ChengSr","IG_ChrisFormage","IG_Clay","IG_ClayPain","IG_Cletus","IG_Dale","IG_DaveNorton","IG_Denise","IG_Devin","IG_Dom","IG_Dreyfuss","IG_DrFriedlander","IG_Fabien","IG_FBISuit_01","IG_Floyd","IG_Groom",
    "IG_Hao","IG_Hunter","IG_Janet","ig_JAY_Norris","IG_JewelAss","IG_JimmyBoston","IG_JimmyDiSanto","IG_JoeMinuteMan","ig_JohnnyKlebitz","IG_Josef","IG_Josh","IG_KerryMcIntosh","IG_LamarDavis","IG_Lazlow","IG_LesterCrest",
    "IG_LifeInvad_01","IG_LifeInvad_02","IG_Magenta","IG_Manuel","IG_Marnie","IG_MaryAnn","IG_Maude","IG_Michelle","IG_Milton","IG_Molly","IG_MRK","IG_MrsPhillips","IG_MRS_Thornhill","IG_Natalia","IG_NervousRon","IG_Nigel",
    "IG_Old_Man1A","IG_Old_Man2","IG_Omega","IG_ONeil","IG_Orleans","IG_Ortega","IG_Paper","IG_Patricia","IG_Priest","IG_ProlSec_02","IG_Ramp_Gang","IG_Ramp_Hic","IG_Ramp_Hipster","IG_Ramp_Mex","IG_RoccoPelosi","IG_RussianDrunk",
    "IG_Screen_Writer","IG_SiemonYetarian","IG_Solomon","IG_SteveHains","IG_Stretch","IG_Talina","IG_Tanisha","IG_TaoCheng","IG_TaosTranslator","ig_TennisCoach","IG_Terry","IG_TomEpsilon","IG_Tonya","IG_TracyDiSanto","IG_TrafficWarden",
    "IG_TylerDix","IG_Wade","IG_Zimbor","MP_F_DeadHooker","MP_F_Freemode_01","MP_F_Misty_01","MP_F_StripperLite","MP_G_M_Pros_01","MP_HeadTargets","MP_M_Claude_01","MP_M_ExArmy_01","MP_M_FamDD_01","MP_M_FIBSec_01","MP_M_Freemode_01",
    "MP_M_Marston_01","MP_M_Niko_01","MP_M_ShopKeep_01","MP_S_M_Armoured_01","Player_One","Player_Two","Player_Zero","slod_human","slod_large_quadped","slod_small_quadped","S_F_M_Fembarber","S_F_M_Maid_01","S_F_M_Shop_HIGH",
    "S_F_M_SweatShop_01","S_F_Y_AirHostess_01","S_F_Y_Bartender_01","S_F_Y_Baywatch_01","S_F_Y_Cop_01","S_F_Y_Factory_01","S_F_Y_Hooker_01","S_F_Y_Hooker_02","S_F_Y_Hooker_03","S_F_Y_Migrant_01","S_F_Y_MovPrem_01","S_F_Y_Ranger_01",
    "S_F_Y_Scrubs_01","S_F_Y_Sheriff_01","S_F_Y_Shop_LOW","S_F_Y_Shop_MID","S_F_Y_StripperLite","S_F_Y_Stripper_01","S_F_Y_Stripper_02","S_F_Y_SweatShop_01","S_M_M_AmmuCountry","S_M_M_Armoured_01","S_M_M_Armoured_02","S_M_M_AutoShop_01",
    "S_M_M_AutoShop_02","S_M_M_Bouncer_01","S_M_M_ChemSec_01","S_M_M_CIASec_01","S_M_M_CntryBar_01","S_M_M_DockWork_01","S_M_M_Doctor_01","S_M_M_FIBOffice_01","S_M_M_FIBOffice_02","S_M_M_Gaffer_01","S_M_M_Gardener_01","S_M_M_GenTransport",
    "S_M_M_HairDress_01","S_M_M_HighSec_01","S_M_M_HighSec_02","S_M_M_Janitor","S_M_M_LatHandy_01","S_M_M_LifeInvad_01","S_M_M_Linecook","S_M_M_LSMetro_01","S_M_M_Mariachi_01","S_M_M_Marine_01","S_M_M_Marine_02","S_M_M_Migrant_01",
    "S_M_M_MovAlien_01","S_M_M_MovPrem_01","S_M_M_MovSpace_01","S_M_M_Paramedic_01","S_M_M_Pilot_01","S_M_M_Pilot_02","S_M_M_Postal_01","S_M_M_Postal_02","S_M_M_PrisGuard_01","S_M_M_Scientist_01","S_M_M_Security_01","S_M_M_SnowCop_01",
    "S_M_M_StrPerf_01","S_M_M_StrPreach_01","S_M_M_StrVend_01","S_M_M_Trucker_01","S_M_M_UPS_01","S_M_M_UPS_02","S_M_O_Busker_01","S_M_Y_AirWorker","S_M_Y_AmmuCity_01","S_M_Y_ArmyMech_01","S_M_Y_Autopsy_01","S_M_Y_Barman_01","S_M_Y_BayWatch_01",
    "S_M_Y_BlackOps_01","S_M_Y_BlackOps_02","S_M_Y_BlackOps_03","S_M_Y_BusBoy_01","S_M_Y_Chef_01","S_M_Y_Clown_01","S_M_Y_Construct_01","S_M_Y_Construct_02","S_M_Y_Cop_01","S_M_Y_Dealer_01","S_M_Y_DevinSec_01","S_M_Y_DockWork_01","S_M_Y_Doorman_01",
    "S_M_Y_DWService_01","S_M_Y_DWService_02","S_M_Y_Factory_01","S_M_Y_Fireman_01","S_M_Y_Garbage","S_M_Y_Grip_01","S_M_Y_HwayCop_01","S_M_Y_Marine_01","S_M_Y_Marine_02","S_M_Y_Marine_03","S_M_Y_Mime","S_M_Y_PestCont_01",
    "S_M_Y_Pilot_01","S_M_Y_PrisMuscl_01","S_M_Y_Prisoner_01","S_M_Y_Ranger_01","S_M_Y_Robber_01","S_M_Y_Sheriff_01","S_M_Y_Shop_MASK","S_M_Y_StrVend_01","S_M_Y_Swat_01","S_M_Y_USCG_01","S_M_Y_Valet_01","S_M_Y_Waiter_01",
    "S_M_Y_WinClean_01","S_M_Y_XMech_01","S_M_Y_XMech_02","U_F_M_Corpse_01","U_F_M_Miranda","U_F_M_ProMourn_01","U_F_O_MovieStar","U_F_O_ProlHost_01","U_F_Y_BikerChic","U_F_Y_COMJane","U_F_Y_corpse_01","U_F_Y_corpse_02",
    "U_F_Y_HotPosh_01","U_F_Y_JewelAss_01","U_F_Y_Mistress","U_F_Y_PoppyMich","U_F_Y_Princess","U_F_Y_SpyActress","U_M_M_Aldinapoli","U_M_M_BankMan","U_M_M_BikeHire_01","U_M_M_FIBArchitect","U_M_M_FilmDirector","U_M_M_GlenStank_01",
    "U_M_M_Griff_01","U_M_M_Jesus_01","U_M_M_JewelSec_01","U_M_M_JewelThief","U_M_M_MarkFost","U_M_M_PartyTarget","U_M_M_ProlSec_01","U_M_M_ProMourn_01","U_M_M_RivalPap","U_M_M_SpyActor","U_M_M_WillyFist","U_M_O_FinGuru_01",
    "U_M_O_TapHillBilly","U_M_O_Tramp_01","U_M_Y_Abner","U_M_Y_AntonB",	"U_M_Y_BabyD","U_M_Y_Baygor","U_M_Y_BurgerDrug_01","U_M_Y_Chip","U_M_Y_Cyclist_01","U_M_Y_FIBMugger_01","U_M_Y_Guido_01","U_M_Y_GunVend_01","U_M_Y_Hippie_01",
    "U_M_Y_ImpoRage","U_M_Y_Justin","U_M_Y_Mani","U_M_Y_MilitaryBum","U_M_Y_Paparazzi","U_M_Y_Party_01","U_M_Y_Pogo_01","U_M_Y_Prisoner_01","U_M_Y_ProlDriver_01","U_M_Y_RSRanger_01","U_M_Y_SBike","U_M_Y_StagGrm_01","U_M_Y_Tattoo_01",
    "U_M_Y_Zombie_01",
};

int timeer = 0;
bool risky = false;
bool stream = false;
Vector3 TPCoords;
void TPto(Vector3 Coords)
{
    int Handle = PLAYER::PLAYER_PED_ID();
    if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
    {
        ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
    }
    else
        ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
}

Vector3 get_blip_marker()
{
    static Vector3 zero;
    Vector3 coords;

    bool blipFound = false;
    // search for marker blip
    int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
    for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
    {
        if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
        {
            coords = UI::GET_BLIP_INFO_ID_COORD(i);
            blipFound = true;
            break;
        }
    }
    if (blipFound)
    {
        return coords;
    }

    return zero;
}

void teleport_to_marker(Player target)
{
    Vector3 coords = get_blip_marker();
    Entity e = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
    if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
    {
        e = PED::GET_VEHICLE_PED_IS_USING(e);
    }
    bool groundFound = false;
    static float groundCheckHeight[] =
    { 100.0, 150.0, 50.0, 0.0, 0.3, 0.5, 1.0, 2.0, 3.0, 5.0, 10.0, 15.0, 20.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
    for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
    {
        ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
        //WAIT(100);
        if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
        {
            groundFound = true;
            coords.z += 3.0;
            break;
        }
    }
    if (!groundFound)
    {
        coords.z = 5.0;
    }
    big::Misc::teleporttocoords(target, coords);
}

namespace big
{
    int TestInt = 69;
    float TestFloat = 420;
    int NumberKeyboard() {
        GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 10);
        while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) SYSTEM::WAIT(0);
        if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return 0;
        return atof(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
    }

    void base_tab::NativeUI()
    {
        NativeUI::Checks::Controlls();

        switch (NativeUI::Settings::currentMenu) {

        case mainmenu:
        {
            NativeUI::PremiumTitle2("NXT-G3N");
            if (stream == false) { NativeUI::PremiumTitle(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); }
            else { NativeUI::PremiumTitle(""); }

            NativeUI::MenuOption("Self Options", playermenu);
            NativeUI::MenuOption("Playerlist", onlinemenu_playerlist);
            NativeUI::MenuOption("Online Options", allplayers);
            NativeUI::MenuOption("Weapon Options", weapon);
            NativeUI::MenuOption("Vehicle Options", vehicle);
            NativeUI::MenuOption("Teleport", teleports);
            NativeUI::MenuOption("Misc Options", miscoptions);
            if (risky == true) {
                NativeUI::MenuOption("~r~Recovery", recover);
            }
            NativeUI::MenuOption("Menu Settings", Settings);
        }
        break;
        case teleports:
        {
            NativeUI::Title("Teleport Locations");
            NativeUI::MenuOption("IPLs", ipl);
            if (NativeUI::Option("Mount Chiliad")) 
            {
                Vector3 Coords;
                Coords.x = 496.75f; Coords.y = 5591.17f; Coords.z = 795.03f;
                TPto(Coords);
            }
            if (NativeUI::Option("Maze Bank")) 
            {
                Vector3 Coords;
                Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f;
                TPto(Coords);
            }
            if (NativeUI::Option("Military Base")) 
            {
                Vector3 Coords;
                Coords.x = -2012.8470f; Coords.y = 2956.5270f; Coords.z = 32.8101f;
                TPto(Coords);
            }
            if (NativeUI::Option("Zancudo Tower")) 
            {
                Vector3 Coords;
                Coords.x = -2356.0940; Coords.y = 3248.645; Coords.z = 101.4505;
                TPto(Coords);
            }
            if (NativeUI::Option("Mask Shop")) 
            {
                Vector3 Coords;
                Coords.x = -1338.16; Coords.y = -1278.11; Coords.z = 4.87;
                TPto(Coords);
            }
            if (NativeUI::Option("LS Customs")) 
            {
                Vector3 Coords;
                Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31;
                TPto(Coords);
            }
            if (NativeUI::Option("Ammunation")) 
            {
                Vector3 Coords;
                Coords.x = 247.3652; Coords.y = -45.8777; Coords.z = 69.9411;
                TPto(Coords);
            }
            if (NativeUI::Option("Airport")) 
            {
                Vector3 Coords;
                Coords.x = -1102.2910f; Coords.y = -2894.5160f; Coords.z = 13.9467f;
                TPto(Coords);
            }
            if (NativeUI::Option("Clothes Store")) 
            {
                Vector3 Coords;
                Coords.x = -718.91; Coords.y = -158.16; Coords.z = 37.00;
                TPto(Coords);
            }
            if (NativeUI::Option("Waterfall")) 
            {
                Vector3 Coords;
                Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f;
                TPto(Coords);
            }
            if (NativeUI::Option("FBI")) 
            {
                Vector3 Coords;
                Coords.x = 135.5220f; Coords.y = -749.0003f; Coords.z = 260.0000f;
                TPto(Coords);
            }
            if (NativeUI::Option("Human Labs")) 
            {
                Vector3 Coords;
                Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f;
                TPto(Coords);
            }
            if (NativeUI::Option("MMI")) 
            {
                Vector3 Coords;
                Coords.x = -222.1977; Coords.y = -1185.8500; Coords.z = 23.0294;
                TPto(Coords);
            }
            if (NativeUI::Option("Sandy Shores Airfield")) 
            {
                Vector3 Coords;
                Coords.x = 1741.4960f; Coords.y = 3269.2570f; Coords.z = 41.6014f;
                TPto(Coords);
            }
        }
        break;
        case ipl:
        {
            NativeUI::Title("IPLs");
            if (NativeUI::Option("North Yankton")) 
            {
                STREAMING::REQUEST_IPL("prologue01");
                STREAMING::REQUEST_IPL("Prologue01c");
                STREAMING::REQUEST_IPL("Prologue01d");
                STREAMING::REQUEST_IPL("Prologue01e");
                STREAMING::REQUEST_IPL("Prologue01f");
                STREAMING::REQUEST_IPL("Prologue01g");
                STREAMING::REQUEST_IPL("prologue01h");
                STREAMING::REQUEST_IPL("prologue01i");
                STREAMING::REQUEST_IPL("prologue01j");
                STREAMING::REQUEST_IPL("prologue01k");
                STREAMING::REQUEST_IPL("prologue01z");
                STREAMING::REQUEST_IPL("prologue02");
                STREAMING::REQUEST_IPL("prologue03");
                STREAMING::REQUEST_IPL("prologue03b");
                STREAMING::REQUEST_IPL("prologue03_grv_cov");
                STREAMING::REQUEST_IPL("prologue03_grv_dug");
                STREAMING::REQUEST_IPL("prologue03_grv_fun");
                STREAMING::REQUEST_IPL("prologue04");
                STREAMING::REQUEST_IPL("prologue04b");
                STREAMING::REQUEST_IPL("prologue04_cover");
                STREAMING::REQUEST_IPL("prologue05");
                STREAMING::REQUEST_IPL("prologue05b");
                STREAMING::REQUEST_IPL("prologue06");
                STREAMING::REQUEST_IPL("prologue06b");
                STREAMING::REQUEST_IPL("prologue06_int");
                STREAMING::REQUEST_IPL("prologuerd");
                STREAMING::REQUEST_IPL("prologuerdb");
                STREAMING::REQUEST_IPL("prologue_DistantLights");
                STREAMING::REQUEST_IPL("prologue_grv_torch");
                STREAMING::REQUEST_IPL("prologue_m2_door");
                STREAMING::REQUEST_IPL("prologue_LODLights");
                STREAMING::REQUEST_IPL("DES_ProTree_start");
                Vector3 Coords;
                Coords.x = 3595.39673f; Coords.y = -4893.727f; Coords.z = 115.838394f;
                TPto(Coords);
            }
            if (NativeUI::Option("Porn Yacht")) 
            {
                STREAMING::REQUEST_IPL("smboat");
                Vector3 Coords;
                Coords.x = -2045.8f; Coords.y = -1031.2f; Coords.z = 11.9f;
                TPto(Coords);
            }
            if (NativeUI::Option("Aircraft Carrier")) 
            {
                STREAMING::REQUEST_IPL("hei_carrier");
                STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
                STREAMING::REQUEST_IPL("hei_Carrier_int1");
                STREAMING::REQUEST_IPL("hei_Carrier_int2");
                STREAMING::REQUEST_IPL("hei_Carrier_int3");
                STREAMING::REQUEST_IPL("hei_Carrier_int4");
                STREAMING::REQUEST_IPL("hei_Carrier_int5");
                STREAMING::REQUEST_IPL("hei_Carrier_int6");
                STREAMING::REQUEST_IPL("hei_carrier_LODLights");
                Vector3 Coords;
                Coords.x = 3069.330f; Coords.y = -4632.4f; Coords.z = 15.043f;
                TPto(Coords);
            }
            if (NativeUI::Option("Sunken Cargoship")) 
            {
                STREAMING::REQUEST_IPL("sunkcargoship");
                Vector3 Coords;
                Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 0.0f;
                TPto(Coords);
            }
            if (NativeUI::Option("Hospital")) 
            {
                STREAMING::REQUEST_IPL("RC12B_HospitalInterior");
                STREAMING::REQUEST_IPL("RC12B_Destroyed");
                Vector3 Coords;
                Coords.x = 356.8f; Coords.y = -590.1f; Coords.z = 43.3f;
                TPto(Coords);
            }
            if (NativeUI::Option("Oneil Farm")) 
            {
                STREAMING::REMOVE_IPL("farm_burnt");
                STREAMING::REMOVE_IPL("farm_burnt_props");
                STREAMING::REQUEST_IPL("farm");
                STREAMING::REQUEST_IPL("farm_props");
                STREAMING::REQUEST_IPL("farmint");
                STREAMING::REQUEST_IPL("farmint_cap");
                Vector3 Coords;
                Coords.x = 2441.2f; Coords.y = 4968.5f; Coords.z = 51.7f;
                TPto(Coords);
            }
            if (NativeUI::Option("Life Invader Office")) 
            {
                STREAMING::REQUEST_IPL("facelobby");
                STREAMING::REQUEST_IPL("facelobbyfake");
                Vector3 Coords;
                Coords.x = -1047.9f; Coords.y = -233.0f; Coords.z = 39.0f;
                TPto(Coords);
            }
            if (NativeUI::Option("Cargoship")) 
            {
                STREAMING::REQUEST_IPL("cargoship");
                Vector3 Coords;
                Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 9.3192f;
                TPto(Coords);
            }
            if (NativeUI::Option("Jewelry Store")) 
            {
                STREAMING::REQUEST_IPL("jewel2fake");
                STREAMING::REQUEST_IPL("post_hiest_unload");
                STREAMING::REQUEST_IPL("bh1_16_refurb");
                Vector3 Coords;
                Coords.x = -630.4f; Coords.y = -236.7f; Coords.z = 40.0f;
                TPto(Coords);
            }
            if (NativeUI::Option("Morgue")) 
            {
                STREAMING::REQUEST_IPL("Coroner_Int_on");
                Vector3 Coords;
                Coords.x = 244.9f; Coords.y = -1374.7f; Coords.z = 39.5f;
                TPto(Coords);
            }

        }
        break;
        case weapon:
        {
            NativeUI::Title("Weapons");
            if (NativeUI::Option("Give All Weapons")) 
            {
                uint Weapons[] = { 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D };
                for (int i = 0; i < (sizeof(Weapons) / 4); i++) 
                {
                    WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Weapons[i], 9999, 1);
                }
            }
            NativeUI::Bool("Infinite Ammo", Gun::inf, [] { Gun::noreloadv(Gun::inf); });
            NativeUI::Bool("Explosive Ammo", Gun::expammo, [] {Gun::Expammos(Gun::expammo); });
            NativeUI::Bool("Fire Ammo", Gun::fireammo, [] {Gun::Fireammos(Gun::fireammo); });
            NativeUI::Bool("Explosive Meele", Gun::expmeel, [] {Gun::Expmeels(Gun::expmeel); });
            NativeUI::Bool("Rainbow Gun", Gun::rbgun, [] { Gun::RBGuner(Gun::rbgun); });
            NativeUI::Bool("Rapid Fire", Gun::rapidfire);
        }
        break;
        case weatheroptions:
        {
            NativeUI::Title("Weather Options");
            if (NativeUI::Option("Sun")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Clear"); }
            if (NativeUI::Option("Rain")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Clearing"); }
            if (NativeUI::Option("Snow")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Snowlight"); }
            if (NativeUI::Option("Thunder")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Thunder"); }
            if (NativeUI::Option("Blizzard")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Blizzard"); }
            if (NativeUI::Option("Overcast")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Overcast"); }
            if (NativeUI::Option("Foggy")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Foggy"); }
            if (NativeUI::Option("Smog")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Smog"); }
            if (NativeUI::Option("Clouds")) { GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("Clouds"); }

        }
        break;
        case miscoptions:
        {
            NativeUI::Title("Misc Options");
            NativeUI::MenuOption("Weather", weatheroptions);
            NativeUI::Bool("Kill Peds", Misc::killpedsbool);
            NativeUI::Bool("Explode Peds", Misc::explodepedsbool);
            NativeUI::Bool("Explode Cars", Misc::explodenearbyvehiclesbool);
            NativeUI::Bool("Delete Cars", Misc::deletenearbyvehiclesbool);
            NativeUI::Bool("Peds Drop 10K", Misc::playertenkped);
            NativeUI::Int("Choose Time", timeer, 0, 24);
            if (NativeUI::Option("Set Time")) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(timeer, 0, 0); }
        }
        break;
        case allplayers:
        {
            NativeUI::Title("All Players");
            NativeUI::Bool("ESP", Online::esper, [] {});
            if (NativeUI::Option("Take Weps in the Lobby")) 
            {
                for (int i = 0; i < 32; i++)
                {
                    if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) 
                    {
                        if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_PED_ID())
                        {
                            Player allplayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
                            if (!(features::cstrcmp(PLAYER::GET_PLAYER_NAME(i), "-")))
                            {
                                WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(allplayers), true);
                            }
                        }
                    }
                }
            }
            if (NativeUI::Option("Give Weps in the Lobby")) 
            {

                for (int i = 0; i < 32; i++)
                {
                    if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) 
                    {
                        Player allplayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
                        if (!(features::cstrcmp(PLAYER::GET_PLAYER_NAME(i), "-")))
                        {
                            if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_PED_ID())
                            {
                                uint Weapons[] = { 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D };
                                for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
                                    WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(allplayers), Weapons[i], 9999, 1);
                                }
                            }
                        }
                    }
                }
            }
            if (NativeUI::Option("Cage All Player")) 
            {
                Misc::trapall();
            }
            if (NativeUI::Option("Teleport all to Me")) 
            {
                int Me = PLAYER::PLAYER_PED_ID();
                Vector3 MyPosition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Me, 0.0, 0.0, 0.0);
                Misc::teleportallcoords(MyPosition);
            }
            //  Menu::MenuOption("Force Animation All", forceanall);
            if (NativeUI::Option("Kill Lobby")) 
            {

                for (int i = 0; i < 32; i++)
                {
                    Vector3 MyPosition = { -15000, -15000, -50 };
                    Misc::teleportallcoordsns(MyPosition);
                }
            }
            if (NativeUI::Option("Kick All From Car")) 
            {
                for (int i = 0; i < 32; i++)
                {
                    if (i != PLAYER::PLAYER_ID())
                    {
                        features::RequestControlOfEnt(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
                        AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
                        AI::CLEAR_PED_TASKS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
                        AI::CLEAR_PED_SECONDARY_TASK(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
                    }
                }
            };
            if (NativeUI::Option("Explode All")) 
            {
                for (int i = 0; i < 33; i++)
                {
                    if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) == PLAYER::PLAYER_PED_ID()) continue;
                    {
                        Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
                        FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 1000.f, true, false, 100.f);
                    }
                }
            }
        }
        break;
        case playermenu:
        {
            NativeUI::Title("Self Options");
            NativeUI::MenuOption("Model Changer", modelchanger);
            NativeUI::MenuOption("Animations", anim);
            if (risky == true) { NativeUI::MenuOption("Money", moneyoptions); }
            NativeUI::Bool("God Mode", Local::god, [] { Local::God(Local::god); });
            NativeUI::Bool("Invisible", Local::invisibility, [] { Local::Invisibility(Local::invisibility); });
            NativeUI::Bool("Super Jump", Local::playersuperjump, [] { Local::SuperJump(Local::playersuperjump); });
            NativeUI::Bool("Tiny Player", Local::betiny, [] { Local::TinyPlayer(Local::betiny); });
            NativeUI::Bool("Mobile Radio", Local::mobileRadio, [] { Local::mobilevoid(Local::mobileRadio); });
            if (NativeUI::Option("New Look")) { PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true); }
            NativeUI::Option("Cleaner", [] { int Ped = PLAYER::PLAYER_PED_ID(); PED::CLEAR_PED_BLOOD_DAMAGE(Ped); PED::RESET_PED_VISIBLE_DAMAGE(Ped); });
        }
        break;
        case moneyoptions:
        {
            NativeUI::Title("$$$");
            NativeUI::Option("~r~These methodes are Risky.");
            NativeUI::Option("----------");
            NativeUI::Int("Amount", Misc::amount, 0, 90000000, 1000000);
            NativeUI::Bool("Bank Cash", Misc::banked);
            NativeUI::Bool("Give Cash", Misc::giver);
            NativeUI::Option("----------");
            NativeUI::Bool("~r~Drop 39999", Misc::savenewdrop, [] {Misc::cashdrop(Misc::savenewdrop); });
            if (NativeUI::Option("Bank Cash 1 Mil")) {
                Misc::deposit(1000000);
            }
            if (NativeUI::Option("Withdraw 1 Mil")) {
                Misc::withdraw(1000000);
            }
            if (NativeUI::Option("Bank Cash 10 Mil")) {
                Misc::deposit(10000000);
            }
            if (NativeUI::Option("Withdraw 10 Mil")) {
                Misc::withdraw(10000000);
            }
            if (NativeUI::Option("Bank Cash 100 Mil")) {
                Misc::deposit(100000000);
            }
            if (NativeUI::Option("Withdraw 100 Mil")) {
                Misc::withdraw(100000000);
            }
        }
        break;
        case modelchanger:
        {
            NativeUI::Title("Model Changer");
            for (int i = 0; i < ARRAYSIZE(pedModels); i++)
            {
                if (NativeUI::Option(pedModels[i]))
                {
                    DWORD model = GAMEPLAY::GET_HASH_KEY(pedModels[i]);
                    STREAMING::REQUEST_MODEL(model);
                    while (!STREAMING::HAS_MODEL_LOADED(model)) features::WAIT(0);
                    PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
                    PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
                    features::WAIT(10);
                    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
                    features::WAIT(10);
                }
            }
        }
        break;
        case anim:
        {
            NativeUI::Title("Animations");
            NativeUI::MenuOption("Scenarios", senas);
            if (NativeUI::Option("Clear Animation")) { Misc::clearanim(); }
            if (NativeUI::Option("Sex Receiver")) { Misc::doAnimation("rcmpaparazzo_2", "shag_loop_poppy"); }
            if (NativeUI::Option("Sex Giver")) { Misc::doAnimation("rcmpaparazzo_2", "shag_loop_a"); }
            if (NativeUI::Option("Stripper Dance")) { Misc::doAnimation("mini@strip_club@private_dance@part1", "priv_dance_p1"); }
            if (NativeUI::Option("Pole Dance")) { Misc::doAnimation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); }
            if (NativeUI::Option("Push Ups")) { Misc::doAnimation("amb@world_human_push_ups@male@base", "base"); }
            if (NativeUI::Option("Sit Ups")) { Misc::doAnimation("amb@world_human_sit_ups@male@base", "base"); }
            if (NativeUI::Option("Celebrate")) { Misc::doAnimation("rcmfanatic1celebrate", "celebrate"); }
            if (NativeUI::Option("Electrocution")) { Misc::doAnimation("ragdoll@human", "electrocute"); }
            if (NativeUI::Option("Suicide")) { Misc::doAnimation("mp_suicide", "pistol"); }
            if (NativeUI::Option("Showering")) { Misc::doAnimation("mp_safehouseshower@male@", "male_shower_idle_b"); }
        }
        break;
        case senas:
        {
            NativeUI::Title("Scenarios");
            if (NativeUI::Option("Kill Animation")) AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
            if (NativeUI::Option("Paparizzi")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PAPARAZZI", 0, true);
            if (NativeUI::Option("Drug Dealer")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRUG_DEALER_HARD", 0, true);
            if (NativeUI::Option("Drinking Coffee")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_AA_COFFEE", 0, true);
            if (NativeUI::Option("Playing Instruments")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, true);
            if (NativeUI::Option("Flexing")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FLEX", 0, true);
            if (NativeUI::Option("Jogging")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_JOG_STANDING", 0, true);
            if (NativeUI::Option("Binoculars")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BINOCULARS", 0, true);
            if (NativeUI::Option("Clipboard")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CLIPBOARD", 0, true);
            if (NativeUI::Option("Bench Press")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, true);
            if (NativeUI::Option("Chin Ups")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, true);
            if (NativeUI::Option("BBQ")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BBQ", 0, true);
            if (NativeUI::Option("Superhero")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUPERHERO", 0, true);
            if (NativeUI::Option("Fishing")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_FISHING", 0, true);
            if (NativeUI::Option("Security")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, true);
            if (NativeUI::Option("Leaf Blower")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, true);
            if (NativeUI::Option("Film Shocking")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true);
            if (NativeUI::Option("Idle Cop")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_COP_IDLES", 0, true);
            if (NativeUI::Option("Drinking")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRINKING", 0, true);
            if (NativeUI::Option("Golf Player")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GOLF_PLAYER", 0, true);
            if (NativeUI::Option("Welding")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_WELDING", 0, true);
            if (NativeUI::Option("Smoking Pot")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING_POT", 0, true);
            if (NativeUI::Option("Hammering")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HAMMERING", 0, true);
            if (NativeUI::Option("Tennis")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TENNIS_PLAYER", 0, true);
            if (NativeUI::Option("Drilling")) AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CONST_DRILL", 0, true);
        }
        break;
        case onlinemenu_playerlist:
        {
            NativeUI::Title("Player List");

            for (int i = 0; i < 32; ++i) 
            {
                if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) 
                {
                    NativeUI::MenuOption(PLAYER::GET_PLAYER_NAME(i), onlinemenu_selected) ? Online::selectedPlayer = i : NULL;
                }
            }
        }
        break;
        case onlinemenu_selected:
        {
            Online::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Online::selectedPlayer), Online::selectedPlayer);
            NativeUI::Title(PLAYER::GET_PLAYER_NAME(Online::selectedPlayer));
            NativeUI::MenuOption("Attach things to Him", attachoptions);
            if (Online::selectedPlayer != PLAYER::PLAYER_ID()) { NativeUI::MenuOption("Force Animation", forcean); }
            if (Online::selectedPlayer != PLAYER::PLAYER_ID()) { NativeUI::MenuOption("TP Options", tpother); }
            //NativeUI::MenuOption("Effects", PTFXO);


            NativeUI::Bool("Water Loop", Online::playerwaterloop[Online::selectedPlayer], [] { Online::WaterLoop(Online::playerwaterloop[Online::selectedPlayer]); });
            NativeUI::Bool("Fire Loop", Online::playerfireloop[Online::selectedPlayer], [] { Online::FireLoop(Online::playerfireloop[Online::selectedPlayer]); });
            NativeUI::Bool("Freeze", Online::freezed[Online::selectedPlayer], [] { Online::Freezer(Online::freezed[Online::selectedPlayer]); });
            NativeUI::Bool("Fuck Handling", Online::fuckedhandling[Online::selectedPlayer], [] { Online::fuckhandling(Online::fuckedhandling[Online::selectedPlayer]); });
            NativeUI::Bool("Shake Cam", Online::camshaker[Online::selectedPlayer], [] { Online::shakecam(Online::camshaker[Online::selectedPlayer]); });
            if (Online::selectedPlayer != PLAYER::PLAYER_ID()) { NativeUI::Bool("Spectate", Online::spectate[Online::selectedPlayer], [] { Online::specter(Online::spectate[Online::selectedPlayer]); }); }
            NativeUI::Bool("Explosion Loop", Online::exploder[Online::selectedPlayer], [] { Online::explodeloop(Online::exploder[Online::selectedPlayer]); });
            if (NativeUI::Option("Explode him")) 
            {
                Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), false);
                FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 1000.f, true, false, 1000.f);
            }
            if (NativeUI::Option("Kick him out of Car")) 
            {
                Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer);
                features::RequestControlOfEnt(playerPed);
                AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
                AI::CLEAR_PED_TASKS(playerPed);
                AI::CLEAR_PED_SECONDARY_TASK(playerPed);
            }
            if (NativeUI::Option("Kill Player")) 
            {

                int selectedPed = Online::selectedPlayer;
                Vector3 MyPosition = { -15000, -15000, -50 };
                Misc::teleporttocoords(selectedPed, MyPosition);
            }
            if (NativeUI::Option("Slingshot Car")) 
            {
                NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), true));
                if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), true)));
                {
                    ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
                }
            }
            if (NativeUI::Option("Clone Player"))
            {
                PED::CLONE_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), 1, 1, 1);
            }
            if (NativeUI::Option("Cage Player")) 
            {
                Online::trapcage(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer));
            }
            if (PLAYER::PLAYER_PED_ID() == NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0)) 
            {
                if (NativeUI::Option("~g~Kick his Ass")) 
                {
                    if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer)))
                    {
                        NETWORK::NETWORK_SESSION_KICK_PLAYER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer));
                    }
                }
            }
            else 
            {
                if (NativeUI::Option("~r~Kick his Ass")) 
                {
                    if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer)))
                    {
                        NETWORK::NETWORK_SESSION_KICK_PLAYER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer));
                    }
                }
            }
            if (NativeUI::Option("Give All Weapons")) 
            {
                uint Weapons[] = { 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D };
                for (int i = 0; i < (sizeof(Weapons) / 4); i++) 
                {
                    WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), Weapons[i], 9999, 1);
                }
            }
            if (NativeUI::Option("Take All Weapons")) 
            {
                WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), true);
            }
        }
        break;
        case forcean:
        {
            NativeUI::Title("Force Animation");
            if (NativeUI::Option("Stop Animation")) { AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer)); }
            if (NativeUI::Option("Sex Receiver")) { Misc::animatePlayer(Online::selectedPlayer, "rcmpaparazzo_2", "shag_loop_poppy"); }
            if (NativeUI::Option("Sex Giver")) { Misc::animatePlayer(Online::selectedPlayer, "rcmpaparazzo_2", "shag_loop_a"); }
            if (NativeUI::Option("Stripper Dance")) { Misc::animatePlayer(Online::selectedPlayer, "mini@strip_club@private_dance@part1", "priv_dance_p1"); }
            if (NativeUI::Option("Pole Dance")) { Misc::animatePlayer(Online::selectedPlayer, "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); }
            if (NativeUI::Option("Push Ups")) { Misc::animatePlayer(Online::selectedPlayer, "amb@world_human_push_ups@male@base", "base"); }
            if (NativeUI::Option("Sit Ups")) { Misc::animatePlayer(Online::selectedPlayer, "amb@world_human_sit_ups@male@base", "base"); }
            if (NativeUI::Option("Celebrate")) { Misc::animatePlayer(Online::selectedPlayer, "rcmfanatic1celebrate", "celebrate"); }
            if (NativeUI::Option("Electrocution")) { Misc::animatePlayer(Online::selectedPlayer, "ragdoll@human", "electrocute"); }
            if (NativeUI::Option("Suicide")) { Misc::animatePlayer(Online::selectedPlayer, "mp_suicide", "pistol"); }
            if (NativeUI::Option("Showering")) { Misc::animatePlayer(Online::selectedPlayer, "mp_safehouseshower@male@", "male_shower_idle_b"); }

        }
        break;
        case attachoptions:
        {
            NativeUI::Title("Attach Options");
            if (NativeUI::Option("Plate")) { Misc::attachobjects2("p_oil_slick_01"); }
            if (NativeUI::Option("EMP")) { Misc::attachobjects2("hei_prop_heist_emp"); }
            if (NativeUI::Option("Orange Ball")) { Misc::attachobjects2("prop_juicestand"); }
            if (NativeUI::Option("Weed")) { Misc::attachobjects2("prop_weed_01"); }
            if (NativeUI::Option("Safe")) { Misc::attachobjects2("p_v_43_safe_s"); }
            if (NativeUI::Option("Ufo")) { Misc::attachobjects2("p_spinning_anus_s"); }
            if (NativeUI::Option("Toilet")) { Misc::attachobjects2("prop_ld_toilet_01"); }
            if (NativeUI::Option("Christmas Tree")) { Misc::attachobjects2("prop_xmas_tree_int"); }
            if (NativeUI::Option("Windmill")) { Misc::attachobjects2("prop_windmill_01"); }
            if (NativeUI::Option("Radar")) { Misc::attachobjects2("prop_air_bigradar"); }
            char* objects[136] = { "prop_bskball_01", "PROP_MP_RAMP_03", "PROP_MP_RAMP_02", "PROP_MP_RAMP_01", "PROP_JETSKI_RAMP_01", "PROP_WATER_RAMP_03", "PROP_VEND_SNAK_01", "PROP_TRI_START_BANNER", "PROP_TRI_FINISH_BANNER", "PROP_TEMP_BLOCK_BLOCKER", "PROP_SLUICEGATEL", "PROP_SKIP_08A", "PROP_SAM_01", "PROP_RUB_CONT_01B", "PROP_ROADCONE01A", "PROP_MP_ARROW_BARRIER_01", "PROP_HOTEL_CLOCK_01", "PROP_LIFEBLURB_02", "PROP_COFFIN_02B", "PROP_MP_NUM_1", "PROP_MP_NUM_2", "PROP_MP_NUM_3", "PROP_MP_NUM_4", "PROP_MP_NUM_5", "PROP_MP_NUM_6", "PROP_MP_NUM_7", "PROP_MP_NUM_8", "PROP_MP_NUM_9", "prop_xmas_tree_int", "prop_bumper_car_01", "prop_beer_neon_01", "prop_space_rifle", "prop_dummy_01", "prop_rub_trolley01a", "prop_wheelchair_01_s", "PROP_CS_KATANA_01", "PROP_CS_DILDO_01", "prop_armchair_01", "prop_bin_04a", "prop_chair_01a", "prop_dog_cage_01", "prop_dummy_plane", "prop_golf_bag_01", "prop_arcade_01", "hei_prop_heist_emp", "prop_alien_egg_01", "prop_air_towbar_01", "hei_prop_heist_tug", "prop_air_luggtrolley", "PROP_CUP_SAUCER_01", "prop_wheelchair_01", "prop_ld_toilet_01", "prop_acc_guitar_01", "prop_bank_vaultdoor", "p_v_43_safe_s", "p_spinning_anus_s", "prop_can_canoe", "prop_air_woodsteps", "Prop_weed_01", "prop_a_trailer_door_01", "prop_apple_box_01", "prop_air_fueltrail1", "prop_barrel_02a", "prop_barrel_float_1", "prop_barrier_wat_03b", "prop_air_fueltrail2", "prop_air_propeller01", "prop_windmill_01", "prop_Ld_ferris_wheel", "p_tram_crash_s", "p_oil_slick_01", "p_ld_stinger_s", "p_ld_soc_ball_01", "prop_juicestand", "p_oil_pjack_01_s", "prop_barbell_01", "prop_barbell_100kg", "p_parachute1_s", "p_cablecar_s", "prop_beach_fire", "prop_lev_des_barge_02", "prop_lev_des_barge_01", "prop_a_base_bars_01", "prop_beach_bars_01", "prop_air_bigradar", "prop_weed_pallet", "prop_artifact_01", "prop_attache_case_01", "prop_large_gold", "prop_roller_car_01", "prop_water_corpse_01", "prop_water_corpse_02", "prop_dummy_01", "prop_atm_01", "hei_prop_carrier_docklight_01", "hei_prop_carrier_liferafts", "hei_prop_carrier_ord_03", "hei_prop_carrier_defense_02", "hei_prop_carrier_defense_01", "hei_prop_carrier_radar_1", "hei_prop_carrier_radar_2", "hei_prop_hei_bust_01", "hei_prop_wall_alarm_on", "hei_prop_wall_light_10a_cr", "prop_afsign_amun", "prop_afsign_vbike", "prop_aircon_l_01", "prop_aircon_l_02", "prop_aircon_l_03", "prop_aircon_l_04", "prop_airhockey_01", "prop_air_bagloader", "prop_air_blastfence_01", "prop_air_blastfence_02", "prop_air_cargo_01a", "prop_air_chock_01", "prop_air_chock_03", "prop_air_gasbogey_01", "prop_air_generator_03", "prop_air_stair_02", "prop_amb_40oz_02", "prop_amb_40oz_03", "prop_amb_beer_bottle", "prop_amb_donut", "prop_amb_handbag_01", "prop_amp_01", "prop_anim_cash_pile_02", "prop_asteroid_01", "prop_arm_wrestle_01", "prop_ballistic_shield", "prop_bank_shutter", "prop_barier_conc_02b", "prop_barier_conc_05a", "prop_barrel_01a", "prop_bar_stool_01", "prop_basejump_target_01" };

            if (NativeUI::Option("Delete All Objects")) 
            {
                for (int i = 0; i < 5; i++) 
                {
                    Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), 1);
                    GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
                    GAMEPLAY::CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, 2, 0);
                    GAMEPLAY::CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, 2, 0, 0, 0, 0, 0);
                    for (int i = 0; i < 136; i++) 
                    {
                        Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 4.0, GAMEPLAY::GET_HASH_KEY(objects[i]), 0, 0, 1);

                        if (ENTITY::DOES_ENTITY_EXIST(obj) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer))) 
                        {
                            features::RequestControlOfEnt(obj);
                            int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj);
                            NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
                            features::RequestControlOfid(netID);
                            ENTITY::DETACH_ENTITY(obj, 1, 1);
                            if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(obj)) 
                            {
                                ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, 1, 1);
                                ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&obj);
                                ENTITY::DELETE_ENTITY(&obj);
                            }
                        }
                    }
                }
            }
        }
        break;
        case vehicle:
        {
            NativeUI::Title("Vehicle Options");
            // Menu::MenuOption("Los Santos Customs", lsc);
             //Menu::MenuOption("Number Plate", plateoptions);
            NativeUI::MenuOption("Vehicle Spawner", vehspawner);
            if (NativeUI::Bool("Car Godmode", Car::cargodmodebool)) { Car::cargodmode(); }
            NativeUI::Bool("Engine Allways On", Car::enginealwaysonbool, [] { Car::enginealwayson(Car::enginealwaysonbool); });
            NativeUI::Bool("Horn Boost", Car::boostbool, [] { Car::carboost(Car::boostbool); });
            // Menu::Bool("Flighing Car", Features::fcbool, [] { Features::FlyingCarLoop(Features::fcbool); });
            if (NativeUI::Option("Fix Car")) 
            {
                uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
                VEHICLE::SET_VEHICLE_FIXED(Vehicle);
                VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle);
                VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0);
            }
            if (NativeUI::Option("Max Car")) 
            {
                Car::maxvehicle();
            }
            if (NativeUI::Option("Flip Car")) 
            {
                Car::flipup();
            }
            if (NativeUI::Option("Open Doors")) 
            {
                VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, true, false);
                VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, true, false);
                VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, true, false);
                VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, true, false);
                VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 4, true, false);
                VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 5, true, false);
                VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 6, true, false);
                VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 7, true, false);
            }
            if (NativeUI::Option("Close Doors")) 
            {
                VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
            }
        }
        break;
        case vehspawner:
        {
            NativeUI::Title("Vehicle Spawner");
            NativeUI::MenuOption("Super", Super);
            NativeUI::MenuOption("Sports", Sports);
            NativeUI::MenuOption("Sport Classic", SportClassic);
            NativeUI::MenuOption("Offroad", Offroad);
            NativeUI::MenuOption("Sedans", Sedans);
            NativeUI::MenuOption("Coupes", Coupes);
            NativeUI::MenuOption("Muscle", Muscle);
            NativeUI::MenuOption("Boats", Boats);
            NativeUI::MenuOption("Commercial", Commercial);
            NativeUI::MenuOption("Compacts", Compacts);
            NativeUI::MenuOption("Cycles", Cycles);
            NativeUI::MenuOption("Emergency", Emergency);
            NativeUI::MenuOption("Helicopters", Helicopters);
            NativeUI::MenuOption("Industrial", Industrial);
            NativeUI::MenuOption("Military", Military);
            NativeUI::MenuOption("Motorcycles", Motorcycles);
            NativeUI::MenuOption("Planes", Planes);
            NativeUI::MenuOption("Service", Service);
            NativeUI::MenuOption("SUV", SUV);
            NativeUI::MenuOption("Trailer", Trailer);
            NativeUI::MenuOption("Trains", Trains);
            NativeUI::MenuOption("Utility", Utility);
            NativeUI::MenuOption("Vans", Vans);
            NativeUI::Bool("Spawn in Car", Car::spawnincar);
            NativeUI::Bool("Spawn Maxed", Car::spawnmaxed);

            break;
        case Super:
            NativeUI::Title("Super");
            for (auto car : Super1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Sports:
            NativeUI::Title("Sports");
            for (auto car : Sports1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case SportClassic:
            NativeUI::Title("Sports Classic");
            for (auto car : SportsClassics1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Offroad:
            NativeUI::Title("Offroad");
            for (auto car : OffRoad1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Sedans:
            NativeUI::Title("Sedans");
            for (auto car : Sedans1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Coupes:
            NativeUI::Title("Coupes");
            for (auto car : Coupes1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Muscle:
            NativeUI::Title("Muscle");
            for (auto car : Muscle1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Boats:
            NativeUI::Title("Boats");
            for (auto car : Boats1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Commercial:
            NativeUI::Title("Commercial");
            for (auto car : Commercial1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Compacts:
            NativeUI::Title("Compacts");
            for (auto car : Compacts1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Cycles:
            NativeUI::Title("Cycles");
            for (auto car : Cycles1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Emergency:
            NativeUI::Title("Emergency");
            for (auto car : Emergency1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Helicopters:
            NativeUI::Title("Helicopters");
            for (auto car : Helicopters1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Industrial:
            NativeUI::Title("Industrial");
            for (auto car : Industrial1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Military:
            NativeUI::Title("Military");
            for (auto car : Military1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Motorcycles:
            NativeUI::Title("Motorcycles");
            for (auto car : Motorcycles1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Planes:
            NativeUI::Title("Planes");
            for (auto car : Planes1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Service:
            NativeUI::Title("Service");
            for (auto car : Service1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case SUV:
            NativeUI::Title("SUV");
            for (auto car : SUVs1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Trailer:
            NativeUI::Title("Trailer");
            for (auto car : Trailer1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Trains:
            NativeUI::Title("Trains");
            for (auto car : Trains1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Utility:
            NativeUI::Title("Utility");
            for (auto car : Utility1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        case Vans:
            NativeUI::Title("Vans");
            for (auto car : Vans1) { NativeUI::Option(car, [car] { Car::spawn_vehicle(car); }); }
            break;
        }
        break;
        case recover:
        {
            NativeUI::Title("Recovery");
            if (NativeUI::Option("Full Recovery")) 
            {
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), Online::Levels[120], 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);

                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_8"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_9"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_10"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_11"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_12"), -1, 1);

                STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_USJS_FOUND"), 50, 0);
                STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1, 0);
                STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
                STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 0);
                STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 0);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);

                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_31"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
            }
            if (NativeUI::Option("Clear Badsport Stats")) 
            {
                STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MPPLY_OVERALL_BADSPORT"), 0.0f, TRUE);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_DESTROYED_PVEHICLES"), 0, TRUE);
                STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BADSPORT_MESSAGE"), 0, TRUE);
            }
            if (NativeUI::Option("Rank Set 88")) 
            {
                Online::SetRank(88);
            }
            if (NativeUI::Option("Rank Set 100")) 
            {
                Online::SetRank(100);
            }
            if (NativeUI::Option("Rank Set 120")) 
            {
                Online::SetRank(120);
            }
            if (NativeUI::Option("Rank Set 200")) 
            {
                Online::SetRank(200);
            }
            if (NativeUI::Option("Rank Set 420")) 
            {
                Online::SetRank(420);
            }
            if (NativeUI::Option("Rank Set 500")) 
            {
                Online::SetRank(500);
            }
            if (NativeUI::Option("Rank Set 1000")) 
            {
                Online::SetRank(1000);
            }
            if (NativeUI::Option("Rank Set 1337")) 
            {
                Online::SetRank(1337);
            }
            if (NativeUI::Option("Rank Set 8000")) 
            {
                Online::SetRank(8000);
            }
        }
        break;
        case Settings:
        {
            NativeUI::Title("Settings");
            NativeUI::MenuOption("Protection", protection);
            NativeUI::MenuOption("Colors", Theme);
            NativeUI::Option("~HUD_COLOUR_GOLD~Social Club Account:");
            NativeUI::Option(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()));
            if (NativeUI::Option("Unload")) { g_running = false; };
            if (NativeUI::Option("Close GTA")) { exit(0); };
        }
        break;
        case protection:
        {
            NativeUI::Title("Protection");
            NativeUI::Bool("Risky Mode", risky);
            NativeUI::Bool("Fame Mode (Hide Name)", stream);
        }
        break;
        case Theme:
        {
            NativeUI::Title("Colors");
            NativeUI::MenuOption("Theme Loader", Themes);
            NativeUI::MenuOption("Title Background", settingstitlerect);
            NativeUI::MenuOption("Selection Box", settingsscroller);
            NativeUI::MenuOption("Option Text", settingsoptiontext);
            if (NativeUI::Option("MenuX plus")) 
            {
                if (NativeUI::Settings::menuX < 0.81f) NativeUI::Settings::menuX += 0.01f;
            }
            if (NativeUI::Option("MenuX minus")) 
            {
                if (NativeUI::Settings::menuX > 0.17f) NativeUI::Settings::menuX -= 0.01f;
            }
        }
        break;
        case Themes:
        {
            NativeUI::Title("Theme Colors");
            if (NativeUI::Option("Red Theme")) 
            {
                NativeUI::Settings::titleRect = { 100, 0, 0, 255 };
                NativeUI::Settings::optionRect = { 50, 50, 50, 100 };
                NativeUI::Settings::scroller = { 100, 0, 0, 255 };
            }
            if (NativeUI::Option("Blue Theme")) 
            {
                NativeUI::Settings::titleRect = { 0, 0, 200, 255 };
                NativeUI::Settings::optionRect = { 50, 50, 50, 100 };
                NativeUI::Settings::scroller = { 0, 0, 200, 255 };
            }
            if (NativeUI::Option("Green Theme")) 
            {
                NativeUI::Settings::titleRect = { 0, 180, 0, 255 };
                NativeUI::Settings::optionRect = { 50, 50, 50, 100 };
                NativeUI::Settings::scroller = { 0, 0, 180, 255 };
            }
            if (NativeUI::Option("Purple Theme"))
            {
                NativeUI::Settings::titleRect = { 146, 39, 245, 255 };
                NativeUI::Settings::optionRect = { 50, 50, 50, 100 };
                NativeUI::Settings::scroller = { 146, 39, 245, 255 };
            }
            if (NativeUI::Option("Load Default Theme")) 
            {
                NativeUI::Settings::titleRect = { 52, 73, 94, 255 };
                NativeUI::Settings::scroller = { 121, 135, 136, 150 };
                NativeUI::Settings::optionRect = { 2, 41, 58, 255 };
            }
        }
        break;
        case settingstitlerect:
        {
            NativeUI::Title("Title Rect");
            if (NativeUI::Int("Red", NativeUI::Settings::titleRect.r, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
                    NativeUI::Settings::titleRect.r = NumberKeyboard();
                }
            }
            if (NativeUI::Int("Green", NativeUI::Settings::titleRect.g, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
                    NativeUI::Settings::titleRect.g = NumberKeyboard();
                }
            }
            if (NativeUI::Int("Blue", NativeUI::Settings::titleRect.b, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
                    NativeUI::Settings::titleRect.b = NumberKeyboard();
                }
            }
            if (NativeUI::Int("Opacity", NativeUI::Settings::titleRect.a, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
                    NativeUI::Settings::titleRect.a = NumberKeyboard();
                }
            }
        }
        break;
        case settingsoptiontext:
        {
            NativeUI::Title("Option Text");
            if (NativeUI::Int("Red", NativeUI::Settings::optionText.r, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
                    NativeUI::Settings::optionText.r = NumberKeyboard();
                }
            }
            if (NativeUI::Int("Green", NativeUI::Settings::optionText.g, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
                    NativeUI::Settings::optionText.g = NumberKeyboard();
                }
            }
            if (NativeUI::Int("Blue", NativeUI::Settings::optionText.b, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
                    NativeUI::Settings::optionText.b = NumberKeyboard();
                }
            }
            if (NativeUI::Int("Opacity", NativeUI::Settings::optionText.a, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
                    NativeUI::Settings::optionText.a = NumberKeyboard();
                }
            }
            NativeUI::MenuOption("Font", font);
        }
        break;
        case font:
        {
            NativeUI::Title("Font");
            if (NativeUI::Option("Standard Font")) { NativeUI::Settings::optionText.f = 6; }
            if (NativeUI::Option("Chalet London")) { NativeUI::Settings::optionText.f = 0; }
            if (NativeUI::Option("House Script")) { NativeUI::Settings::optionText.f = 1; }
            if (NativeUI::Option("Monospace")) { NativeUI::Settings::optionText.f = 2; }
            if (NativeUI::Option("Wing Dings")) { NativeUI::Settings::optionText.f = 3; }
            if (NativeUI::Option("Chalet Comprime Cologne")) { NativeUI::Settings::optionText.f = 4; }
            if (NativeUI::Option("Pricedown")) { NativeUI::Settings::optionText.f = 7; }
        }
        break;
        case settingsscroller:
        {
            NativeUI::Title("Scroller");
            if (NativeUI::Int("Red", NativeUI::Settings::scroller.r, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) 
                {
                    NativeUI::Settings::scroller.r = NumberKeyboard();
                }
            }
            if (NativeUI::Int("Green", NativeUI::Settings::scroller.g, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) 
                {
                    NativeUI::Settings::scroller.g = NumberKeyboard();
                }
            }

            if (NativeUI::Int("Blue", NativeUI::Settings::scroller.b, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) 
                {
                    NativeUI::Settings::scroller.b = NumberKeyboard();
                }
            }
            if (NativeUI::Int("Opacity", NativeUI::Settings::scroller.a, 0, 255))
            {
                if (keypushed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) 
                {
                    NativeUI::Settings::scroller.a = NumberKeyboard();
                }
            }
        }
        break;
        case tpother:
        {
            NativeUI::Title("TP Options");
            if (NativeUI::Option("Teleport all to Him")) 
            {
                int Me = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer);
                Vector3 MyPosition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Me, 0.0, 0.0, 0.0);
                Misc::teleportallcoords(MyPosition);
            }

            if (NativeUI::Option("Teleport to Me")) 
            {

                int Me = PLAYER::PLAYER_PED_ID();
                Vector3 MyPosition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Me, 0.0, 0.0, 0.0);
                int selectedPed = Online::selectedPlayer;
                Misc::teleporttocoords(selectedPed, MyPosition);
            }
            if (NativeUI::Option("Teleport Into Car")) 
            {
                Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), false);
                for (int i = -1; i < 16; i++)
                {
                    if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i))
                    {
                        PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, i);
                    }
                }
            };
            NativeUI::MenuOption("Locations", teleportso);
            NativeUI::Option("Teleport To Player", [] {Online::TeleportToPlayer(Online::selectedPlayer); });
        }
        break;
        }
        NativeUI::End();
    }
}