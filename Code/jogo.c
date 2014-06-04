#include "jogo.h"

void spawnMonster(int currentStage, multiList* lista);
void beginAttack(int *attackNumber, int X0, int Y0, multiList* lista);

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

    int ***background = alocaHsvMatriz(largura, altura);
    getBackground(cam, background);
    
    /**********/
    
    // Allegro Items
    ALLEGRO_COLOR cor = al_map_rgb_f(1, 0, 0);
    
    ALLEGRO_COLOR cor2 = al_map_rgb_f(0, 0, 1);

    ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);

    ALLEGRO_BITMAP *HPBarBox = NULL;
    HPBarBox = al_load_bitmap("Graphics/hpBar.png");

    ALLEGRO_BITMAP *gameScreen = al_create_sub_bitmap(buffer, 0, 0, largura, altura);

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
    int currentStage = 1;
    int mobLimit = 4;
    int mobCount = 0;
    int mobKills = 0;
    int mobTarget = 20;
    int respawnTime = -200;
    int playerHP = 100;
    int shouldLoad = 1;

    int sx, sy;

    multiList *omniList = malloc(sizeof(multiList));
    omniList -> primeiroMonstro = NULL;
    

    fila *filaPlayerAtk = aloca();

    /***********************************************************************/
    //       Bob.3.0                  LOOPING                              //
    /***********************************************************************/
    
    while(1) {
        if(shouldLoad){
            s = initStageWithNumber(currentStage);

            al_attach_audio_stream_to_mixer(s -> stageAudio, al_get_default_mixer());
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


            /***********************************************************************/
            //       Bob.4.0            Monster Cycles                             //
            /***********************************************************************/

            if(respawnTime >= 300 - (s -> stageNum * 18) && mobCount <= s -> limitSpawn){
                mobCount++;
                spawnMonster(s -> stageNum, omniList);
                respawnTime = 0;
            }
            
            if(omniList -> primeiroMonstro != NULL){
                noMonster *temp = malloc(sizeof(noMonster));
                temp = omniList -> primeiroMonstro;
                
                do{

                    if(temp -> monster -> ready != 1){
                        printf("Started monster move sequence\n");
                        startMove(temp -> monster);
    
                    }
                        
                    if(temp -> monster -> cooldown > temp -> monster -> currentCooldown && temp -> monster -> ready == 1){
                        printf("Generating new attack\n");
                        beginAttack(temp -> monster -> ataque, temp -> monster -> X, temp -> monster -> Y, omniList);
                        temp -> monster -> currentCooldown = -0;
                    }
            
                    al_draw_bitmap(temp->monster->image, temp->monster->X, temp->monster->Y, 0);

                    if(temp -> prox != NULL)
                        temp = temp -> prox;

                }while(temp -> prox != NULL);
            }
            
            
            
            
            

            //Processamento de câmera.
            cameraLoop(matriz, cam, filaPlayerAtk, background, gameScreen, &sx, &sy);
            
            printf("%d, %d\n", sx, sy);
            al_draw_bitmap(shield, sx - al_get_bitmap_width(shield), sy - al_get_bitmap_height(shield), 0);
            

            if(!HPBarBox)
                printf("DAMN\n");
            
            float tempHP = (float) playerHP / 100;
            al_draw_filled_rectangle(41, altura - 79, (tempHP * (largura - 41)), altura - 51, cor);
            
            al_draw_scaled_bitmap(HPBarBox,
                                  0, 0,
                                  al_get_bitmap_width(HPBarBox),
                                  al_get_bitmap_height(HPBarBox),
                                  40, altura - 80,
                                  largura - 80, 30,
                                  0);

            al_flip_display();
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
    printf("a\n");
    al_shutdown_image_addon();
    printf("b\n");
    //al_uninstall_audio();
    printf("c\n");
    //al_uninstall_system();

    printf("aqui?\n");

    camera_finaliza(cam);

    printf("???\n");

    return EXIT_SUCCESS;
}

/***********************************************************************/
//   Bob.9.0      Other Functions -- reserved for required here only   //
/***********************************************************************/

// Bob.9.1 - spawnMonster

void spawnMonster(int currentStage, multiList* lista){
    Monster* minion = initWithMonsterNumber(currentStage);
    
    printf("A monster has spawned!\n");
    noMonster* m = malloc(sizeof(noMonster));
    m -> monster = minion;
    m -> prox = NULL;

    //Procura lugar na lista
    if(lista -> primeiroMonstro == NULL){
        printf("Should be here!\n");

        lista -> primeiroMonstro = m;
        return;
    }

    noMonster* temp;
    temp = lista -> primeiroMonstro;
    printf("HU3!\n");

    while(temp -> prox != NULL) {
        printf("lolz!\n");
        temp = temp -> prox;
    }
    printf("HU3!\n");

    temp -> prox = m;
    printf("With no bugs at all on the way\n");
}

void beginAttack(int *attackNumber, int X0, int Y0, multiList* lista){
    int chosenAttack;
    int randomizer = (rand() % 60) % 4;
    if(randomizer != 0)
        chosenAttack = attackNumber[0];
    else
        chosenAttack = attackNumber[1];
    
    printf("novoAtaque began\n");
    
    Ataque* novoAtaque = initWithAttackNumber(chosenAttack, X0, Y0);
    printf("noAtaque began\n");

    
    noAtaque* a = malloc(sizeof(noAtaque));
    a -> attack = novoAtaque;
    a -> prox = NULL;
    printf("Procurando lugar na lista began\n");
    
    //procura lugar na lista
    if(lista -> primeiroAtaque == NULL){
        lista -> primeiroAtaque = a;
        return;
    }
    noAtaque* temp;
    temp = lista -> primeiroAtaque;
    printf("While began\n");
    
    while (temp -> prox != NULL) {
        temp = temp -> prox;
    }
    
    temp -> prox = a;
    
}





