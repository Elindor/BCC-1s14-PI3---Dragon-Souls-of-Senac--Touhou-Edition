#include "stage.h"

stage *initStageWithNumber(int n){
	stage *temp = malloc(sizeof(stage));
	temp -> stageBackground = NULL;
	temp -> stageAudio = NULL;
	temp -> bossAudio = NULL;

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

			break;
	}

	return temp;
}

void removeStage(stage *s){
	al_destroy_bitmap(s -> stageBackground);
	al_destroy_audio_stream(s -> stageAudio);
	al_destroy_audio_stream(s -> bossAudio);

	free(s);
}