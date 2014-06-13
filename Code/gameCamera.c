#import "gameCamera.h"

void getBackground(camera *cam, int ***background){
  int x, y;
  int i = 0;

  int tempH, tempS, tempV;

  ALLEGRO_BITMAP *titleScreen = al_load_bitmap("Graphics/TitleScreen.png");
  if(!titleScreen)
    erro("erro ao alocar titleScreen.\n");

  al_draw_bitmap(titleScreen, 0, 0, 0);
  al_flip_display();

    for(;i < 10; i++){
      al_rest(0.5);

      for(y = 0; y < cam->altura; y++)
        for(x = 0; x < cam->largura; x++){
            rgbToHsv(cam->quadro[y][x][0], cam->quadro[y][x][1], cam->quadro[y][x][2], 
            &tempH, &tempS, &tempV);
  
            if(tempH > 180){
                tempH -= 360;
                tempH = -tempH;
            }
  
            background[y][x][0] += tempH;
  
            background[y][x][1] += tempS;
          
            background[y][x][2] += tempV;
        }
    }

    for(y = 0; y < cam->altura; y++)
    	for(x = 0; x < cam->largura; x++){
    		background[y][x][0] /= 10;
    		background[y][x][1] /= 10;
    		background[y][x][2] /= 10;
    	}
}

void cameraLoop(unsigned char ***matriz, camera *cam, fila *f, int ***background, ALLEGRO_BITMAP *gameScreen, int *sx, int *sy){
    camera_atualiza(cam);
    
    int x, y;
    
    int bx = 0;
    int by = 0;
    int bn = 0;
    
    int cyr = 0;
    int cxr = 0;
    int cnr = 0;

    int h, s, v;
    int dh, ds, dv;
    int tempH;

    int lastX = -1;
    int lastY = -1;

    if(f->fim != NULL){
      lastX = f->fim->x;
      lastY = f->fim->y;
    }

    ALLEGRO_BITMAP *silhueta = al_create_bitmap(cam -> largura, cam -> altura);

    for(y = 0; y < cam->altura; y++){
        for(x = 0; x < cam->largura; x++){
            //Espada
            rgbToHsv(cam->quadro[y][x][0], cam->quadro[y][x][1], cam->quadro[y][x][2], &h, &s, &v);

            if((h < 30 || h > 330) && s > 75 && v > 75){
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
            if(h < 160 && h > 120 && s > 50 && v > 85){
              by += y;
              bx += x;
              bn++;
            }
        }
    }

    /**********/
    camera_copia(cam, matriz, silhueta);

    al_convert_mask_to_alpha(silhueta, al_map_rgb(0, 0, 0));

    al_draw_tinted_bitmap(silhueta, al_map_rgba(75, 75, 175, 25), 0, 0, 0);
    /**********/

    if(bn > 25){
        *sx = bx / bn;
        *sy = by / bn;
    }

    else{
        *sx = -1;
        *sy = -1;
    }

    if(cnr > 5){
        x = cxr / cnr;
        y = cyr / cnr;

        al_draw_circle(x, y, 100, al_map_rgb(255, 0, 0), 1);

        insere(f, x, y);
    }

    else if(lastX >= 0 && lastY >= 0)
        insere(f, lastX, lastY);

    if(f->count > 5)
        retira(f);

    drawAtk(f);

    al_destroy_bitmap(silhueta);
}

void drawAtk(fila *f){
  if(f->comeco && f->comeco->prox){
      elemento *e1, *e2;

      e1 = f->comeco;
      e2 = f->comeco->prox;

      int alphaMult = 255/(f->count-1);
      int alpha = 0;

      while(e1 != NULL && e2 != NULL){
          al_draw_line(e1->x, e1->y, e2->x, e2->y, al_map_rgb(255, 0, 0), 3);

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