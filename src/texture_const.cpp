//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: texture_const.cpp
//
// 내용: 텍스쳐파일, 버텍스 상수, 이미지파일 정의 모두!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "texture_const.h"
#include "d3dx_class.h"
#include "image.h"
#include "texture_list.h"


Image_File imgfile_unit("image/unit.png");
Image_File imgfile_map("image/map.PNG");
Image_File imgfile_map2("image/map2.PNG");
Image_File imgfile_fog("image/fog.tga");
Image_File imgfile_sniper("image/sniper.png");
Image_File imgfile_gun("image/gun.PNG");
Image_File imgfile_weapon_interface("image/weapon_interface.PNG");
Image_File imgfile_system("image/system.PNG");
Image_File imgfile_tile("image/tile.PNG");
Image_File imgfile_font("image/font.PNG");
Image_File imgfile_minimap("image/minimap.PNG");
Image_File imgfile_minimap2("image/minimap2.PNG");


Texture tex_player(&imgfile_unit,0,0,32,32);
Texture tex_box(&imgfile_unit,0,32,32,64);
Texture tex_target(&imgfile_unit,32,32,64,64);
Texture tex_focus(&imgfile_unit,64,32,96,64);
Texture tex_melee(&imgfile_unit,96,32,128,64);
Texture tex_melee2(&imgfile_unit,192,160,224,192);
Texture tex_melee3(&imgfile_unit,224,160,256,192);
Texture tex_potal(&imgfile_unit,128,32,160,64);
Texture tex_gun(&imgfile_gun,0,0,1,1);
Texture tex_minimap(&imgfile_minimap,0,0,61,61);
Texture tex_minimap2(&imgfile_minimap2,0,0,120,120);

Texture tex_net(&imgfile_unit,160,32,192,64);
Texture tex_net_cap(&imgfile_unit,192,32,224,64);
Texture tex_grenade(&imgfile_unit,224,32,256,64);
Texture tex_missile(&imgfile_unit,256,32,288,64);
Texture tex_fire(&imgfile_unit,64,160,96,192);
Texture tex_barricade(&imgfile_unit,96,160,128,192);
Texture tex_throw_knife(&imgfile_unit,128,160,160,192);
Texture tex_fire_bottle(&imgfile_unit,160,160,192,192);

Texture tex_virus_missile(&imgfile_unit,0,160,32,192);
Texture tex_virus(&imgfile_unit,32,160,64,192);
Texture tex_smoke(&imgfile_unit,0,192,64,256);
Texture tex_rock(&imgfile_unit,256,160,288,192);
Texture tex_small_rock(&imgfile_unit,288,160,320,192);
Texture tex_trap(&imgfile_unit,320,160,352,192);
Texture tex_trap_effect(&imgfile_unit,352,160,384,192);
Texture tex_poison(&imgfile_unit,384,160,416,192);

Texture tex_emotion_sleep(&imgfile_unit,288,32,320,64);
Texture tex_emotion_normal(&imgfile_unit,320,32,352,64);
Texture tex_emotion_search(&imgfile_unit,352,32,384,64);
Texture tex_emotion_attack(&imgfile_unit,384,32,416,64);
Texture tex_emotion_doubt(&imgfile_unit,416,32,448,64);

Texture tex_backstab(&imgfile_unit,448,32,480,64);


Texture tex_mon_red_man(&imgfile_unit,32,0,64,32);
Texture tex_mon_zombie_weak(&imgfile_unit,64,0,96,32);
Texture tex_mon_zombie_big(&imgfile_unit,96,0,128,32);
Texture tex_mon_bug_weak(&imgfile_unit,128,0,160,32);
Texture tex_mon_pyro(&imgfile_unit,160,0,192,32);
Texture tex_mon_hunter(&imgfile_unit,192,0,224,32);
Texture tex_mon_bug_bomb(&imgfile_unit,224,0,256,32);
Texture tex_mon_bug_fly(&imgfile_unit,256,0,288,32);
Texture tex_mon_zombie_virus(&imgfile_unit,288,0,320,32);
Texture tex_mon_rocket_man(&imgfile_unit,320,0,352,32);
Texture tex_mon_blue_man(&imgfile_unit,352,0,384,32);
Texture tex_mon_zombie_boomer(&imgfile_unit,384,0,416,32);
Texture tex_mon_zombie_ghost(&imgfile_unit,416,0,448,32);
Texture tex_mon_sf_man(&imgfile_unit,448,0,480,32);
Texture tex_mon_berserker(&imgfile_unit,480,32,512,64);
Texture tex_mon_water_man(&imgfile_unit,0,128,32,160);
Texture tex_mon_spy(&imgfile_unit,32,128,64,160);
Texture tex_mon_pyro2(&imgfile_unit,64,128,96,160);
Texture tex_mon_bug_fly2(&imgfile_unit,96,128,128,160);
Texture tex_mon_bug_fire_moth(&imgfile_unit,128,128,160,160);
Texture tex_mon_bug_ant_lion(&imgfile_unit,160,128,192,160);
Texture tex_mon_bug_beetle(&imgfile_unit,192,128,224,160);
Texture tex_mon_zombie_small(&imgfile_unit,224,128,256,160);
Texture tex_mon_zombie_noise(&imgfile_unit,256,128,288,160);
Texture tex_mon_rock_giant(&imgfile_unit,288,128,320,160);
Texture tex_mon_robot(&imgfile_unit,320,128,352,160);
Texture tex_mon_spider(&imgfile_unit,352,128,384,160);
Texture tex_mon_spider2(&imgfile_unit,384,128,416,160);
Texture tex_mon_alert_robot(&imgfile_unit,416,128,448,160);
Texture tex_mon_alert(&imgfile_unit,448,128,480,160);
Texture tex_mon_bug_fling(&imgfile_unit,384,96,416,128);
Texture tex_mon_bug_fly_boss(&imgfile_unit,416,96,448,128);
Texture tex_mon_bug_drill_head(&imgfile_unit,416,160,448,192);
Texture tex_mon_bug_drill_body(&imgfile_unit,448,160,480,192);
Texture tex_mon_bug_drill_tail(&imgfile_unit,480,160,512,192);







Texture tex_map(&imgfile_map,0,0,1024,1024);
Texture tex_map2(&imgfile_map2,0,0,2048,2048);
Texture tex_tile(&imgfile_tile,0,0,1024,1024);
Texture tex_fog(&imgfile_fog,0-150,0-150,512+150,512+150);
Texture tex_sniper(&imgfile_sniper,0,0,599,399);
Texture tex_font[11] = {
	Texture(&imgfile_font,0,0,14,21),
	Texture(&imgfile_font,14,0,28,21),
	Texture(&imgfile_font,28,0,42,21),
	Texture(&imgfile_font,42,0,56,21),
	Texture(&imgfile_font,56,0,70,21),
	Texture(&imgfile_font,70,0,84,21),
	Texture(&imgfile_font,84,0,98,21),
	Texture(&imgfile_font,98,0,112,21),
	Texture(&imgfile_font,112,0,126,21),
	Texture(&imgfile_font,126,0,140,21),
	Texture(&imgfile_font,140,0,154,21)
};

Texture tex_inter_pistol(&imgfile_weapon_interface,128,0,256,64);
Texture tex_inter_rifle(&imgfile_weapon_interface,0,0,128,64);
Texture tex_inter_shotgun(&imgfile_weapon_interface,256,0,384,64);
Texture tex_inter_bazooka(&imgfile_weapon_interface,0,64,128,128);
Texture tex_inter_flame_thrower(&imgfile_weapon_interface,128,64,256,128);
Texture tex_inter_unknown(&imgfile_weapon_interface,256,64,384,128);

Texture tex_inter_sheild(&imgfile_weapon_interface,384,64,512,128);
Texture tex_inter_2_pistol(&imgfile_weapon_interface,0,128,128,192);
Texture tex_inter_sniper(&imgfile_weapon_interface,128,128,256,192);
Texture tex_inter_bow(&imgfile_weapon_interface,256,128,384,192);
Texture tex_inter_trap(&imgfile_weapon_interface,384,128,512,192);
Texture tex_inter_mini_gun(&imgfile_weapon_interface,0,192,128,256);
Texture tex_inter_cross_bow(&imgfile_weapon_interface,128,192,256,256);
Texture tex_inter_axe(&imgfile_weapon_interface,256,192,384,256);
Texture tex_inter_cloak(&imgfile_weapon_interface,384,192,512,256);
Texture tex_inter_knife(&imgfile_weapon_interface,0,256,128,320);
Texture tex_inter_club(&imgfile_weapon_interface,128,256,256,320);
Texture tex_inter_hammer(&imgfile_weapon_interface,256,256,384,320);
Texture tex_inter_box(&imgfile_weapon_interface,384,256,512,320);
Texture tex_inter_spear(&imgfile_weapon_interface,0,320,128,384);
Texture tex_inter_cloth(&imgfile_weapon_interface,128,320,256,384);
Texture tex_inter_bomb(&imgfile_weapon_interface,256,320,384,384);
Texture tex_inter_net(&imgfile_weapon_interface,0,384,128,448);
Texture tex_inter_drug(&imgfile_weapon_interface,128,384,256,448);
Texture tex_inter_block(&imgfile_weapon_interface,256,384,384,448);
Texture tex_inter_shoes(&imgfile_weapon_interface,128,448,256,512);
Texture tex_inter_silencer(&imgfile_weapon_interface,256,448,384,512);


Texture tex_item_unknown(&imgfile_unit,160,64,192,96);
Texture tex_item_pistol(&imgfile_unit,0,64,32,96);
Texture tex_item_rifle(&imgfile_unit,32,64,64,96);
Texture tex_item_shotgun(&imgfile_unit,64,64,96,96);
Texture tex_item_bazooka(&imgfile_unit,96,64,128,96);
Texture tex_item_flame_thrower(&imgfile_unit,128,64,160,96);
Texture tex_item_heal(&imgfile_unit,128,96,160,128);
Texture tex_item_bullet(&imgfile_unit,170,107,182,116);
Texture tex_item_portal1(&imgfile_unit,192,96,224,128);
Texture tex_item_portal2(&imgfile_unit,224,96,256,128);
Texture tex_item_portal3(&imgfile_unit,256,96,288,128);
Texture tex_item_button(&imgfile_unit,288,96,320,128);
Texture tex_item_button2(&imgfile_unit,320,96,352,128);
Texture tex_alert_target(&imgfile_unit,352,96,384,128);


Texture tex_item_color_red(&imgfile_unit,0,96,32,128);
Texture tex_item_color_yellow(&imgfile_unit,32,96,64,128);
Texture tex_item_color_blue(&imgfile_unit,64,96,96,128);
Texture tex_item_color_green(&imgfile_unit,96,96,128,128);


Texture tex_system_heart(&imgfile_system,0,0,23,20);
Texture tex_system_exp(&imgfile_system,29,6,57,17);
Texture tex_system_gauge_border(&imgfile_system,1,29,100,44);
Texture tex_system_gauge(&imgfile_system,3,46,98,57);


Image_File::Image_File(const char* name_):
name(name_), texture(NULL), width(0), height(0)
{

}
Image_File::~Image_File()
{
	if(texture)
		texture->Release();  
}

void Image_File::loading(IDirect3DDevice9* device_)
{
	D3DXIMAGE_INFO ImageInfo;
	D3DXGetImageInfoFromFile(name.c_str(), &ImageInfo);
	if(FAILED(D3DXCreateTextureFromFileEx(device_, name.c_str(), ImageInfo.Width, ImageInfo.Height, 1, D3DUSAGE_AUTOGENMIPMAP, ImageInfo.Format, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &texture)))
	{
	}
	width = (float)ImageInfo.Width;
	height = (float)ImageInfo.Height;
}

IDirect3DTexture9* Image_File::GetPointer()
{
	return texture;
}

void Direct_Manager::TextureLoading()
{
	imgfile_unit.loading(device);
	imgfile_map.loading(device);
	imgfile_map2.loading(device);
	imgfile_fog.loading(device);
	imgfile_sniper.loading(device);
	imgfile_gun.loading(device);
	imgfile_weapon_interface.loading(device);
	imgfile_system.loading(device);
	imgfile_tile.loading(device);
	imgfile_font.loading(device);
	imgfile_minimap.loading(device);
	imgfile_minimap2.loading(device);
	
	tex_player.loading();
	tex_box.loading();
	tex_target.loading();
	tex_focus.loading();
	tex_melee.loading();
	tex_melee2.loading();
	tex_melee3.loading();
	tex_potal.loading();
	tex_gun.loading();
	tex_minimap.loading();
	tex_minimap2.loading();

	tex_net.loading();
	tex_net_cap.loading();
	tex_grenade.loading();
	tex_missile.loading();
	tex_fire.loading();
	tex_barricade.loading();
	tex_throw_knife.loading();
	tex_fire_bottle.loading();

	tex_virus_missile.loading();
	tex_virus.loading();
	tex_smoke.loading();
	tex_rock.loading();
	tex_small_rock.loading();
	tex_trap.loading();
	tex_trap_effect.loading();
	tex_poison.loading();

	tex_emotion_sleep.loading();
	tex_emotion_normal.loading();
	tex_emotion_search.loading();
	tex_emotion_attack.loading();
	tex_emotion_doubt.loading();

	tex_backstab.loading();


	tex_mon_red_man.loading();
	tex_mon_zombie_weak.loading();
	tex_mon_zombie_big.loading();
	tex_mon_bug_weak.loading();
	tex_mon_pyro.loading();
	tex_mon_hunter.loading();
	tex_mon_bug_bomb.loading();
	tex_mon_bug_fly.loading();
	tex_mon_zombie_virus.loading();
	tex_mon_rocket_man.loading();
	tex_mon_blue_man.loading();
	tex_mon_zombie_boomer.loading();
	tex_mon_zombie_ghost.loading();
	tex_mon_sf_man.loading();
	tex_mon_berserker.loading();
	tex_mon_water_man.loading();
	tex_mon_spy.loading();
	tex_mon_pyro2.loading();
	tex_mon_bug_fly2.loading();
	tex_mon_bug_fire_moth.loading();
	tex_mon_bug_ant_lion.loading();
	tex_mon_bug_beetle.loading();
	tex_mon_zombie_small.loading();
	tex_mon_zombie_noise.loading();
	tex_mon_rock_giant.loading();
	tex_mon_robot.loading();
	tex_mon_spider.loading();
	tex_mon_spider2.loading();
	tex_mon_alert_robot.loading();
	tex_mon_alert.loading();
	tex_mon_bug_fling.loading();
	tex_mon_bug_fly_boss.loading();
	tex_mon_bug_drill_head.loading();
	tex_mon_bug_drill_body.loading();
	tex_mon_bug_drill_tail.loading();

	tex_map.loading();
	tex_map2.loading();
	tex_tile.loading();
	tex_sniper.loading();
	tex_fog.loading();
	for(int i=0;i<11;i++)
		tex_font[i].loading();
	
	tex_inter_pistol.loading();
	tex_inter_rifle.loading();
	tex_inter_shotgun.loading();
	tex_inter_bazooka.loading();
	tex_inter_flame_thrower.loading();
	tex_inter_unknown.loading();
	tex_inter_sheild.loading();
	tex_inter_2_pistol.loading();
	tex_inter_sniper.loading();
	tex_inter_bow.loading();
	tex_inter_trap.loading();
	tex_inter_mini_gun.loading();
	tex_inter_cross_bow.loading();
	tex_inter_axe.loading();
	tex_inter_cloak.loading();
	tex_inter_knife.loading();
	tex_inter_club.loading();
	tex_inter_hammer.loading();
	tex_inter_box.loading();
	tex_inter_spear.loading();
	tex_inter_cloth.loading();
	tex_inter_bomb.loading();
	tex_inter_net.loading();
	tex_inter_drug.loading();
	tex_inter_block.loading();
	tex_inter_shoes.loading();
	tex_inter_silencer.loading();



	
	tex_item_unknown.loading();
	tex_item_pistol.loading();
	tex_item_rifle.loading();
	tex_item_shotgun.loading();
	tex_item_bazooka.loading();
	tex_item_flame_thrower.loading();
	tex_item_heal.loading();
	tex_item_bullet.loading();
	tex_item_portal1.loading();
	tex_item_portal2.loading();
	tex_item_portal3.loading();
	tex_item_button.loading();
	tex_item_button2.loading();
	tex_alert_target.loading();

	tex_item_color_red.loading();
	tex_item_color_yellow.loading();
	tex_item_color_blue.loading();
	tex_item_color_green.loading();

	tex_system_heart.loading();
	tex_system_exp.loading();
	tex_system_gauge_border.loading();
	tex_system_gauge.loading();
}
