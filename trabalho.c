#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**  *(void **)(pbuffer) = apontar para primeira celula
    *(void **)(ponteiro que é pbuffer + sizeof(void *)) = apontar para ultima celula
    *(void **)(ponteiro que é  pbuffer + (sizeof(void *) * 2)) = para leitura e quantidade de inserções
    *(int *)(ponteiro que é  pbuffer + (sizeof(void *) * 2) + (sizeof(int))) = inteiro usado para opções do menu
    *(char *)(ponteiro que é pbuffer + (sizeof(void *) * 2) + (sizeof(int) * 2)) = inteiro para buscar informações

    ---------POSIÇÕES DOS DADOS DENTRO DA LISTA
     1- primeira posição é a string com 10 char para o nome.
     2- *(int *)(ponteiro + (sizeof(char) * 10)) = A UM VALOR INTEIRO REFERENTE A IDADE
     3- *(int *)(ponteiro + (sizeof(char) * 10) + sizeof(int)) = SEGUNDO VALOR INT REFERENTE AO TELEFONE
     4- *(void **)(ponteiro + (sizeof(char) * 10) + (sizeof(int) * 2)) = É O PONTEIRO VOOID QUE APONTA PARA QUEM VEM ANTES
     5- *(void **)(ponteiro + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))) = ..... aponta para quem vem depois
**/  


void *head(void);
void limpaponteiro(void *pbuffer);
void insere(void *pbuffer);
void addinfo(void *novacelula);
void remover(void *pbuffer);
void buscanome(void *pbuffer);
void traslista(void *pbuffer);

int main(){
    void *pbuffer=NULL;
    pbuffer=head();
    for(;;){
        printf("\n\nInforme o valor de sua escolha\n   [1] - Inserir um nome\n   [2] - Remover o primeiro nome\n   [3] - Buscar um nome\n   [4] - Listar nomes\n   [5] - sair\n   Informe valor: ");
        scanf("%d",&(*(int *)(pbuffer + (sizeof(void *) *2) + (sizeof(int)))));
        switch (*(int *)(pbuffer + (sizeof(void *) *2) + (sizeof(int)))){
            case 5:
                limpaponteiro(pbuffer);
                free(pbuffer);
                exit(1);
                break;
            case 1:
                insere(pbuffer);
                break;
            case 2:
                remover(pbuffer);
                break;    
            case 3:
                buscanome(pbuffer);
                break;
            case 4:
                traslista(pbuffer);
                break;    
            default:
                system("cls");
                printf("\n\n----VALOR INVALIDO -----\nTente novamente\n\n");
                break;
        };
    };
    exit(0);
};

void traslista(void *pbuffer){
    if (*(int *)(pbuffer + (sizeof(void *) * 2)) == 0){ // se a lista não tiver nenhuma inserção
        system("cls");
        printf("\n\n----LISTA ESTAVA VAZIA-----\n\n");
    } else{
        void *PROX; // variavel para percorrer a lista
        PROX = *(void **)(pbuffer); // PROX recebe a cabeça da lista para percorrer toda ela desde o inicio
        system("cls");

        void *auxiliar;
        printf("\nLISTA COMPLETA: \n");
        while (PROX != NULL){ // ENQUANTO A INFORMAÇÃO DO SEGUNDO VOID QUE ESTA CONTIDO EM PROX, NÃO FOR NULL (ULTIMA CÉLULA)
            auxiliar = PROX; 
            printf("\nNome: ");
            while (*(char *)auxiliar != '\0'){ // enquanto não for o ultimo caracter contido em char
                putchar(*(char *)auxiliar);
                auxiliar= auxiliar + sizeof(char); // incremento
            };
            printf("\nIdade: %d", *(int *)(PROX + (sizeof(char) * 10))); //informa a valor contido no primeiro espaço de memoria int da celula
            printf("\nTelefone: %d\n", *(int *)(PROX + (sizeof(char) * 10) + sizeof(int))); // informa a valor contido no segundo espaço de memoria int da celula
       
            PROX = *(void **)(PROX + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))); // incremento mesmo que x=x+1
        };
    };
};


void buscanome (void *pbuffer){
    if (*(void **)(pbuffer + (sizeof(void *) * 2)) == 0){ // caso ainda não tenha nenhuma inserção na lista
        printf("\n\n----LISTA JA ESTA VAZIA----\n\n");
        return;
    };

    system("cls");
    void *procura;
    procura = *(void **)(pbuffer); // procura, será um ponteiro que ira percorrer o pbuffer desde a primeira célula até chegar na info desejada
    printf("Qual nome deseja buscar: ");
    setbuf(stdin,NULL);
    scanf("%10s", &(*(char *)(pbuffer + (sizeof(void *) * 2) + (sizeof(int) * 2)))); // utilizado o espaço char de pbuffer para armazenar o nome a ser buscado
    system("cls");
    printf("-----DADOS ENCONTRADOS NO SISTEMA:\n");

    void *auxiliar;
    while( procura != NULL){ // irá ficar em loop para que o procura, possa percorrer todo o pbuffer
        if (strcmp((char *)(pbuffer + (sizeof(void *) * 2) + (sizeof(int) * 2)) , (char *)(procura)) == 0){ // valor 0 quer dizer que ambas possuem mesmo tamanho ou seja são iguais
            auxiliar= procura; // assim que identificado igualdade, auxiliar apontará para a mesma info que o procura
            printf("\n\nNome: ");
            while (*(char *)auxiliar != '\0'){
                putchar(*(char *)auxiliar);  // para printar toda a informação char que possuir no campo char 
                auxiliar = (auxiliar + sizeof(char));
            };
            printf("\nIdade %d", *(int *)(auxiliar + (sizeof(char) *10))); // trará a info de idade no primeiro campo int dos buffers de inserção
            printf("\nTelefone: %d\n", *(int *)(auxiliar + (sizeof(char) *10) + (sizeof(int)))); // tras a info do 2 valor int dentro dos buffers de inserção
          
        };
         procura = *(void **)(procura + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))); // mesma coisa que um x=x+1 para dar sequencia no while que estará em funcionamento
    };
    return;
};


void remover(void *pbuffer){
    void *inicio, *final; // para armazenarem o inicio e final do pbuffer

    if (*(void **)(pbuffer + (sizeof(void *) * 2)) == 0){ // Caso a lista esteja vazia
        printf("\n\n----LISTA JA ESTAVA VAZIA -----\n\n");
    };
    if (*(void **)(pbuffer + (sizeof(void *) * 2)) == 1){ // caso seja uma lista de um só elemento
        *(void **)(pbuffer + (sizeof(void *) * 2)) = *(void **)(pbuffer + (sizeof(void *) * 2)) - (int)1; //diminuo um elemento do inteiro que armazena a quantidade de inserções (uma espécie de x=x-1)
        inicio = *(void **)(pbuffer);
        free(inicio);
        printf("\n\n Dados da celula 1 foram removidos\n\n");
    }else{ // caso seja uma lista com diversas inserções
        *(void **)(pbuffer + (sizeof(void *) * 2)) = *(void **)(pbuffer + (sizeof(void *) * 2)) - (int)1; // diminuo um elemento do inteiro que armazena a quantidade de inserções (uma espécie de x=x-1)
        inicio = *(void **)(pbuffer); // inicio recebe os dados iniciais de pbuffer
        final = *(void **)(inicio + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))); // final, recebe a informação de ponteiro (->prox) da celula inicial do pbuffer (ou seja a celula 2)
        *(void **)(pbuffer) = final; // celula inicial do pbuffer passa a ser a 2, conforme o "final" esta apontando
        *(void **)(final + (sizeof(char) * 10) + (sizeof(int) * 2)) = NULL; // celula 2 passa a apontar NULL como seu antecessor, ou seja agora ela é a primeira
        free(inicio);
        printf("\n\n DADOS DA CELULA 1 FORAM REMOVIDOS\n\n");
    };
};

void *head(void){
    void *pbuffer;
    pbuffer=(void *)malloc((sizeof(int *) *2) + (sizeof(void *) * 2) + (sizeof(char *) * 10));  // 2 int para (quantidade, idade, telefone) 
    if( pbuffer == NULL){
        printf("\n\n----- ERRO EM ALOCAR MEMORIA -----");
        exit(1);
    }
    *(int *)(pbuffer + (sizeof(void *) * 2)) = 0;   //usarei essa expressão sempre que for incrementar uma nova unidade de informações
    *(void **)(pbuffer) = NULL;
    *(void **)(pbuffer + sizeof(void *)) = NULL;
    return pbuffer;
};

void limpaponteiro(void *pbuffer){
	void *auxiliar = *(void **)(pbuffer); // recebe as info da cabeça do pbuffer (o inicio)
    void *PROX = *(void **)(pbuffer);    // mesma coisa que o auxiliar

    while (PROX != NULL){ // enquanto a info do segundo void (que aponta para o final ->prox) não for NULL (fim da lista)
        auxiliar = PROX;
        PROX = *(void **)(PROX + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))); // mesma coisa que um x=x+1 é um incremento que direciona para a proxima celula. ele percorre todo o bloco existe e vai para o proximo (->prox) do bloco de informações seguinte
        free(auxiliar);
    };
};

void insere(void *pbuffer){
    void *novacelula;
    novacelula=(void *)malloc((sizeof(char *) *10) + ((sizeof(int *) *2) + (sizeof(void *) *2)));  // crio nova celula para receber dados e aloco espaço para a mesma
    
    void *PROX; // recebera infos do pbuffer para percorrer lista, será o mesmo que ->PROX
    void *ANTE; // .......... mesmo que ->ANTERIOR

    if( novacelula == NULL ){
        printf("\n\n ------ ERRO AO ALOCAR MEMORIA  ------\n\n");
        exit(1);
    }
    *(void **)(pbuffer + ((sizeof(void *) * 2))) = *(void **)(pbuffer + ((sizeof(void *) * 2))) + (int)1; // aumentei uma inidade no void do pbuffer

    addinfo(novacelula); // chama a função que vai receber as informações do usuário na celula recem criada

    if( *(int *)(pbuffer + (sizeof(void *) *2)) == 1 ){  // ou seja, se for a primeira inserção de dados
        *(void **)pbuffer = novacelula;       // primeira celula aponta para celula que recebe novas informações
        *(void **)(pbuffer + (sizeof(void *))) = novacelula;    // ultima celula do buffer aponta  também para as novas informações
        *(void **)(novacelula + (sizeof(int) *2) + (sizeof(char) *10)) = NULL; // faço o ponteiro andar até a memoria alocada para o primeiro void que é o PONTEIRO QUE APONTA PARA A PRIMEIRA CELULA
        *(void **)(novacelula + (sizeof(int) *2) + (sizeof(char) *10) + (sizeof(void *))) = NULL; // ponteiro anda até o segundo void, onde é o PONTEIRO QUE APONTA PARA ULTIMA CÉLULA
    } else{ // caso não seja a primeira inserção
        PROX=*(void **)pbuffer; // recebe as informações apontadas no pbuffer, pois será usado para saber se a nova inserção é maior ou menor (vem antes ou depois) do que já esta no pbuffer
        while( (strcmp((char *)novacelula, (char *)PROX) == 1) && (*(void **)(PROX + (sizeof(int) *2) + (sizeof(char) *10) + (sizeof(void *))) != NULL) ){  // enquanto a novacelula for maior que as informações que já existem em pbuffer e o indice apontado em pbuffer for diferente do null ÚLTIMO, o while ira ficar percorrendo
            PROX = *(void **)(PROX + (sizeof(int) *2) + (sizeof(char) *10) + (sizeof(void *)));  // mesma coisa que um PROX=PROX+1
        }
        if( (strcmp((char *)novacelula, (char *)PROX) == 1) && (*(void **)(PROX + (sizeof(int) *2) + (sizeof(char) *10) + (sizeof(void *))) == NULL) ){ // ultimo elemento da lista
            PROX = *(void **)(pbuffer + (sizeof(void *)));  // PROX agora aponta para  a ultima celula
            *(void **)(pbuffer + (sizeof(void *))) = novacelula; // agora endereço que apontava para o ultimo elemento no PBUFFER apontará para as novas informações
            *(void **)(novacelula + (sizeof(int) *2) + (sizeof(char) *10) + sizeof(void *)) = NULL;  //agora o ->PROX (nesse caso o void *) aponta para NULL, pq ele é o ultimo elemento
            *(void **)(novacelula + (sizeof(int) *2) + (sizeof(char) *10)) = PROX; // assim a novacelula aponta seu void anterior (->ante) para informação que já existia no pbuffer
            *(void **)(PROX + (sizeof(int) *2) + (sizeof(char) *10) + (sizeof(void *))) = novacelula; // ultimo elemento do pbuffer apontará para celula recem inserido ao final
        }else if ( *(void **)(PROX + (sizeof(int) *2) + (sizeof(char) *10)) == NULL){ // caso a nova informação seja a menor e se torne a primeira inserção de uma lista que já contenha informações
            *(void **)(pbuffer) = novacelula; // cabeça do pbuffer aponta para novas informações
            *(void**)(novacelula + (sizeof(int) *2) + (sizeof(char) *10)) = NULL; // agora a nova celula de informações aponta como NULL para um elemento anterior, já que ela é a primeira celula
            *(void **)(novacelula + (sizeof(int) *2) + (sizeof(char) *10) + (sizeof(void *))) = PROX;  // o void que possui a função de (->PROX) aponta para os elementos que já estavam em PROX/pbuffer
            *(void **)(PROX + (sizeof(int) *2) + (sizeof(char) *10)) = novacelula; // assim o ->ante aponta para os elmentos novos
        }else{    // caso seja uma inserção ao centro ou entre outras informações
            ANTE = *(void **)(PROX + (sizeof(int) *2) + (sizeof(char) *10)); // agora esta celula ira receber o apontamento para a anterior de PROX 
            *(void **)(novacelula + (sizeof(int) *2) + (sizeof(char) *10)) = ANTE; // nova informação apontara para elementos anteriores que ja estavam apontados  pelo PROX, que foi também apontado pelo ANTE
            *(void **)(novacelula + (sizeof(int) *2) + (sizeof(char) *10) + (sizeof(void *))) = PROX; // novas informações apontam para os elementos da frente, conforme o PROX já fazia
            *(void **)(ANTE + (sizeof(int) *2) + (sizeof(char) *10) + (sizeof(void *))) = novacelula; // elementos anteriores a nova informação, apontaram para a nova informação
            *(void **)(PROX + (sizeof(int) *2) + (sizeof(char) *10)) = novacelula; // informações que estarão a frente das novas, estão apontando para as novas informações inseridas
            }
        }
};


void addinfo(void *novacelula){
    printf("\nInforme o nome: ");
    setbuf(stdin,NULL);
    scanf("%10s", &(*(char *)novacelula)); 
    printf("Idade: ");
    scanf("%d", &(*(int *)(novacelula + (sizeof(char) *10 ))));
    printf("Telefone: ");
    scanf("%d", &(*(int *)(novacelula + (sizeof(char) *10 ) + (sizeof(int)))));
};