#include <stdio.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "camera.h"



#define FPS 60

/*///////////////////////////////////////////////////////////////////////////
//                Bob.0.0      Glossário - Atalhos
//************************************************************************//*
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
//
//
//
//
//
//
//
//
//
//
//      Looping break / Finalização . . . . . . . . . . . . . . . . 9.0
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

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    if(!timer)
        erro("erro na criacao do relogio\n");

    ALLEGRO_DISPLAY *display = al_create_display(largura, altura/2);
    if(!display)
        erro("erro na criacao da janela\n");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if(!queue)
        erro("erro na criacao da fila\n");

    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));

    al_start_timer(timer);

    
    /***********************************************************************/
    //      Bob.2.0       Instanciação de variáveis fixas                  //
    /***********************************************************************/

    // Matrizes-camera
    unsigned char ***matriz = camera_aloca_matriz(cam);
    
    /**********/
    
    // Allegro Items
    ALLEGRO_COLOR cor = al_map_rgb_f(1, 0, 0);
    
    ALLEGRO_COLOR cor2 = al_map_rgb_f(0, 0, 1);

    ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);

    ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, largura/2, altura/2);

    ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, largura/2, 0, largura/2, altura/2);

    /**********/
    
    // Common Items
    srand(time(NULL));
    int desenhar = 0;
    int terminar = 0;
    int makeOnce = 1;
    int makeOnce2 = 1;
    int cycle = 0;
    int hitx = rand() % (largura/2);
    int hity = rand() % (altura/2);

    /***********************************************************************/
    //       Bob.3.0                  LOOPING                              //
    /***********************************************************************/

    
    while(1) {
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

        if(desenhar && al_is_event_queue_empty(queue)) { //Execução da fila:
            desenhar = 0;
            camera_atualiza(cam);

            /**********/

        

    
        

            /**********/

            al_flip_display();
        }
    }
    
    
    /***********************************************************************/
    //   Bob.9.0      LOOPING BREAK -- Starting shutdown                   //
    /***********************************************************************/

    al_destroy_bitmap(direita);

    al_destroy_bitmap(esquerda);

    camera_libera_matriz(cam, matriz);

    /**********/

    al_stop_timer(timer);

    al_unregister_event_source(queue, al_get_display_event_source(display));
    al_unregister_event_source(queue, al_get_timer_event_source(timer));

    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_timer(timer);

    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_uninstall_system();

    camera_finaliza(cam);

    return EXIT_SUCCESS;
}
