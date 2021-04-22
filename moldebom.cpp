#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>

using namespace std;
#define ARRIBA     72  
#define IZQUIERDA  75
#define DERECHA    77
#define ABAJO      80
#define ESC        27
#define ENTER      13
#define COMECAR	   99
#define PARAR      112
//definição dos códigos de cada tecla de acordo com a tabela ASCII

int backcolor=0;
int dir = 0;
int x=39,y=22;
int anteriorpx,anteriorpy;
int cont=0, cont2=0, cont3=0, cont4=0, A;
int R;
char tecla;

long int puntos = -5;
int vidas = 3;

void setCColor( int color)
{
        static HANDLE hConsole;

        hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

        SetConsoleTextAttribute( hConsole, color | (backcolor * 0x10 + 0x100) );
		//definição da cor de fundo
	}

int color[9] = {
      0x009,
      0x00E,
      0x00C,
      0x002,
      0x00B,
      0x005,
      0x00F,
	  0x00D
     };

void gotoxy(int x, int y) 
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
    //mudança das coordenadas na matriz para saber onde será impresso o novo pacman e fantasmas e deletado os antigos
}

char mapa[50][150] = {
	 "                                                      "
     "                                                      ",
     "                  AXXXXXXXXXXXXXXXXXXXB AXXXXXXXXXXXXXXXXXXXB",
     "                  YL__________________Y Y___________________Y",
     "                  Y_AXXXXXB_AXXXXXXXB_Y Y_AXXXSXXXB_AXXXXXB_Y",
     "                  Y_Y     Y_Y       Y_Y Y_Y       Y_Y     Y_Y",
     "                  Y_DXXXXXC_DXXXXXXXC_DXC_DXXXXXXXC_DXXXXXC_Y",
     "                  Y________|_________|___|_________|________Y",
     "                  Y_AXXXXXB_AXB_AXXXXXXXXXXXXXB_AXB_AXXXXXB_Y",
     "                  Y_DXXXXXC_Y Y_DXXXXB   AXXXXC_Y Y_DXXXXXC_Y",
     "                  Y_________Y Y______Y   Y______Y Y_________Y",
     "                  DXXXXXXXB_Y DXXXXB_Y   Y_AXXXXC Y_AXXXXXXXC",
     "                          Y_Y AXXXXC_DXXXC_DXXXXB Y_Y        ",
     "                          Y_Y Y_________________Y Y_Y        ",
     "                  XXXXXXXXC_DXC_AXXXXXX XXXXXXB_DXC_DXXXXXXXX",
     "                  _________|____Y      *      Y____|_________",
     "                  XXXXXXXXB_AXB_DXXXXXXXXXXXXXC_AXB_AXXXXXXXX",
     "                          Y_Y Y_________________Y Y_Y        ",
     "                          Y_Y Y_AXXXXXXXXXXXXXB_Y Y_Y        ",
     "                  AXXXXXXXC_DXC_DXXXXB   AXXXXC_DXC_DXXXXXXXB",
     "                  Y________|_________Y   Y_________|________Y",
     "                  Y_AXXXXXB_AXXXXXXB_Y   Y_AXXXXXXB_AXXXXXB_Y",
     "                  Y_DXXXB Y_DXXXXXXC_DXXXC_DXXXXXXC_Y AXXXC_Y",
     "                  Y_____Y Y_________|_____|_________Y Y_____Y",
     "                  DXXXB_Y Y_AXB_AXXXXXXXXXXXXXB_AXB_Y Y_AXXXC",
     "                  AXXXC_DXC_Y Y_DXXXXB   AXXXXC_Y Y_DXC_DXXXB",
     "                  Y_________Y Y______Y   Y______Y Y__R______Y",
     "                  Y_AXXXXXXXC DXXXXB_Y   Y_AXXXXC DXXXXXXXB_Y",
     "                  Y_DXXXXXXXXEXXXXXC_DXXXC_DXXXXXXXXXXXXXXC_Y",
     "                  Y_________________|_____|_________________Y",
     "                  DXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXC",
     "                                                      "
};
//mapa criado de acordo com o mapa de tiles onde é subtituido cada letra por um símbolo


void pintar_mapa()
{
     for(int i = 0 ; i < 78 ; i++){
         for(int j = 0 ; j < 30 ; j++){
               gotoxy(i,j);

               if(mapa[j][i] == 'X') {setCColor(color[0]);printf("%c",205);}
			    if(mapa[j][i] == '_') {setCColor(color[1]); printf("%c",250);}
				 else if(mapa[j][i] == 'Y') {setCColor(color[0]);printf("%c",186);}
				  else if(mapa[j][i] == 'A') {setCColor(color[0]);printf("%c",201);}
				   else if(mapa[j][i] == 'B') {setCColor(color[0]);printf("%c",187);}
				    else if(mapa[j][i] == 'C') {setCColor(color[0]);printf("%c",188);}
					 else if(mapa[j][i] == 'D') {setCColor(color[0]);printf("%c",200);}
					  else if(mapa[j][i] == 'E') {setCColor(color[7]);printf("%c",178);}
					   else if(mapa[j][i] == 'S') {setCColor(color[7]);printf("%c",219);}
						else if(mapa[j][i] == 'L') {setCColor(color[2]);printf("%c",155);}
		   				 else if(mapa[j][i] == 'R') {setCColor(color[3]);printf("%c",169);}


         }
     }
     //troca das letras por símbolos e cores correspondentes a cada parte do mapa
}


void pacman(int x , int y){
     setCColor(color[1]);
     gotoxy(x,y); printf("%c",184);
     //informações contidas na classe pacman como cor símbolo e movimentação
}

void borrar_pacman(int x, int y){
     gotoxy(x,y); printf(" ");
     if(mapa[y][x] == '_'){ mapa[y][x] = ' '; puntos += 5;}
     	//função que deleta o antigo pacman e os pontos fazendo já a contagem deles
}
void teclear(){
    if(kbhit()){
      tecla = getch();
      switch(tecla){
      case ARRIBA:
         dir = 0;
         break;

      case ABAJO:
         dir = 1;
         break;

      case DERECHA:
         dir = 2;
         break;

      case IZQUIERDA:
         dir = 3;
         break;
     
      case COMECAR:
      	 PlaySound(TEXT("C:\\PacmanRemixC.wav"), NULL, SND_FILENAME | SND_ASYNC);
      	 break;
     
      case PARAR:
     	 PlaySound(TEXT("C:\\troca.wav"), NULL, SND_FILENAME | SND_ASYNC);
         break;
      }

   }
   //função para detectar cada tecla pressionada e realizar a ação predefinida
}

class fantasma{
      int fdir;
      int _x, _y;
      int col;
      //informações da classe fantasma como cor, posição e movimentação
public:
      fantasma(int x , int y , int color);
      void dibujar_fantasma() const;
      void borrar_fantasma() const;
      void mover_fantasma();
      void choque_pacman();
	  //funções de colisão com pacman, de movimentação, de impressão e remoção do simbolo conforme movimentação na matriz
  };
fantasma::fantasma(int x , int y, int color){
      _x = x;
      _y = y;
      col = color;
      fdir = rand()%4;
      //criação do novo fantasma na nova posição
}
void fantasma::dibujar_fantasma() const{

     setCColor(color[col]);
     gotoxy(_x,_y); printf("%c",223);
}
void fantasma::borrar_fantasma() const{

     gotoxy(_x,_y); printf(" ");
}
void fantasma::choque_pacman(){
     if(y == _y && x == _x || (fdir == 0 && dir == 1 || fdir == 1 && dir == 0
     ||fdir == 2 && dir == 3 || fdir == 3 && dir == 2 )&&(_y == anteriorpy && _x == anteriorpx)){


      x = 39;
      y = 22;
      dir = 4;
      vidas--;
	  //função para detectar colisões e diminuir a quantidade de lifes do player
     }
     else if(x==53 and y==25 and cont4<5){
	  _x = 43;
      _y = 14;
      dir = 4;
      cont4++;
      //função de respawn dos fantasmas
	 }
	 else if(R==22){
		 _x = 43;
		 _y = 14;
	 }


}

void fantasma::mover_fantasma(){
     borrar_fantasma();
     choque_pacman();
     int bolx=_x,boly=_y;

     if(mapa[_y][_x] == '|'){
             fdir = rand()%4;
     }
     if(mapa[_y][_x] == '*'){
             fdir = 0;
     }

     if(fdir == 2){
          if(mapa[_y][_x+1] != 'X' && mapa[_y][_x+1] != 'A' && mapa[_y][_x+1] != 'Y' &&
          mapa[_y][_x+1] != 'B' && mapa[_y][_x+1] != 'C' && mapa[_y][_x+1] != 'D')         _x++;
          else fdir = rand()%4;
     }
     if(fdir == 3){
          if(mapa[_y][_x-1] != 'X' && mapa[_y][_x-1] != 'A' && mapa[_y][_x-1] != 'Y' &&
          mapa[_y][_x-1] != 'B' && mapa[_y][_x-1] != 'C' && mapa[_y][_x-1] != 'D')          _x--;
          else fdir = rand()%4;
     }
     if(fdir == 0){
          if(mapa[_y-1][_x] != 'X' && mapa[_y-1][_x] != 'A' && mapa[_y-1][_x] != 'Y' &&
          mapa[_y-1][_x] != 'B' && mapa[_y-1][_x] != 'C' && mapa[_y-1][_x] != 'D')           _y--;
          else fdir = rand()%4;
     }
     if(fdir == 1){
          if(mapa[_y+1][_x] != 'X' && mapa[_y+1][_x] != 'A' && mapa[_y+1][_x] != 'Y' &&
      mapa[_y+1][_x] != 'B' && mapa[_y+1][_x] != 'C' && mapa[_y+1][_x] != 'D')                _y++;
          else fdir = rand()%4;
     }

     if(mapa[boly][bolx] == '_') {setCColor(color[1]); gotoxy(bolx,boly);printf("%c",250);}
  	   else if(mapa[boly][bolx] == 'L' and cont2==0) {setCColor(color[2]); gotoxy(bolx, boly);printf("%c",155);}
  	   	else if(mapa[boly][bolx] == 'R' and cont4==0){setCColor(color[3]); gotoxy(bolx, boly);printf("%c",169);}

     // rutina atajo
     if(_x <= 17) _x = 61;
        else if(_x >= 62) _x = 18;
     dibujar_fantasma();
 
 //função para fazer com que  a movimentação seja conforme o mapa para haver colisão e os atalhos funcionarem
}


void marcador(){

   gotoxy(5,4); printf("PONTOS");
   gotoxy(5,6); printf("    ");
   setCColor(color[6]);
   gotoxy(5,6); printf("%ld",puntos);

   setCColor(color[1]);
   gotoxy(5,25); printf("VIDAS");
   for(int i = 0 ; i <= vidas ; i++){
       gotoxy(5,i+27);printf(" ");

   }
   for(int i = 0 ; i < vidas ; i++){
       gotoxy(5,i+27);printf("%c",208);

   }
   setCColor(color[6]);
   gotoxy(70,22);printf("MODIFIED BY: JONE");
   setCColor(color[1]);
   gotoxy(70,23);printf("C - comecar musica P - parar musica");
   setCColor(color[6]);
   gotoxy(70,24);printf("%c",223);printf(" - fantasma");
   setCColor(color[3]);
   gotoxy(70,25);printf("%c",169);;printf(" - respawn dos fantasmas");
   setCColor(color[7]);
   gotoxy(70,26);printf("%c",178);printf(" - entrada do portal");
   setCColor(color[2]);
   gotoxy(70,27);printf("%c",155);printf(" - vida extra");
   setCColor(color[7]);
   gotoxy(70,28);printf("%c",219);printf(" - saida do portal");
   setCColor(color[6]);
   gotoxy(70,29);printf("Cuidado com o fantasma invisivel");
   
   
   //marcadores de informações do player e manual do jogo
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
	//função para esconder cursor
}



int main(){
	keybd_event(VK_MENU,0x36,0,0);
	keybd_event(VK_RETURN,0x1C,0,0);
	keybd_event(VK_RETURN,0x1C,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
	//função de tela cheia

	

   fantasma A(41,14,2);
   fantasma B(43,14,3);
   fantasma C(40,14,4);
   fantasma D(39,14,5);
   fantasma E(42,14,8);
   //definição da posição inicial dos fantasmas
   pintar_mapa();
  //subtituição das letras por simbolos e respectivas cores 

   while(vidas > 0 && puntos < 1940){
   	  SetCursorPos(1500, 1000);
   	  //definição para seta do mouse ficar fora de visão no canto da tela
	  ShowConsoleCursor(false);
      marcador();
      borrar_pacman(x,y);
      anteriorpx = x; anteriorpy = y;
	  

      teclear();

      if(dir == 0 && mapa[y-1][x] != 'X' && mapa[y-1][x] != 'A' && mapa[y-1][x] != 'Y' &&
      mapa[y-1][x] != 'B' && mapa[y-1][x] != 'C' && mapa[y-1][x] != 'D')                       y--;


      else if(dir == 1 && mapa[y+1][x] != 'X' && mapa[y+1][x] != 'A' && mapa[y+1][x] != 'Y' &&
      mapa[y+1][x] != 'B' && mapa[y+1][x] != 'C' && mapa[y+1][x] != 'D')                       y++;
  	  //limitações de colisão no eixo y

      pacman(x,y);
      Sleep(55);
      borrar_pacman(x,y);
	  
      A.choque_pacman();
      B.choque_pacman();
      C.choque_pacman();
      D.choque_pacman();
      E.choque_pacman();

      anteriorpx = x; anteriorpy = y;
      teclear();


      if(dir == 2 && mapa[y][x+1] != 'X' && mapa[y][x+1] != 'A' && mapa[y][x+1] != 'Y' &&
      mapa[y][x+1] != 'B' && mapa[y][x+1] != 'C' && mapa[y][x+1] != 'D')                       x++;


      else if(dir == 3 && mapa[y][x-1] != 'X' && mapa[y][x-1] != 'A' && mapa[y][x-1] != 'Y' &&
      mapa[y][x-1] != 'B' && mapa[y][x-1] != 'C' && mapa[y][x-1] != 'D')                         x--;
  	   //limitações de colisão no eixo x	  
  
      A.mover_fantasma();
      B.mover_fantasma();
      C.mover_fantasma();
      D.mover_fantasma();
      E.mover_fantasma();
      pacman(x,y);
      if(R==22){
		  Sleep(0);
	  }else{
	  	  Sleep(55);
	  }		
			
     
      if(x < 18) {
        borrar_pacman(x,y);
        x = 61;
      }
      else if(x > 60){
        borrar_pacman(x,y);
        x= 18;
      }
      //atalho para pacman

	  if(x==29 and y==27 and cont==0){
	  	borrar_pacman(29,27);
		  x=46; y=3;
		  cont++;
	  }
	  //outro atalho(ou portal nesse caso)
	  
	  if(x==19 and y==2 and cont2==0){
		  vidas++;
		  cont2++;
	  }
	  //vida extra
	  
	  while(cont3==0){
		  
		gotoxy(70,17);cout<<"Bem Vindo Player"<<endl;
		gotoxy(70,18);cout<<"Deseja qual dificuldade?"<<endl;
		gotoxy(70,20);cout<<"1 - NORMAL, 2 - DIFICIL, ";setCColor(color[2]);cout<<"3 - INSANO"<<endl;
		setCColor(color[1]);gotoxy(70,21);cin>>R;
		
		
		cont3++;
		//menu de seleção de dificuldade
	}
	  
	  if(R==2){
		A.mover_fantasma();
		B.mover_fantasma();
		C.mover_fantasma();
		D.mover_fantasma();
		E.mover_fantasma();
	}
	else if(R==3){
		A.mover_fantasma();
		B.mover_fantasma();
		C.mover_fantasma();
		D.mover_fantasma();
		E.mover_fantasma();
		A.mover_fantasma();
		B.mover_fantasma();
		C.mover_fantasma();
		D.mover_fantasma();
		E.mover_fantasma();
	}
	//aumento da velocdade conforme opção selecionada
   }
   
   if(puntos==1940){
	   gotoxy(34,14);cout<<"VOCE GANHOU"<<endl;
   }
   else{
	   gotoxy(34,14);cout<<"VOCE PERDEU"<<endl;
   }
   //informação dos dados da vitória ou derrota
   
   for(int i = 0 ; i <= vidas ; i++){
       gotoxy(5,i+27);printf(" ");
       //eliminação do icone das vidas conforme forem perdidas
   }
   SetCursorPos(300, 300);
   //retorno da seta do mouse ao centro da tela
   system("pause>NULL");
   return 0;

}