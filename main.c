//albano alex 3ain
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
void gotoxy(short c, short r) {
	if (c>0 && r>0) {
		COORD CursorPosition = { c-1, r-1 };
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut, CursorPosition);
	}
}
//menu iniziale
void mainmenu(){
	gotoxy (40,2);
	printf("%c  %c  Welcome to Blackjack!  %c  %c",5,6,3,4);
	gotoxy(1,5);
	printf("%c How To Play: ",16);
	gotoxy(1,6);
	printf("1) The player will be given 2 cards.The player's cards will be facing upwards meanwhile the dealer will have 1 card out of 2 facing downwards.");
	gotoxy(1,7);
	printf("   A value will be displayed based on the sum of the player/dealer cards.");
	gotoxy(1,9);
	printf("2) Your goal is to beat the dealer by having a value higher than the dealer or equal to 21");
	gotoxy(1,11);
	printf("3) If the player has a value equal to 21 with only 2 cards given then its called Blackjack and the dealer will pay 3/2 of the current bet.");
	gotoxy(1,13);
	printf("4) If the player/dealer has a higher than 21 its called a bust and the player/dealer loses automatically.");
	gotoxy(1,15);
	printf("5) The dealer can't stop drawing cards until he reaches a value higher than or equal to 17");
	gotoxy(1,17);
	printf("%c About cards:",16);
	gotoxy(1,18);
	printf("The Aces have a value of 1 or 11 depending on what's best for the player/dealer.");
	gotoxy(1,20);
	printf("Jacks, Queens and Kings have a value of 10");
}
//aggiunta di soldi al saldo
float addbalance(float balance){
	system("cls");
	gotoxy(1,3);
	printf("Insert ammount to add to your current balance: ");
	float baladd;
	bool isbal=false;
	while(isbal==false){
		scanf("%f",&baladd);
		if((baladd+balance)>0 && (baladd+balance)<1000001){
			balance+=baladd;
			isbal=true;
		}
		else{
			printf("Invalid ammount!\n");
		}
	}
	return balance;
}
//selezione della puntata
float betsize(float balance){
	bool valid=false;
	char option;
	while(valid==false){
		gotoxy(1,3);
		printf("press 1 to play at $1/bet\npress 2 to play at $5/bet \npress 3 to play at $10/bet \npress 4 to play at $50/bet \npress 5 to play at $100/bet\npress 6 to play at $500/bet \npress 7 to play at $1k/bet \npress 8 to play at $5k/bet \npress 9 to play at $10k/bet \nBet size: ");
		option=getch();
		if (kbhit()){
			option=getch();
		}
		gotoxy(20,12);
		switch(option)
		{
			case '1':
				if(balance>=1.0){
					valid=true;
					return 1.0;
				}
				valid=false;
				printf("Invalid option: low balance!\n");
				break;
			case '2':
				if(balance>=5.0){
					valid=true;
					return 5.0;
				}
				valid=false;
				printf("Invalid option: low balance!\n");
				break;
			case '3':
				if(balance>=10.0){
					valid=true;
					return 10.0;
				}
				valid=false;
				printf("Invalid option: low balance!\n");
				break;
			case '4':
				if(balance>=50.0){
					valid=true;
					return 50.0;
				}
				valid=false;
				printf("Invalid option: low balance!\n");
				break;
			case '5':
				if(balance>=100.0){
					valid=true;
					return 100.0;
				}
				valid=false;
				printf("Invalid option: low balance!\n");
				break;
			case '6':
				if(balance>=500.0){
					valid=true;
					return 500.0;
				}
				valid=false;
				printf("Invalid option: low balance!\n");
				break;
			case '7':
				if(balance>=1000.0){
					valid=true;
					return 1000.0;
				}
				valid=false;
				printf("Invalid option: low balance!\n");
				break;
			case '8':
				if(balance>=5000.0){
					valid=true;
					return 5000.0;
				}
				valid=false;
				printf("Invalid option: low balance!\n");
				break;
			case '9':
				if(balance>=10000.0){
					valid=true;
					return 10000.0;
				}
				valid=false;
				printf("Invalid option: low balance!\n");
				break;
			default:
				valid=false;
				printf("not a valit option!         \n");
				break;
		}
	}
}
//creazione del mazzo
void cardalg(int cards[52],int idx[52]){
	int x=1;
	for(size_t i=0;i<49;i+=4){
		cards[i]=x;
		cards[i+1]=x;
		cards[i+2]=x;
		cards[i+3]=x;
		if(x<10){
			x++;
		}
	}
	x=1;
	for(size_t i=0;i<52;i++){
		idx[i]=x;
		x++;
	}
}
//mischia le carte
void shuffle(int deck[52],int cards[52],int idx[52]){
	for(size_t i=0;i<52;i++){
		deck[i]=cards[i];
	}
	for(int i=0;i<rand()%1000+2000;i++){
		size_t j=rand()%52;
		size_t k=rand()%52;
		int temp=deck[j];
		deck[j]=deck[k];
		deck[k]=temp;

		temp=idx[j];
		idx[j]=idx[k];
		idx[k]=temp;
	}
}
//distribuzione di una carta
void distribute(int deck[52],size_t deck_idx,int idx[52],int xidx[11],int x[11],size_t x_idx){
	x[x_idx]=deck[deck_idx];
	xidx[x_idx]=idx[deck_idx];
}
//stampa del gioco a video
void game_print(int dealer[11],size_t dealer_idx,int player[11],size_t player_idx,int dvalue1,int dvalue2,int pvalue1,int pvalue2,size_t var){
	gotoxy(1,15);
	if(dvalue1==dvalue2){
		if(var==1){
			printf("\nDealer value: %i+?\n",dvalue1);
		}
		if(var==0){
			printf("\nDealer value: %i   \n",dvalue1);
		}
	}
	else{
		if(var==1){
			printf("\nDealer value: %i+?/%i+?\n",dvalue1,dvalue2);
		}
		if(var==0){
			printf("\nDealer value: %i/%i     \n",dvalue1,dvalue2);
		}
	}
	gotoxy(1,30);
	if(pvalue1==pvalue2){
		printf("\nPlayer value: %i    \n",pvalue1);
	}
	else{
		printf("\nPlayer value: %i/%i\n",pvalue1,pvalue2);
	}
	gotoxy(1,32);
	printf("---------------------");
}
//stampa la carta
void printcard(int cardvalue,int cardidx,int type){
	int count=0;
	char let=cardvalue+48;
	char bordo[50][50];
	bordo[3][3]=cardvalue+48;
	for(size_t i=0;i<12;i++){
		if(type==0){
			gotoxy(10,18+count);
		}
		if(type==1){
			gotoxy(40,18+count);
		}
		if(type==2){
			gotoxy(70,18+count);
		}
		if(type==3){
			gotoxy(100,18+count);
		}
		if(type==4){
			gotoxy(130,18+count);
		}
		if(type==5){
			gotoxy(160,18+count);
		}
		if(type==6){
			gotoxy(190,18+count);
		}

		if(type==7){
			gotoxy(10,3+count);
		}
		if(type==8 || type==100){
			gotoxy(40,3+count);
		}
		if(type==9){
			gotoxy(70,3+count);
		}
		if(type==10){
			gotoxy(100,3+count);
		}
		if(type==11){
			gotoxy(130,3+count);
		}
		if(type==12){
			gotoxy(160,3+count);
		}
		if(type==13){
			gotoxy(190,3+count);
		}
		if(type==100){
			for(size_t j=0;j<15;j++){
				bordo[i][j]='*';
				printf("%c",bordo[i][j]);
			}
		}
		else{
			for(size_t j=0;j<15;j++){
				if(i==0 || i==11 || j==0 || j==14){
					bordo[i][j]='*';
				}
				else{
					bordo[i][j]=' ';
				}
				if((i==2 && j==2) || (i==9 && j==12)){
					if(cardidx%4==1){
						bordo[i][j]=3;
					}
					if(cardidx%4==2){
					bordo[i][j]=4;
					}
					if(cardidx%4==3){
						bordo[i][j]=5;
					}
					if(cardidx%4==0){
						bordo[i][j]=6;
					}
				}
				if(cardvalue==1){
					bordo[1][2]='A';
					bordo[10][12]='A';
				}
				else if(cardvalue==10){
					if(cardidx>40 && cardidx<45){
						bordo[1][2]='J';
						bordo[10][12]='J';
					}
					if(cardidx>44 && cardidx<49){
						bordo[1][2]='Q';
						bordo[10][12]='Q';
					}
					if(cardidx>48){
						bordo[1][2]='K';
						bordo[10][12]='K';
				}
					if(cardidx<41){
						bordo[1][2]='1';
						bordo[1][3]='0';
						bordo[10][11]='1';
						bordo[10][12]='0';
					}
				}
				else if((i==1 && j==2) || (i==10 && j==12)){
					bordo[i][j]=let;
				}
				printf("%c",bordo[i][j]);
			}
		}

		count++;
		printf("\n");
	}
}
//controllo di primo caso di vittoria
bool check_win_21(int value1,int value2){
	if(value1==21 || value2==21){
		return true;
	}
	return false;
}
//controllo di secondo caso di vittoria
int check_win(int pvalue1,int dvalue1,int dvalue2){
	if((dvalue2>=17 && dvalue2<=21) || (dvalue1>=17 && dvalue1<=21)){
		if(dvalue1==pvalue1 || dvalue2==pvalue1){
			return 3;
		}
		if(dvalue1>pvalue1 && dvalue2>pvalue1){
			return 1;
		}
		if(dvalue1<pvalue1 || dvalue2<pvalue1){
			return 2;
		}
	}
	return 0;
}
//selezione azione in gioco
int optionf(int repeat,float balance,float bet){
	bool valid=false;
	char option;
	while(valid==false){
		if(repeat==0 && balance>=2*bet){
			gotoxy(1,33);
			printf("\npress 'h' to hit, 'd' to double down or 's' to stay: ");
		}
		else{
			gotoxy(1,33);
			printf("\npress 'h' to hit  or 's' to stay:                    ");
		}

		option=getch();
		if (kbhit()){
			option=getch();
		}
		switch(option)
		{
			case 'h':
				gotoxy(65,34);
				printf("                   \n");
				valid=true;
				return 1;
				break;
			case 'd':
				gotoxy(65,34);
				printf("                   \n");
				valid=true;
				return 2;
				break;
			case 's':
				gotoxy(65,34);
				printf("                   \n");
				valid=true;
				return 3;
				break;
			default:
				gotoxy(65,34);
				printf("not a valid option!\n");
				break;
		}
	}
}
//gioco
int game(int cards[52],int idx[52],float balance,float bet){
	int deck[52];
	size_t deck_idx=0;
	size_t dealer_idx=0;
	size_t player_idx=0;
	shuffle(deck,cards,idx);
	int dealer[11]={0};
	int didx[11]={0};
	int player[11]={0};
	int pidx[11]={0};
	int ptype=0;
	int dtype=7;
	for(int i=0;i<2;i++){
		distribute(deck,deck_idx,idx,pidx,player,player_idx);
		player_idx++;
		deck_idx++;
	}
	for(int i=0;i<2;i++){
		distribute(deck,deck_idx,idx,didx,dealer,dealer_idx);
		dealer_idx++;
		deck_idx++;
	}
	printcard(dealer[dealer_idx-2],didx[dealer_idx-2],dtype);
	dtype++;
	printcard(dealer[dealer_idx-1],didx[dealer_idx-1],100);
	printcard(player[player_idx-2],pidx[player_idx-2],ptype);
	ptype++;
	printcard(player[player_idx-1],pidx[player_idx-1],ptype);
	ptype++;
	int pvalue1=0;
	int pvalue2=0;
	pvalue1=player[0]+player[1];
	pvalue2=pvalue1;
	if(player[0]==1 || player[1]==1){
		pvalue2+=10;
	}
	int dvalue1=0;
	int dvalue2=0;
	dvalue1=dealer[0];
	dvalue2=dvalue1;
	if(dealer[0]==1){
		dvalue2+=10;
	}
	size_t var=1;
	game_print(dealer,dealer_idx,player,player_idx,dvalue1,dvalue2,pvalue1,pvalue2,var);
	if(check_win_21(pvalue1,pvalue2)==true){
		gotoxy(1,32);
		printf("\nPlayer wins!\n");
		return 5;
	}
	int rep=0;
	int isval;
	bool isdub=false;
	while((pvalue1<=21 || pvalue2<=21) && (isval=optionf(rep,balance,bet))<3){
		if(rep==0){
			if(isval==2){
				isdub=true;
			}
		}
		rep++;
		distribute(deck,deck_idx,idx,pidx,player,player_idx);
		player_idx++;
		deck_idx++;
		pvalue1+=player[player_idx-1];
		pvalue2+=player[player_idx-1];
		printcard(player[player_idx-1],pidx[player_idx-1],ptype);
		ptype++;
		bool x=false;
		if(player[player_idx-1]==1){
			for(size_t i=0;i<player_idx-1;i++){
				if(player[i]==1){
					x=true;
				}
			}
			if(x==false){
				pvalue2+=10;
			}
		}
		game_print(dealer,dealer_idx,player,player_idx,dvalue1,dvalue2,pvalue1,pvalue2,var);
		if(check_win_21(pvalue1,pvalue2)==true){
			if(isdub==true){
				gotoxy(1,32);
				printf("\nPlayer wins!\n");
				return 3;
			}
			gotoxy(1,32);
			printf("\nPlayer wins!\n");
			return 1;
		}
	}
	if(pvalue1>21 && pvalue2>21){
		if(isdub==true){
			gotoxy(1,32);
			printf("\nPlayer Busts! Dealer wins!\n");
			return 4;
		}
		gotoxy(1,32);
		printf("\nPlayer Busts! Dealer wins!\n");
		return 0;
	}

	if(pvalue2<21){
		pvalue1=pvalue2;
	}
	dvalue1+=dealer[1];
	dvalue2+=dealer[1];
	printcard(dealer[dealer_idx-1],didx[dealer_idx-1],dtype);
	dtype++;
	bool x=false;
	if(dealer[dealer_idx-1]==1){
			for(size_t i=0;i<dealer_idx-1;i++){
				if(dealer[i]==1){
					x=true;
				}
			}
			if(x==false){
				dvalue2+=10;
			}
		}
	var=0;
	game_print(dealer,dealer_idx,player,player_idx,dvalue1,dvalue2,pvalue1,pvalue2,var);
	if(check_win_21(dvalue1,dvalue2)==true || check_win(pvalue1,dvalue1,dvalue2)==1){
		if(isdub==true){
			gotoxy(1,32);
			printf("\nDealer wins!\n");
			return 4;
		}
		gotoxy(1,32);
		printf("\nDealer wins!\n");
		return 0;
	}
	if(check_win(pvalue1,dvalue1,dvalue2)==2){
		if(isdub==true){
			gotoxy(1,32);
			printf("\nPlayer wins!\n");
			return 3;
		}
		gotoxy(1,32);
		printf("\nPlayer wins!\n");
		return 1;
	}
	while(dvalue1<=21 || dvalue2<=21){
		distribute(deck,deck_idx,idx,didx,dealer,dealer_idx);
		dealer_idx++;
		deck_idx++;
		dvalue1+=dealer[dealer_idx-1];
		dvalue2+=dealer[dealer_idx-1];
		printcard(dealer[dealer_idx-1],didx[dealer_idx-1],dtype);
		dtype++;
		bool x=false;
		if(dealer[dealer_idx-1]==1){
			for(size_t i=0;i<dealer_idx-1;i++){
				if(dealer[i]==1){
					x=true;
				}
			}
			if(x==false){
				dvalue2+=10;
			}
		}
		game_print(dealer,dealer_idx,player,player_idx,dvalue1,dvalue2,pvalue1,pvalue2,var);
		if(check_win_21(dvalue1,dvalue2)==true || check_win(pvalue1,dvalue1,dvalue2)==1){
			if(isdub==true){
				gotoxy(1,32);
				printf("\nDealer wins!\n");
				return 4;
			}
			gotoxy(1,32);
			printf("\nDealer wins!\n");
			return 0;
		}
		if(check_win(pvalue1,dvalue1,dvalue2)==2){
			if(isdub==true){
				gotoxy(1,32);
				printf("\nPlayer wins!\n");
				return 3;
			}
			gotoxy(1,32);
			printf("\nPlayer wins!\n");
			return 1;
		}
		if(check_win(pvalue1,dvalue1,dvalue2)==3){
			gotoxy(1,32);
			printf("\nIts a Draw!\n");
			return 2;
		}
		if(dvalue1>21 && dvalue2>21){
			if(isdub==true){
				gotoxy(1,32);
				printf("\nDealer Busts! Player wins!\n");
				return 3;
			}
			gotoxy(1,32);
			printf("\nDealer Busts! Player wins!\n");
			return 1;
		}
	}
	return 0;
}
//continua/gioca ancora
int playagain(int type){
	bool valid=false;
	char option;
	if(type==1){
		while(valid==false){
			gotoxy(1,22);
			printf("\npress Enter to continue or any other to leave: \n");
			option=getch();
			if (kbhit()){
				option=getch();
			}
			switch(option)
			{
				case 13:
					valid=true;
					return 1;
					break;
				default:
					return 0;
					break;
			}
		}
	}
	if(type==2){
		while(valid==false){
			gotoxy(1,33);
			printf("\npress Enter to play again or press 'a' to add money to balance or press 'c' to change current bet or any other to leave: \n");
			option=getch();
			if (kbhit()){
				option=getch();
			}
			switch(option)
			{
				case 13:
					valid=true;
					return 1;
					break;
				case 'a':
					valid=true;
					return 2;
					break;
				case 'c':
					valid=true;
					return 3;
					break;
				default:
					return 0;
					break;
			}
		}
	}

}
//main
int main(){
	srand(time(NULL));
	int cards[52];
	int idx[52];
	cardalg(cards,idx);
	int wins=0,draws=0,losses=0;
	float balance;
	float bet;
	mainmenu();
	if(playagain(1)==0){
		exit(0);
	}
	system("cls");
	gotoxy(1,1);
	printf("To start things off how much money are you willing to spend?");
	gotoxy(1,3);
	printf("Insert your balance (max balance $1m): ");
	bool isbal=false;
	while(isbal==false){
		scanf("%f",&balance);
		if(balance>0 && balance<1000001){
			system("cls");
			printf("Next step is selecting the size of the bet:");
			bet=betsize(balance);
			isbal=true;
		}
		else{
			printf("Invalid ammount!\n");
		}
	}
	int x=1;
	while(x>0){
		if(x==2){
			balance=addbalance(balance);
		}
		if(x==3){
			system("cls");
			bet=betsize(balance);
		}
		system("cls");
		int space=50;
		char s=' ';
		printf("Balance: %.2f$ at %.0f$/bet %*c Wins: %i - Draws: %i - Losses: %i\n",balance,bet,space,s,wins,draws,losses);

		int y=0;
		y=game(cards,idx,balance,bet);
		if(y==0){
			losses+=1;
			balance-=bet;
		}
		if(y==1){
			wins+=1;
			balance+=bet;
		}
		if(y==2){
			draws+=1;
		}
		if(y==3){
			wins+=1;
			balance+=2*bet;
		}
		if(y==4){
			losses+=1;
			balance-=2*bet;
		}
		if(y==5){
			wins+=1;
			balance+=3*(bet/2.0);
		}
		if(balance<bet){
			gotoxy(1,34);
			printf("Balance too low! Game Over.                           ");
			x=false;
		}
		else{
			x=playagain(2);
		}
	}
}