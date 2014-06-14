#include "stage.h"

stage *initStageWithNumber(int n){
	stage *temp = malloc(sizeof(stage));
    temp -> stageNum = n;
	temp -> stageBackground = NULL;
	temp -> stageAudio = NULL;
	temp -> bossAudio = NULL;
    int randomModifier = rand()%100;

	switch(n){
		case 1:
			temp -> stageBackground = al_load_bitmap("Graphics/BeachSide.png");
			if(!temp -> stageBackground)
				erro("Erro na alocação de stageBackground para stage 1\n");

			temp -> stageAudio = al_load_audio_stream("Sound/BeachSide.ogg", 4, 1024);
			if(!temp -> stageAudio)
				erro("Erro na alocação de stageAudio para stage 1\n");

			temp -> bossAudio = al_load_audio_stream("Sound/Marlingone.ogg", 4, 1024);
			if(!temp -> bossAudio)
				erro("Erro na alocação de bossAudio para stage 1\n");

			al_set_audio_stream_gain(temp -> bossAudio, 1.5);

            temp -> targetKills = 20;
            
            temp -> limitSpawn = 4;
            
			break;

		case 2:
			temp -> stageBackground = al_load_bitmap("Graphics/RuinedVillage.png");
			if(!temp -> stageBackground)
				erro("Erro na alocação de stageBackground para stage 2\n");

			temp -> stageAudio = al_load_audio_stream("Sound/RuinedVillage.ogg", 4, 1024);
			if(!temp -> stageAudio)
				erro("Erro na alocação de stageAudio para stage 2\n");

			temp -> bossAudio = al_load_audio_stream("Sound/Hueda.ogg", 4, 1024);
			if(!temp -> bossAudio)
				erro("Erro na alocação de bossAudio para stage 2\n");

            temp -> targetKills = 40;
            
            temp -> limitSpawn = 5;
            
            randomModifier += 30;
            
			break;

		case 3:
			temp -> stageBackground = al_load_bitmap("Graphics/Macalania.png");
			if(!temp -> stageBackground)
				erro("Erro na alocação de stageBackground para stage 3\n");

			temp -> stageAudio = al_load_audio_stream("Sound/IceLake.ogg", 4, 1024);
			if(!temp -> stageAudio)
				erro("Erro na alocação de stageAudio para stage 3\n");

			temp -> bossAudio = al_load_audio_stream("Sound/Cirno.ogg", 4, 1024);
			if(!temp -> bossAudio)
				erro("Erro na alocação de bossAudio para stage 3\n");

            temp -> targetKills = 70;
            
            temp -> limitSpawn = 6;
            
            randomModifier += 40;
            
			break;

		case 4:
			temp -> stageBackground = al_load_bitmap("Graphics/Drangleic.png");
			if(!temp -> stageBackground)
				erro("Erro na alocação de stageBackground para stage 4\n");

			temp -> stageAudio = al_load_audio_stream("Sound/DrangleicCastle.ogg", 4, 1024);
			if(!temp -> stageAudio)
				erro("Erro na alocação de stageAudio para stage 4\n");

			temp -> bossAudio = al_load_audio_stream("Sound/GuardianDragon.ogg", 4, 1024);
			if(!temp -> bossAudio)
				erro("Erro na alocação de bossAudio para stage 4\n");

            temp -> targetKills = 100;
            
            temp -> limitSpawn = 6;
            
            randomModifier += 80;
            
			break;

		case 5:
			temp -> stageBackground = al_load_bitmap("Graphics/Moria.png");
			if(!temp -> stageBackground)
				erro("Erro na alocação de stageBackground para stage 5\n");

			temp -> stageAudio = al_load_audio_stream("Sound/DwarvenRuins.ogg", 4, 1024);
			if(!temp -> stageAudio)
				erro("Erro na alocação de stageAudio para stage 5\n");

			temp -> bossAudio = al_load_audio_stream("Sound/Balrog.ogg", 4, 1024);
			if(!temp -> bossAudio)
				erro("Erro na alocação de bossAudio para stage 5\n");
            
            temp -> targetKills = 100;
            
            temp -> limitSpawn = 6;
            
            randomModifier += 70;
            
			break;

		case 6:
			//MISSING OCEAN PALACE!!!
			temp -> stageBackground = al_load_bitmap("Graphics/BeachSide.png");
			if(!temp -> stageBackground)
				erro("Erro na alocação de stageBackground para stage 6\n");

			//MISSING OCEAN PALACE HEME!!!
			temp -> stageAudio = al_load_audio_stream("Sound/BeachSide.ogg", 4, 1024);
			if(!temp -> stageAudio)
				erro("Erro na alocação de stageAudio para stage 6\n");

			temp -> bossAudio = al_load_audio_stream("Sound/Lavos.ogg", 4, 1024);
			if(!temp -> bossAudio)
				erro("Erro na alocação de bossAudio para stage 6\n");

            temp -> targetKills = 150;
            
            temp -> limitSpawn = 7;
            
            randomModifier += 60;
            
			break;
	}
    
    
    if(randomModifier > 100){
        temp -> darkPhantom = 30 + n;
        temp -> darkSpawn = rand()% temp -> targetKills + 1;
    }
    else{
        temp -> darkPhantom = 0;
        temp -> darkSpawn = -1;
    }
    //temp -> darkPhantom = 30 + n;
    //temp -> darkSpawn = 1;

    al_set_audio_stream_playmode(temp -> stageAudio, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playmode(temp -> bossAudio, ALLEGRO_PLAYMODE_LOOP);

	return temp;
}

void removeStage(stage *s){
	al_set_audio_stream_playing(s -> stageAudio, false);
	al_set_audio_stream_playing(s -> bossAudio, false);

	al_drain_audio_stream(s -> stageAudio);
	al_drain_audio_stream(s -> bossAudio);

	al_detach_audio_stream(s -> stageAudio);
	al_detach_audio_stream(s -> bossAudio);

	al_destroy_bitmap(s -> stageBackground);
	al_destroy_audio_stream(s -> stageAudio);
	al_destroy_audio_stream(s -> bossAudio);

	free(s);
}