#include <stdio.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "camera.h"

#include "fila.h"
#include "hsvMatriz.h"

#define FPS 60

void erro(char *mensagem) {
  fputs(mensagem, stderr);

  exit(EXIT_FAILURE);
}

void drawAtk(fila *f);

void rgbToHsv(int r, int g, int b, int *h, int *s, int *v);

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
  int ***background = alocaHsvMatriz(cam->largura, cam->altura);

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

  float cyr, cxr, cnr, lastCx, lastCy;

  int r, g, b, r2, g2, b2;

  int h, s, v, h2, s2, v2;
  int fh, fs, fv;

  int dh, ds, dv;
  int tempH;

  int token;

  double value;
  int dist;

  al_rest(1);

  for(y = 0; y < altura; y++)
    for(x = 0; x < largura; x++){
      rgbToHsv(cam->quadro[y][x][0], cam->quadro[y][x][1], cam->quadro[y][x][2], 
        &background[y][x][0], &background[y][x][1], &background[y][x][2]);

      if(background[y][x][0] > 180){
        background[y][x][0] -= 360;
        background[y][x][0] = -background[y][x][0];
      }
        
    }

  al_rest(1);

  for(y = 0; y < altura; y++)
    for(x = 0; x < largura; x++){
      rgbToHsv(cam->quadro[y][x][0], cam->quadro[y][x][1], cam->quadro[y][x][2], 
        &fh, &fs, &fv);

      if(fh > 180){
        fh -= 360;
        fh = -fh;
      }

      background[y][x][0] += fh;
      background[y][x][0] /=2;

      background[y][x][1] += fs;
      background[y][x][1] /=2;
      
      background[y][x][2] += fv;
      background[y][x][2] /=2;  
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
    printf("%d\n", al_is_event_queue_empty(queue));
    if(desenhar && al_is_event_queue_empty(queue)) {
      desenhar = 0;
      camera_atualiza(cam);

      /**********/

      int bx, by, bn;

      cyr = 0;
      cxr = 0;
      cnr = 0;

      for(y = 0; y < altura; y++){
        for(x = 0; x < largura; x++){
          //Espada
          r = cam->quadro[y][x][0];
          g = cam->quadro[y][x][1];
          b = cam->quadro[y][x][2];

          rgbToHsv(r, g, b, &h, &s, &v);

          if(h < 15 || h > 345)
            if(s > 75 && v > 75){
              cyr += y;
              cxr += x;
              cnr++;
            }

          //Silhueta (REFINAR!!!)
          if(h > 180)
            tempH = -(h - 360);

          else
            tempH = h;

          dh = tempH - background[y][x][0];
          if(dh < 0)
            dh = -dh;

          ds = s - background[y][x][1];
          if(ds < 0)
            ds = -ds;

          dv = v - background[y][x][2];
          if(dv < 0)
            dv = -dv;

          //dh > 15 && ds > 10 para tirar a interfencia de iluminacao, mas gera mtuiro ruido
          //ds > 25 é o mais preciso, mas sofre de interferencia de iluminacao
          if(dv > 25){
            //valores para teste!
            matriz[y][x][0] = 37;
            matriz[y][x][1] = 50;
            matriz[y][x][2] = 248;
          }

          else{
            matriz[y][x][0] = 0;
            matriz[y][x][1] = 0;
            matriz[y][x][2] = 0;
          }

          //Escudo
          if(h < 135 && h > 105 && s > 50 && v > 75){
            by += y;
            bx += x;
            bn++;

            matriz[y][x][0] = 0;
            matriz[y][x][1] = 255;
            matriz[y][x][2] = 0;
          }
        }
      }

     /*for(y = 1; y < altura-1; y++)
        for(x = 1; x < largura-1; x++){
          token = 4;

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
          }*/

      cycle++;
      if(cycle > 50 && bn > 0){
        value = (pow(hitx - (bx / 2 /bn), 2) + pow(hity - (by / 2 / bn), 2));
        dist = sqrt(value) - 7;

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
      //cor para teste!
      al_convert_mask_to_alpha(silhueta, al_map_rgb(37, 50, 248));
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
        lastCx = cxr / cnr;
        lastCy = cyr / cnr;

        al_draw_circle(lastCx, lastCy, 100, al_map_rgb(255, 0, 0), 1);

        insere(f, lastCx, lastCy);
      }

      else
        insere(f, lastCx, lastCy);

      if(f->count > 10)
          retira(f);

      drawAtk(f);

      al_flip_display();
    }
  }

  /**********/

  libera(f);

  al_destroy_bitmap(silhueta);

  al_destroy_bitmap(esquerda);

  camera_libera_matriz(cam, matriz);
  liberaHsvMatriz(background, cam->largura, cam->altura);

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

void rgbToHsv(int r, int g, int b, int *h, int *s, int *v){
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

  if(delta != 0){ 
    if(cMax == tempR){
      if(tempG >= tempB)
        *h = 60 * ((tempG - tempB) / delta);
    
      else
        *h = 60 * ((tempG - tempB) / delta) + 360;
    }
    
    else if(cMax == tempG)
      *h = 60 * ((tempB - tempR) / delta) + 120;
    
    else
      *h = 60 * ((tempR - tempG) / delta) + 240;
  }

  else
    *h = 0;
  
  *s = delta/cMax * 100;
  
  *v = cMax * 100;
}