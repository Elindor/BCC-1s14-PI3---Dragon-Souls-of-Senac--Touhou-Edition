#include "jogo.h"

void spawnMonster(int currentStage, multiList* lista);
int beginAttack(int *attackNumber, int X0, int Y0, multiList* lista);
void dismissAttack(multiList *list, noAtaque *noAtk);
int currentStage;

/*///////////////////////////////////////////////////////////////////////////
//                Bob.0.0      Glossário - Atalhos
**************************************************************************
//
//      Após lidarmos com códigos desagradevelmente longos no ultimo PI,
//  estipula-se aqui um protocolo de procura com ctrl + f (Ou command + f)
//
//      Para procurar um item, procurar pelo código dele com o antecessor:
//
//                                  Bob.
//
//      Item                                                        Num
//
//      void erro() . . . . . . . . . . . . . . . . . . . . . . . . 0.1
//
//      Inicialização de camera e allegro . . . . . . . . . . . . . 1.0
//
//      Iniciação de variáveis fixas  . . . . . . . . . . . . . . . 2.0
//
//      Looping / gameflow basics . . . . . . . . . . . . . . . . . 3.0
//
//      Monster Cycles  . . . . . . . . . . . . . . . . . . . . . . 4.0
//
//
//
//
//
//
//
//
//
//      Looping break / Finalização . . . . . . . . . . . . . . . . 8.0
//
//
//
//      Other Functions . . . . . . . . . . . . . . . . . . . . . . 9.0
//
//
//////////////////////////////////////////////////////////////////////////*/

// Bob.0.1
void erro(char *mensagem) {
    fputs(mensagem, stderr);

    exit(EXIT_FAILURE);
}


int main() {
    
    /***********************************************************************/
    //       Bob.1.0   Inicialização da camera e allegro                   //
    /***********************************************************************/
    
    camera *cam = camera_inicializa(0);
    if(!cam)
        erro("erro na inicializacao da camera\n");

    int largura = cam->largura;
    int altura = cam->altura;

    if(!al_init())
        erro("erro na inicializacao do allegro\n");

    if(!al_init_image_addon())
        erro("erro na inicializacao do adicional de imagem\n");

    if(!al_init_primitives_addon())
        erro("erro na inicializacao do adicional de primitivas\n");

    if(!al_install_audio())
        erro("erro na inicialização do addon de audio.\n");

    if(!al_init_acodec_addon())
        erro("erro na inicializção do acodec.\n");

    if(!al_reserve_samples(1))
        erro("erro ao alocar canais de áudio.\n");

    al_init_font_addon();

    if(!al_init_ttf_addon())
        erro("erro ao inicializar ttf addon.\n");
    
    ALLEGRO_FONT *fonte = NULL;
    fonte = al_load_font("Fonts/OptimusPrinceps.ttf", 48, 0);
    if(!fonte)
        erro("erro na criacao da fonte\n");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    if(!timer)
        erro("erro na criacao do relogio\n");

    ALLEGRO_DISPLAY *display = al_create_display(largura, altura);
    if(!display)
        erro("erro na criacao da janela\n");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if(!queue)
        erro("erro na criacao da fila\n");

    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));

    al_start_timer(timer);
    
    
    // Bob.1.1    seed de rand
    srand(time(NULL));
    
    /***********************************************************************/
    //      Bob.2.0       Instanciação de variáveis fixas                  //
    /***********************************************************************/

    // Matrizes-camera
    unsigned char ***matriz = camera_aloca_matriz(cam);

    //Teste ttf
    //al_draw_text(fonte, al_map_rgb(255, 0, 0), largura/2, altura/2, 0, "YOU DIED");
    //al_flip_display();

    int ***background = alocaHsvMatriz(largura, altura);
    getBackground(cam, background);
    
    /**********/
    
    // Allegro Items
    ALLEGRO_COLOR cor = al_map_rgb_f(1, 0, 0);
    ALLEGRO_COLOR cinza = al_map_rgb_f(0.6, 0.6, 0.6);

    
    ALLEGRO_COLOR cor2 = al_map_rgb_f(0, 0, 1);

    ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);

    ALLEGRO_BITMAP *HPBarBox = NULL;
    HPBarBox = al_load_bitmap("Graphics/hpBar.png");

    ALLEGRO_BITMAP *gameScreen = al_create_sub_bitmap(buffer, 0, 0, largura, altura);
    
    ALLEGRO_BITMAP *loading1 = al_load_bitmap("Graphics/TitleScreen.png");

    ALLEGRO_BITMAP *victory = al_load_bitmap("Graphics/victory.png");
    
    ALLEGRO_BITMAP *loading2 = al_load_bitmap("Graphics/loadingRuinedVillage.png");
    ALLEGRO_BITMAP *Phantom2_1 = al_load_bitmap("Graphics/darkSpirit2-1.png");
    ALLEGRO_BITMAP *Phantom2_2 = al_load_bitmap("Graphics/darkSpirit2-2.png");
    ALLEGRO_BITMAP *Phantom2_3 = al_load_bitmap("Graphics/darkSpirit2-3.png");
    
    ALLEGRO_BITMAP *loading3 = al_load_bitmap("Graphics/loadingFrozenLake.png");
    ALLEGRO_BITMAP *Phantom3_1 = al_load_bitmap("Graphics/darkSpirit3-1.png");
    ALLEGRO_BITMAP *Phantom3_2 = al_load_bitmap("Graphics/darkSpirit3-2.png");
    ALLEGRO_BITMAP *Phantom3_3 = al_load_bitmap("Graphics/darkSpirit3-3.png");
    
    ALLEGRO_BITMAP *loading4 = al_load_bitmap("Graphics/loadingDrangleicCastle.png");
    ALLEGRO_BITMAP *Phantom4_1 = al_load_bitmap("Graphics/darkSpirit4-1.png");
    ALLEGRO_BITMAP *Phantom4_2 = al_load_bitmap("Graphics/darkSpirit4-2.png");
    ALLEGRO_BITMAP *Phantom4_3 = al_load_bitmap("Graphics/darkSpirit4-3.png");
    
    ALLEGRO_BITMAP *loading5 = al_load_bitmap("Graphics/loadingOldDwarven.png");
    ALLEGRO_BITMAP *Phantom5_1 = al_load_bitmap("Graphics/darkSpirit5-1.png");
    ALLEGRO_BITMAP *Phantom5_2 = al_load_bitmap("Graphics/darkSpirit5-2.png");
    ALLEGRO_BITMAP *Phantom5_3 = al_load_bitmap("Graphics/darkSpirit5-3.png");
    
    ALLEGRO_BITMAP *loading6 = al_load_bitmap("Graphics/loadingUnderseaPalace.png");
    ALLEGRO_BITMAP *Phantom6_1 = al_load_bitmap("Graphics/darkSpirit6-1.png");
    ALLEGRO_BITMAP *Phantom6_2 = al_load_bitmap("Graphics/darkSpirit6-2.png");
    ALLEGRO_BITMAP *Phantom6_3 = al_load_bitmap("Graphics/darkSpirit6-3.png");
    
    ALLEGRO_BITMAP *endingScreen = al_load_bitmap("Graphics/endingScreen.png");
    

    ALLEGRO_BITMAP *shield = al_load_bitmap("Graphics/LeatherShield.png");

    stage *s = NULL;

    /**********/
    
    // Common Items
    srand(time(NULL));
    int desenhar = 0;
    int terminar = 0;
    int cycle = 0;
    int hitx = rand() % (largura);
    int hity = rand() % (altura);
    int mobLimit = 4;
    int mobCount = 0;
    int mobKills = 0;
    int mobTarget = 20;
    int respawnTime = -200;
    int playerHP = 100;
    int barrier = 20;
    int shouldLoad = 1;
    int bossFight = 1;
    int stageChangeCountdown = 0;
    int stageWillChange = 0;
    float transparency;
    currentStage = 1;

    int sx, sy;

    multiList *omniList = malloc(sizeof(multiList));
    omniList -> primeiroMonstro = NULL;
    omniList -> primeiroAtaque = NULL;
    omniList -> boss = NULL;
    

    fila *filaPlayerAtk = aloca();

    /***********************************************************************/
    //       Bob.3.0                  LOOPING                              //
    /***********************************************************************/
    
    while(1) {
        if(shouldLoad){
            s = initStageWithNumber(currentStage);
            
            al_attach_audio_stream_to_mixer(s -> stageAudio, al_get_default_mixer());
            al_set_audio_stream_playing(s -> bossAudio, false);
            al_set_audio_stream_playing(s -> stageAudio, true);

            shouldLoad = 0;
        }
            

        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                desenhar = 1;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                terminar = 1;
                break;
            default:
                printf("evento desconhecido\n");
        }

        if(terminar)
            break;

        if(desenhar && al_is_event_queue_empty(queue)){
            desenhar = 0;
            
            //Draw backgound
            al_draw_scaled_bitmap(s -> stageBackground, 0, 0,
                                al_get_bitmap_width(s -> stageBackground),
                                al_get_bitmap_height(s -> stageBackground),
                                0, 0, largura, altura, 0);
            
            //Processamento de câmera.
            cameraLoop(matriz, cam, filaPlayerAtk, background, buffer, &sx, &sy);


            /***********************************************************************/
            //       Bob.4.0            Monster Cycles                             //
            /***********************************************************************/

            // Bob.4.1 Monster Spawning
            
            if(respawnTime >= 300 - (s -> stageNum * 18) && mobCount <= s -> limitSpawn){
                mobCount++;
                if(mobCount == s -> darkSpawn){
                    Monster* Phantom = initWithBossNumber(s -> darkPhantom);
                    omniList -> boss = Phantom;
                }
                else
                    spawnMonster(s -> stageNum, omniList);
                respawnTime = 0;
            }
            
            // Bob.4.2 Monster cycle itself - movement, attack spawning, checking if alive
            
            if(omniList -> primeiroMonstro != NULL){
                noMonster *temp = omniList -> primeiroMonstro;
                
                do{

                    if(temp -> monster -> ready != 1){
                        startMove(temp -> monster);
    
                    }
                    temp-> monster -> currentCooldown++;
                    if(temp -> monster -> cooldown * 10 < temp -> monster -> currentCooldown && temp -> monster -> ready == 1){
                        printf("Generating new attack\n");
                        temp -> monster -> currentCooldown = -beginAttack(temp -> monster -> ataque, temp -> monster -> centerX, temp -> monster -> centerY, omniList);
                       
                    }
            
                    al_draw_bitmap(temp->monster->image, temp->monster->X, temp->monster->Y, 0);

                    if(temp -> prox != NULL)
                        temp = temp -> prox;

                }while(temp -> prox != NULL);
            }

            
            // Bob.4.3 Boss cycles - Also phantoms
            
            if(omniList -> boss == NULL && omniList -> primeiroMonstro == NULL && mobCount == s -> limitSpawn){
                //Spawns boss
                if(respawnTime < 10300){        //Desliga musica, seta 300 ciclos de espera
                    respawnTime = 10000;
                    al_set_audio_stream_playing(s -> stageAudio, false);
                }
                else{                           //liga musica, BEGIN
                    Monster* CHEFE = initWithBossNumber(20 + currentStage);
                    omniList -> boss = CHEFE;
                    al_set_audio_stream_playing(s -> bossAudio, true);
                    bossFight = 1;
                }
            }
            
            if(omniList -> boss != NULL) {
                startMove(omniList -> boss);
                omniList -> boss -> currentCooldown++;
                if(omniList -> boss -> cooldown * 10 < omniList -> boss -> currentCooldown && omniList -> boss -> ready == 1){
                    printf("Generating new BOOOOOOOSS attack\n");
                    omniList -> boss -> currentCooldown = -beginAttack(omniList -> boss -> ataque, omniList -> boss -> centerX, omniList -> boss -> centerY, omniList);
                }
                al_draw_bitmap(omniList -> boss -> image, omniList -> boss -> X, omniList -> boss -> Y, 0);
            }
            
            if(bossFight == 1 && omniList -> boss == NULL){
                bossFight = 0;
                respawnTime = -300;
                stageWillChange = 1;
                currentStage++;
            }
            
            
            
            // Bob.4.4 Attack Cycles - move, check strike
            
            if(omniList -> primeiroAtaque != NULL){
                noAtaque *temp = omniList -> primeiroAtaque;
                
                do{
                    if(temp -> attack -> currentDuration < 8 && temp -> attack -> preAnimationTime == 0){
                        int radius = 40 - temp -> attack -> currentDuration * 4;
                        al_draw_filled_circle(temp -> attack -> targetX, temp -> attack -> targetY, radius, cor);
                    }
                    // Move ataque
                    if(temp -> attack -> duration > temp -> attack -> currentDuration){
                        checkAttack(temp -> attack);
                    }
                    
                    // HIT
                    else{
                        if(temp -> attack -> deathCountdown == 0){
                            
                            double value = ( pow(temp -> attack -> targetX - sx, 2) + pow(temp -> attack -> targetY - sy, 2) );
                            int dist = sqrt(value) - 7;
                            
                            if(dist < al_get_bitmap_width(shield) && dist > -al_get_bitmap_width(shield)){
                                printf("Blocked!!\n");

                            }
                            else if(barrier >= 1){    //Se houver barreira, tem todo esse paranauê
                                barrier -=temp -> attack -> damage;
                                if(barrier < 0){
                                    playerHP += barrier;
                                    barrier = 0;
                                }
                            }
                            else // Senão é bem simples
                                playerHP -= temp -> attack -> damage;

                            
                        }
                          temp -> attack -> deathCountdown++;
                    }
                    
                    // Attack dealloc
                    
                    noAtaque *tempForDelete = NULL;
                    if(temp -> attack -> deathCountdown >= 5){
                        tempForDelete = temp;
                    }
                    
                    // attack list scrolling
                    if(temp -> prox != NULL)
                        temp = temp -> prox;
                    
                    if(tempForDelete != NULL){
                        dismissAttack(omniList, tempForDelete);
                        printf("Attack successfully dismissed\n");
                    }
                    
                }while(temp -> prox != NULL);
            }
            
            
            
            
            
            

            
            
            
            
            
            
            /***********************************************************************/
            //       Bob.6.0            Interface Cycles, bitches                  //
            /***********************************************************************/
            
            
            if(sx > 0 && sy > 0)
                //al_draw_bitmap(shield, sx - al_get_bitmap_width(shield) / 2, sy - al_get_bitmap_height(shield) / 2, 0);
                al_draw_tinted_bitmap(shield, al_map_rgba_f(1, 1, 1, 0.6), sx - al_get_bitmap_width(shield) / 2, sy - al_get_bitmap_height(shield) / 2, 0);

            
            
            
            if(omniList -> boss == NULL){
                //al_draw_text(fonte, al_map_rgb(0, 0, 255), largura - 75, 20, ALLEGRO_ALIGN_RIGHT,
               //              "/ %d", s -> limitSpawn)
                //al_draw_text(fonte, al_map_rgb(0, 0, 255), largura - 60, 20, 0,
               //              "/ %d", s -> limitSpawn)
            }
            else{
                al_draw_filled_rectangle(41, 79, (1 * (largura - 82) + 41),  51, cor);
                
                al_draw_scaled_bitmap(HPBarBox,
                                      0, 0,
                                      al_get_bitmap_width(HPBarBox),
                                      al_get_bitmap_height(HPBarBox),
                                      40, 50,
                                      largura - 80, 30,
                                      0);
            }
            
            
            if(!HPBarBox)
                printf("DAMN\n");
            
            float tempHP = (float) playerHP / 100;
            float tempbarrier = (float) barrier / 100;
            
            //Barrier bar drawing
            
            /*
             
             //CASO COM OUTRA BARRA
            if(barrier >= 1){
                al_draw_filled_rectangle(41, altura - 129, (tempbarrier * (largura - 41)), altura - 101, cinza);
                
                al_draw_scaled_bitmap(HPBarBox,
                                      0, 0,
                                      al_get_bitmap_width(HPBarBox),
                                      al_get_bitmap_height(HPBarBox),
                                      40, altura - 130,
                                      largura - 80, 30,
                                      0);
            }
            */
            
            
            // Hp drawing
            if(playerHP >= 1)
                al_draw_filled_rectangle(41, altura - 79, (tempHP * (largura - 82) + 41), altura - 51, cor);
            //CASO SEM OUTRA BARRA
            if(barrier >= 1)
                al_draw_filled_rectangle(41, altura - 79, (tempbarrier * (largura - 82) + 41), altura - 51, cinza);
            
            al_draw_scaled_bitmap(HPBarBox,
                                  0, 0,
                                  al_get_bitmap_width(HPBarBox),
                                  al_get_bitmap_height(HPBarBox),
                                  40, altura - 80,
                                  largura - 80, 30,
                                  0);

            if(stageWillChange == 1){
                stageChangeCountdown ++;
                
                if(stageChangeCountdown < 75){ // victory warning
                    if(stageChangeCountdown < 25)
                        transparency = (float)stageChangeCountdown / 25;
                    else if(stageChangeCountdown < 50)
                        transparency = 1;
                    else if(stageChangeCountdown < 75)
                        transparency = (float)(75 - stageChangeCountdown) / 25;
                    else
                        transparency = 0;
                    
                    al_draw_tinted_scaled_bitmap(victory, al_map_rgba_f(1, 1, 1, transparency),
                                                 0, 0,
                                                 al_get_bitmap_width(victory),
                                                 al_get_bitmap_height(victory),
                                                 0, (altura/2) - (al_get_bitmap_height(victory) /2),
                                                 largura, al_get_bitmap_height(victory), 0);
                    
                }
                else if(stageChangeCountdown >= 100){
                    if(stageChangeCountdown < 150){     //Stage fog
                        transparency = (float)(stageChangeCountdown - 100) / 50;
                    }
                    else if(stageChangeCountdown <= 250){
                        transparency = 1;
                    }
                    else{
                        transparency = (float)(300 - stageChangeCountdown) / 50;
                    }
                    switch (currentStage) {
                        case 1:
                            al_draw_tinted_scaled_bitmap(loading1, al_map_rgba_f(1, 1, 1, transparency),
                                                         0, 0,
                                                         al_get_bitmap_width(loading1),
                                                         al_get_bitmap_height(loading1),
                                                         0, 0, largura, altura, 0);
                            break;
                        case 2:
                            al_draw_tinted_scaled_bitmap(loading2, al_map_rgba_f(1, 1, 1, transparency),
                                                         0, 0,
                                                         al_get_bitmap_width(loading2),
                                                         al_get_bitmap_height(loading2),
                                                         0, 0, largura, altura, 0);
                            break;
                        case 3:
                            printf("Properly here\n");
                            al_draw_tinted_scaled_bitmap(loading3, al_map_rgba_f(1, 1, 1, transparency),
                                                         0, 0,
                                                         al_get_bitmap_width(loading3),
                                                         al_get_bitmap_height(loading3),
                                                         0, 0, largura, altura, 0);
                            break;
                        case 4:
                            al_draw_tinted_scaled_bitmap(loading4, al_map_rgba_f(1, 1, 1, transparency),
                                                         0, 0,
                                                         al_get_bitmap_width(loading4),
                                                         al_get_bitmap_height(loading4),
                                                         0, 0, largura, altura, 0);
                            break;
                        case 5:
                            al_draw_tinted_scaled_bitmap(loading5, al_map_rgba_f(1, 1, 1, transparency),
                                                         0, 0,
                                                         al_get_bitmap_width(loading5),
                                                         al_get_bitmap_height(loading5),
                                                         0, 0, largura, altura, 0);
                            break;
                        case 6:
                            al_draw_tinted_scaled_bitmap(loading6, al_map_rgba_f(1, 1, 1, transparency),
                                                         0, 0,
                                                         al_get_bitmap_width(loading6),
                                                         al_get_bitmap_height(loading6),
                                                         0, 0, largura, altura, 0);
                            break;
                        case 7:
                            al_draw_tinted_scaled_bitmap(endingScreen, al_map_rgba_f(1, 1, 1, transparency),
                                                         0, 0,
                                                         al_get_bitmap_width(endingScreen),
                                                         al_get_bitmap_height(endingScreen),
                                                         0, 0, largura, altura, 0);
                            if(stageChangeCountdown >= 151)
                                stageChangeCountdown = 151;
                            break;
                            
                        default:
                            break;
                    }
                    
                }
                
                if(stageChangeCountdown == 250){
                    al_set_audio_stream_playing(s -> stageAudio, false);
                    al_set_audio_stream_playing(s -> bossAudio, false);
                    shouldLoad = 1;
                }
                if(stageChangeCountdown == 300){
                    stageWillChange = 0;
                    stageChangeCountdown = 0;
                }
                
                respawnTime = -300;
            }

            
            al_flip_display();


            //check minion hitbox
            if(omniList -> primeiroMonstro != NULL){
                noMonster *temp = omniList -> primeiroMonstro;

                do{
                    monsterGotHit(buffer, temp -> monster);

                    if(temp -> prox != NULL)
                        temp = temp -> prox;

                }while(temp -> prox != NULL);
            }
        }
        
        respawnTime++;
        
    }
    
    
    /***********************************************************************/
    //   Bob.8.0      LOOPING BREAK -- Starting shutdown                   //
    /***********************************************************************/

    //Somehow crashing...
    removeStage(s);

    al_destroy_bitmap(gameScreen);
    al_destroy_bitmap(HPBarBox);
    al_destroy_bitmap(shield);

    libera(filaPlayerAtk);

    camera_libera_matriz(cam, matriz);
    liberaHsvMatriz(background, largura, altura);

    /**********/

    al_stop_timer(timer);

    al_unregister_event_source(queue, al_get_display_event_source(display));
    al_unregister_event_source(queue, al_get_timer_event_source(timer));

    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_timer(timer);

    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    //al_uninstall_audio();
    //al_uninstall_system();


    camera_finaliza(cam);

    return EXIT_SUCCESS;
}






















/***********************************************************************/
//   Bob.9.0      Other Functions -- reserved for required here only   //
/***********************************************************************/

// Bob.9.1 - spawnMonster

void spawnMonster(int currentStage, multiList* lista){
    Monster* minion = initWithMonsterNumber(currentStage);
    
    noMonster* m = malloc(sizeof(noMonster));
    m -> monster = minion;
    m -> prox = NULL;

    //Procura lugar na lista
    if(lista -> primeiroMonstro == NULL){

        lista -> primeiroMonstro = m;
        return;
    }

    noMonster* temp;
    temp = lista -> primeiroMonstro;

    while(temp -> prox != NULL) {
        temp = temp -> prox;
    }

    temp -> prox = m;
    printf("A new Monster has successfully spawned\n");
}


// Bob.9.3 - spawn attack

int beginAttack(int *attackNumber, int X0, int Y0, multiList* lista){
    int chosenAttack;
    int randomizer = (rand() % 60) % 4;
    if(randomizer != 0)
        chosenAttack = attackNumber[0];
    else
        chosenAttack = attackNumber[1];
    
    int totalNumberOfAttacks = 1;
    int numberOfAttacksMade = 0;
    int timeInterval = 5;
    
    //geradores adicionais por tipo
    if(chosenAttack == 6 || chosenAttack == 7) // magicMissiles or Spores
        totalNumberOfAttacks = 3;
    if(chosenAttack == 11) //Curse
        totalNumberOfAttacks = 5;
    
    //geradores adicionais especificos
    if(currentStage == 1 && chosenAttack == 13)
        totalNumberOfAttacks = 3;
    if(currentStage == 3 && chosenAttack == 6){
        totalNumberOfAttacks = 7;
        timeInterval = 3;
    }
    if(currentStage == 4 && chosenAttack == 13){
        totalNumberOfAttacks = 2;
        timeInterval = 0;
    }
    
    int returnedInt;
    do{
        Ataque* novoAtaque = initWithAttackNumber(chosenAttack, X0, Y0);
        novoAtaque -> preAnimationTime = timeInterval * numberOfAttacksMade;
        
        noAtaque* a = malloc(sizeof(noAtaque));
        a -> attack = novoAtaque;
        a -> prox = NULL;
        
        //procura lugar na lista
        if(lista -> primeiroAtaque == NULL)
            lista -> primeiroAtaque = a;
        else{
            noAtaque* temp;
            temp = lista -> primeiroAtaque;
            
            while(temp -> prox != NULL) {
                temp = temp -> prox;
            }
            
            temp -> prox = a;
        }
        
        printf("A new attack has successfully spawned\n");
        returnedInt = a -> attack -> duration;
        numberOfAttacksMade++;
    }while(numberOfAttacksMade < totalNumberOfAttacks);
    
     returnedInt += (numberOfAttacksMade * 3);
    return returnedInt;
}

// Bob.9.4 - dismiss attack

void dismissAttack(multiList *list, noAtaque *noAtk){
    noAtaque *temp = list -> primeiroAtaque;
    
    if(!temp)
        return;
    
    if(temp == noAtk){
        list -> primeiroAtaque = temp -> prox;
        al_destroy_bitmap(noAtk -> attack -> image);
        free(noAtk -> attack);
        free(noAtk);
        return;
    }
    
    
    while(temp -> prox != noAtk)
        temp = temp -> prox;
    
    temp -> prox = temp -> prox -> prox;
    
    al_destroy_bitmap(noAtk -> attack -> image);
    free(noAtk -> attack);
    free(noAtk);

    
}

