BCC-PI3
Repositório para criação do PI III, do Centro Universitário Senac.

OBJETIVO

Criação de um jogo em allegro com OpenCV, que utilize apenas webcam como interface.


|*********************************************************************|

O programa está adaptado para MacBook Pros. Para reverter este efeito, é necessário multiplicar por 2 (Na realidade, remover as divisões por 2) nas dimensões da camera no arquivo jogo.c



|*********************************************************************|

Como citado pelo Prof. Marcelo Hashimoto: 
Em algumas versões de sistemas operacionais baseados em
Debian (por exemplo Ubuntu ou elementaryOS), é necessário
modificar o arquivo camera.h. Substitua a primeira linha

     #include <opencv/highgui.h>

pela linha

     #include <opencv2/highgui/highgui_c.h>

