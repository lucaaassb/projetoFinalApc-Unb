#include <stdio.h> 
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
//======================================================================================//
#define LIMPA_TELA system("clear");
//======================================================================================//
int menu(); //Cabeçalho do menu

//======================================================================================//
// Define o tipo Jogador, possuindo id, nome, posição e idade.
typedef struct jogador{
    int id;
    char nome[50];
    char posicao[50];
    int idade;
}Jogador;

// Define o tipo Time, possuindo 5 Jogadores, nome, e nome do técnico
typedef struct time{
    Jogador jogadores[5];
    char nome[50];
    char nome_tecnico[50];
}Time;

 /*Define o tipo JogadorPartida, que tem como objetivo criar uma forma de relacionar jogadores
com uma partida. Para cada jogador do seu time, em cada partida, devemos registrar as informações desse
jogador nessa partida. Criando esse tipo, basta "dizer" que Partida possui 5 'JogadorPartida'. Depois, conseguimos
analisar as partidas e analisar os dados de jogadores específicos, buscando por ID. */

typedef struct jogadores_partida{
    int id_jogador;
    int num_assistencias;
    int num_kills;
    int num_deaths;
}JogadorPartida;

 /*Define o tipo Partida, que possui dados quantitativos sobre a partida. Além disso, informa
se foi uma vitória ou não, e ainda possui 5 jogadores_partida, que são elementos que guardam os
dados quantitativos de cada jogador nessa partida.*/

typedef struct partida{
    int total_kills_time;
    int total_kills_adversario;
    char vitoria;
    int total_torres_destruidas_time;
    int total_torres_destruidas_adversario;
    int total_assist;
    JogadorPartida jogadores_partida[5];
}Partida;

Time cadastrar_time();
void listar_time(Time team);
Jogador cadastrar_jogador();
Time editar_jogador(Time team);
Partida cadastrar_partida(Time team);
void total_kill_assist(Partida partida[], int contPartidas);
Time pesquisar_jogador (Time team);
void listar_partidas(Partida partida[], Time team, int contPartidas);
void jogador_menor_pontuação(Partida partida[], Time team);
void jogador_maior_pontuação(Partida partida[], Time team);
//======================================================================================//
int main(){ 
	setlocale(LC_ALL,"Portuguese"); 

    int opcao, contPartidas = 0;
    Time team;
    Partida partida[20];

	do {
		opcao = menu();
		switch (opcao) {
			case 1:
                team = cadastrar_time(); 
                LIMPA_TELA; 
				break;
			case 2:
                listar_time(team);
				break;
            case 3:
                editar_jogador(team);
                break;
            case 4:
                cadastrar_partida(team);
                contPartidas++;
                break;
            case 5:
                listar_partidas(partida, team, contPartidas);
                break;
            case 6:
                pesquisar_jogador (team);
                break;
            case 7:
                total_kill_assist(partida, contPartidas);
                break;
            case 8:
                jogador_menor_pontuação(partida, team);
                break;
            case 9:
                jogador_maior_pontuação( partida, team);
                break;
            case 10:
                LIMPA_TELA;
                printf("Obrigado!");
                return 0;
                break;
		}
	}while (opcao != 10);
	
    return 0;  
} 
//======================================================================================//
int menu() { //MENU
	int op;
	printf("\n\n----------MENU----------\n\n");
    printf("1) Cadastrar time\n");
    printf("2) Listar time\n");
    printf("3) Editar time\n");
    printf("4) Cadastrar partida\n");
    printf("5) Listar partidas\n");
    printf("6) Pesquisar jogador\n");
    printf("7) Mostrar número total de kills e assistências\n");
    printf("8) Mostrar jogador com menor pontuação\n");
    printf("9) Mostrar jogador com maior pontuação\n");
    printf("10) Sair\n");
    printf("------------------------\n");
	printf("Digite sua opcao: ");
	scanf("%d", &op);
    LIMPA_TELA;
	return op;
}
//======================================================================================//
Time cadastrar_time(){
	Time novo_time;
	int contador_jogadores = 0;
    bool stop = false;

    printf("Insira o nome do seu time: \n");
	scanf(" %[^\n]", novo_time.nome);
    
    printf("Insira o nome do seu treinador: \n");
    scanf(" %[^\n]", novo_time.nome_tecnico);

    LIMPA_TELA;

	while(contador_jogadores != 5){
		novo_time.jogadores[contador_jogadores] = cadastrar_jogador();
		contador_jogadores++;
	}
	return novo_time;
}
//======================================================================================//
Partida cadastrar_partida(Time team){
    Partida nova_partida;
    int i = 0;
    /*
    a) Receber, para cada jogador do seu time, as seguintes informações:
        i) Número de assistências
            ii) Número de kills
                iii) Número de deaths
    b) Receber o número de kills do seu time
    c) Receber o número de kills do time adversário
    d) Receber o resultado da partida (vitória ou derrota)
    e) Receber o número de torres destruídas do seu time (max = 11)
    f) Receber o número de torres destruídas do time adversário (max = 11)*/
    
    nova_partida.total_kills_time = 0;
    nova_partida.total_kills_adversario = 0;
    nova_partida.total_assist = 0;

    for(i = 0; i < 5; i++){
        
        JogadorPartida jogador_partida;
        jogador_partida.id_jogador = i;

        printf("Insira o número de assistências do jogador %s: \n", team.jogadores[i].nome); // a) i
        scanf("%d", &jogador_partida.num_assistencias);
        nova_partida.total_assist += jogador_partida.num_assistencias;

        printf("Insira o número de kills do jogador %s: \n", team.jogadores[i].nome); // a) ii
        scanf("%d", &jogador_partida.num_kills);
        
        nova_partida.total_kills_time += jogador_partida.num_kills;

        printf("Insira o número de mortes do jogador %s: \n", team.jogadores[i].nome); // a) iii
        scanf("%d", &jogador_partida.num_deaths);

        LIMPA_TELA;

        nova_partida.total_kills_adversario += jogador_partida.num_deaths;

        nova_partida.jogadores_partida[i] = jogador_partida; 
    }

    do{
        printf("Qual foi o resultado da partida? (Vitória ou Derrota = V/D)\n"); // d)
        scanf("%c", &nova_partida.vitoria);
        LIMPA_TELA;
    } while(nova_partida.vitoria != 'V' && nova_partida.vitoria != 'D');

    do{
        printf("Quantas torres foram destruídas pela sua equipe? \n"); // e)
        scanf("%d", &nova_partida.total_torres_destruidas_time);
        LIMPA_TELA;
    } while(nova_partida.total_torres_destruidas_time < 0 || nova_partida.total_torres_destruidas_time > 11);

    do{
        printf("Quantas torres foram destruídas pela equipe adversária? \n"); // f)
        scanf("%d", &nova_partida.total_torres_destruidas_adversario);
        LIMPA_TELA;
    } while(nova_partida.total_torres_destruidas_adversario < 0 || nova_partida.total_torres_destruidas_adversario > 11);
}
//======================================================================================//
//void para listar o time 2
void listar_time(Time team){
//ID - Nome - Posição (ex.: 3 - Rafael - ADC )
    int i = 0;
    printf("Nome do Time: %s\n", team.nome);
    printf("Técnico: %s\n", team.nome_tecnico);
    
    for(i = 0; i < 5; i++){
        printf("ID: %d\t || Nome: %s\t || Posição: %s\t\n", i, team.jogadores[i].nome, team.jogadores[i].posicao);
    }
}
//======================================================================================//
Jogador cadastrar_jogador(){

    bool stop = false;
    Jogador novo_jogador;
    printf("Insira o nome do jogador: \n");
	scanf(" %[^\n]", novo_jogador.nome);
    
    stop = false;

    while(!stop){
        printf("Insira a posição do jogador: \n");
        scanf(" %[^\n]", novo_jogador.posicao);

        if (strcmp(novo_jogador.posicao, "ADC")){
            stop = true;
        } else if(strcmp(novo_jogador.posicao, "SUP")){
            stop = true;
        } else if(strcmp(novo_jogador.posicao, "JG")){
            stop = true;
        } else if(strcmp(novo_jogador.posicao, "MID")){
            stop = true;
        } else if(strcmp(novo_jogador.posicao, "TOP")){
            stop = true;
        } else { 
            printf("Posição inválida, insira novamente!\n");
        }
    } 

    do{
        printf("Insira a idade do jogador: \n");
        scanf("%d", &novo_jogador.idade);
    } while(novo_jogador.idade <= 0 || novo_jogador.idade > 150);    

    LIMPA_TELA;

    return novo_jogador;
}
//======================================================================================//
Time editar_jogador(Time team){

    listar_time(team);
    Jogador novo_jogador;

    int id = -1;
    char altera;

    do{
        printf("Insira o id que deseja alterar: ");
        scanf("%d", &id);
    } while(id >= 0 || id <= 4);

    novo_jogador = cadastrar_jogador();

    
    do{
        printf("Você realmente deseja alterar o jogador? (S/N) \n");
        scanf ("%c", &altera);
    } while(altera != 'N' && altera != 'S');

    if(altera == 'S'){
    team.jogadores[id] = novo_jogador;
    }

    return team;
}
//======================================================================================//
//void para listar as partidas 5
void listar_partidas(Partida partida[], Time team, int contPartidas){
    /*a) Listar todas as partidas cadastradas até o momento, apresentando as seguintes informações:
    i) Resultado
    ii) Número de kills do time
    iii) Número de deaths do time
    iv) Número de torres destruídas do time
    v) Número de torres destruídas do time adversário
    vi) Posição destaque
    (1) Posição destaque mostra a posição e o nome do jogador com maior pontuação
    na partida.*/
    int i = 0, j = 0, k = 0, id_pontMax = 0;

    for(i = 0; i < contPartidas - 1; i++){
        if(partida[i].vitoria == 'V'){
            printf("Resultado: Vitória! :)\n");
        } else {
            printf("Resultado: Derrota! :(\n");
        }

        printf("Número de kills do time: %d \n", partida[i].total_kills_time);

        printf("Número de deaths do time: %d \n", partida[i].total_kills_adversario);

        printf("Número de torres destruídas do time: %d \n", partida[i].total_torres_destruidas_time);

        printf("Número de torres destruídas do time adversário: %d \n", partida[i].total_torres_destruidas_adversario);

        int pontuacao[5], maiorNota = 0;

        for(j = 0; j < 5; j++){
            pontuacao[j] = partida[i].jogadores_partida[j].num_kills * 3;
            pontuacao[j] += partida[i].jogadores_partida[j].num_assistencias;
        }

        for(k = 0; k < 5; k++){
            if(pontuacao[j] > maiorNota){
                maiorNota = pontuacao[j];
            }
        }
        printf("Posição destaque: ");
        printf("O jogador que mais pontuou foi: %s, jogando na posição de: %s\n", team.jogadores[j].nome, team.jogadores[j].posicao);
    }
}
//======================================================================================//
//função para pesquisar jogadores 6
Time pesquisar_jogador (Time team){

    int id = -1;

    do{
        printf("Insira o id que deseja pesquisar: \n");
        scanf("%d", &id);
        if(id < 0 || id > 4){
            printf("ID não encontrado, o jogador não existe!\n");
            break;
        } else {
            printf("ID: %d\t || Nome: %s\t || Posição: %s\t\n", id, team.jogadores[id].nome, team.jogadores[id].posicao);
        }
    } while(id >= 0 || id <= 4);

}
//======================================================================================//
//void para mostrar número total de kills e assistências 7
void total_kill_assist(Partida partida[], int contPartidas){
    int i = 0, totalKill, totalAssist;

    for(i = 0; i < contPartidas - 1; i++){
        totalAssist += partida[i].total_assist;
        totalKill += partida[i].total_kills_time;
    }
    printf("O número total de assistências foi de: %d \n", totalAssist);
    printf("O número total de kills do time foi de: %d \n", totalKill);
}
//======================================================================================//
//void para mostrar jogador com menor pontuação 8 
void jogador_menor_pontuação(Partida partida[], Time team){
    int menorNota = 0, i = 0, j = 0, pontuacao[5];

    for(i = 0; i < 5; i++){
        pontuacao[i] = partida[i].jogadores_partida[i].num_kills * 3;
        pontuacao[i] += partida[i].jogadores_partida[i].num_assistencias;
    }

    for(j = 0; j < 5; j++){
        if(pontuacao[i] < menorNota){
            menorNota = pontuacao[i];
        }
    }
    printf("Jogador que menor pontuou: \n");
    printf("ID: %d\t || Nome: %s\t || Posição: %s\t || Pontuação: %d\t\n", i, team.jogadores[i].nome, team.jogadores[i].posicao, menorNota);
}
//======================================================================================//
//void para mostrar jogador com maior pontuação 9
void jogador_maior_pontuação(Partida partida[], Time team){
    int maiorNota, i = 0, j = 0, pontuacao[5];

    for(i = 0; i < 5; i++){
        pontuacao[i] = partida[i].jogadores_partida[i].num_kills * 3;
        pontuacao[i] += partida[i].jogadores_partida[i].num_assistencias;
    }

    for(j = 0; j < 5; j++){
        if(pontuacao[i] < maiorNota){
            maiorNota = pontuacao[i];
        }
    }
    printf("Jogador que maior pontuou: \n");
    printf("ID: %d\t || Nome: %s\t || Posição: %s\t || Pontuação: %d\t\n", i, team.jogadores[i].nome, team.jogadores[i].posicao, maiorNota);
}
//======================================================================================//
