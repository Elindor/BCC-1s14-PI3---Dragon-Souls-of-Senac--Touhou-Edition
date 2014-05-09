#include <stdio.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "camera.h"

#include "fila.h"

#define FPS 60

void erro(char *mensagem) {
  fputs(mensagem, stderr);

  exit(EXIT_FAILURE);
}

void drawAtk(fila *f);

void rgbToHsv(int r, int g, int b, float *h, float *s, float *v);

int main() {
  //inicialização
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

  ALLEGRO_DISPLAY *display = al_create_display(largura, altura);
  if(!display)
    erro("erro na criacao da janela\n");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  if(!queue)
    erro("erro na criacao da fila\n");

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_display_event_source(display));

  al_start_timer(timer);

  /**********/

  unsigned char ***matriz = camera_aloca_matriz(cam);
  unsigned char ***matrizFiltro = camera_aloca_matriz(cam);

  fila *f = aloca();

  //cor para desenhar o círculo
  ALLEGRO_COLOR cor = al_map_rgb_f(0, 0, 1);

  ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);

  //tela exibindo img normal
  ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, largura, altura);

  //tela mostrando como o computador enxerga
  //ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, largura/2, 0, largura/2, altura/2);
  ALLEGRO_BITMAP *silhueta = al_create_bitmap(largura, altura);

  /**********/
  srand(time(NULL));
  int desenhar = 0;
  int terminar = 0;

  int cycle = 0;
  int hitx = rand() % (largura);
  int hity = rand() % (altura);

  int x, y;

  for(y = 0; y < altura; y++)
    for(x = 0; x < largura; x++){
      matrizFiltro[y][x][0] = cam->quadro[y][x][0];
      matrizFiltro[y][x][1] = cam->quadro[y][x][1];
      matrizFiltro[y][x][2] = cam->quadro[y][x][2];
    }

  //gameloop
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

    //interpretar img e realizar transformações
    if(desenhar && al_is_event_queue_empty(queue)) {
      desenhar = 0;
      camera_atualiza(cam);

      /**********/

      float cyr = 0;  //Soma dos valores y dos pontos considerados pelo computador
      float cxr = 0;  //Soma dos valores x dos pontos considerados pelo computador
      int cnr = 0;    //Qtde de pontos considerados

      int bx, by, bn;

      for(y = 0; y < altura; y++){
        for(x = 0; x < largura; x++){
          //Espada
          int r = cam->quadro[y][x][0];
          int g = cam->quadro[y][x][1];
          int b = cam->quadro[y][x][2];

          float h, s, v;

          rgbToHsv(r, g, b, &h, &s, &v);

          if(h < 15 || h > 345)
            if(s > 75 && v > 75){
              cyr += y;
              cxr += x;
              cnr++;
            }

          //Silhueta (REFINAR!!!)
          int r2 = matrizFiltro[y][x][0];
          int g2 = matrizFiltro[y][x][1];
          int b2 = matrizFiltro[y][x][2];
          int token = 1;

          float h2, s2, v2;
          rgbToHsv(r2, g2, b2, &h2, &s2, &v2);

          float dh, ds, dv;

          dh = h - h2;
          if(dh < 0)
            dh = -dh;

          ds = s - s2;
          if(ds < 0)
            ds = -ds;

          dv = v - v2;
          if(dv < 0)
            dv = -dv;

          if(dv > 25){
            token = 0;
          }

          if(!token) {
            matriz[y][x][0] = 255;
            matriz[y][x][1] = 255;
            matriz[y][x][2] = 255;
          }

          else {
            matriz[y][x][0] = 0;
            matriz[y][x][1] = 0;
            matriz[y][x][2] = 0;
          }
        }
      }

     /*for(y = 1; y < altura-1; y++)
        for(x = 1; x < largura-1; x++){
          int r = cam->quadro[y][x][0];
          int g = cam->quadro[y][x][1];
          int b = cam->quadro[y][x][2];

          int token = 4;

          if(255 != matriz[y+1][x][0])
            token--;
          if(255 != matriz[y-1][x][0])
            token--;
          if(255 != matriz[y][x+1][0])
            token--;
          if(255 != matriz[y][x-1][0])
            token--;

          if(token == 0){
            matriz[y][x][0] = 0;
            matriz[y][x][1] = 0;
            matriz[y][x][2] = 0;
          }

          float h, s, v;

          rgbToHsv(r, g, b, &h, &s, &v);

          if(h < 135 && h > 105){
            if(s > 35){
              by += y;
              bx += x;
              bn++;

              matriz[y][x][0] = 255;
              matriz[y][x][1] = 255;
              matriz[y][x][2] = 255;
            }
          }
        }*/

      cycle++;
      if(cycle > 50){
        double value = (pow(hitx - (bx / 2 /bn), 2) + pow(hity - (by / 2 / bn), 2));
        int dist = sqrt(value) - 7;

        if(dist < 100 && dist > -100 && bn > 0)
          printf("block!\n");

        else{
          if(matriz[hity][hitx][0] == 255)
            printf("hit\n");

          else
            printf("miss\n");
        }

        cycle = 0;
        hitx = rand() % (largura/2);
        hity = rand() % (altura/2);
      }

      /**********/
      camera_copia(cam, cam->quadro, esquerda);

      //Copia img editada na img direita
      camera_copia(cam, matriz, silhueta);
      al_convert_mask_to_alpha(silhueta, al_map_rgb(0, 0, 0));
      al_draw_bitmap(silhueta, 0, 0, 0);
      /**********/

      if(bn > 0)
        al_draw_circle(bx / bn, by / bn, 100, al_map_rgb(0, 0, 255), 1);

      if(cycle >= 40){
        if(cycle < 48){
          al_draw_circle(hitx, hity, 15, al_map_rgb(0, 0, 255), 30);
          al_draw_circle(hitx + largura, hity, 6, al_map_rgb(0, 0, 255), 3);
        }

        else
          al_draw_circle(hitx, hity, 15, al_map_rgb(255, 0, 0), 30);
      }

      if(cnr > 10){
        al_draw_circle(cxr / cnr, cyr / cnr, 100, al_map_rgb(255, 0, 0), 1);

        insere(f, cxr/cnr, cyr/cnr);

        if(f->count > 10)
          retira(f);
      }

      drawAtk(f);

      al_flip_display();
    }
  }

  /**********/

  libera(f);

  al_destroy_bitmap(silhueta);

  al_destroy_bitmap(esquerda);

  camera_libera_matriz(cam, matriz);
  camera_libera_matriz(cam, matrizFiltro);

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

void drawAtk(fila *f){
  if(f->comeco && f->comeco->prox){
    elemento *e1, *e2;

    e1 = f->comeco;
    e2 = f->comeco->prox;

    int alphaMult = 255/(f->count-1);
    int alpha = 0;

    while(e1 != NULL && e2 != NULL){
      al_draw_line(e1->x, e1->y, e2->x, e2->y, al_map_rgba(255, 0, 0, alpha), 3);
      e1 = e2;
      e2 = e2->prox;

      alpha += alphaMult;
    }
  }
}

void rgbToHsv(int r, int g, int b, float *h, float *s, float *v){
  float tempR = (float)r/255;
  float tempG = (float)g/255;
  float tempB = (float)b/255;
  
  float cMax, cMin;
  
  if(tempR >= tempB && tempR >= tempG){
    if(tempG > tempB)
      cMin = tempB;
  
    else
      cMin = tempG;

    cMax = tempR;
  }
  
  else if(tempB >= tempG){
    if(tempG > tempR)
      cMin = tempR;
  
    else
      cMin = tempG;
  
    cMax = tempB;
  }
  
  else{
    if(tempR > tempB)
      cMin = tempB;
  
    else
      cMin = tempR;
  
    cMax = tempG;
  }
  
  float delta = cMax - cMin;
  
  if(cMax == tempR){
    if(tempG >= tempB)
      *h = 60 * ((tempG - tempB) / delta);
  
    else
      *h = 60 * ((tempG - tempB) / delta + 6);
  }
  
  else if(cMax == tempG)
    *h = 60 * ((tempB - tempR) / delta + 2);
  
  else
    *h = 60 * ((tempR - tempG) / delta + 4);
  
  *s = delta/cMax * 100;
  
  *v = cMax *100;
}