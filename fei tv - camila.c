//projeto fei tv - camila dos reis silva//
//O objetivo do projeto FEItv é construir uma plataforma de informações de vídeos, como filmes e séries
//apenas para compartilhamento de informações sobre vídeos, não é preciso reproduzir os vídeos.
//É obrigatório o uso de arquivos de texto (.txt ou similar)


//• Cadastrar novo usuário - ja fiz
//• Login de usuário - ja fiz
//• Buscar vídeo por nome
//• Listar informações de vídeos buscados
//• Curtir e descurtir vídeos
//• Gerenciar favoritos:
//• Criar, editar, excluir lista de reprodução de vídeos favoritos
//• Adicionar/remover vídeos da lista de favoritos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// estrutura do usuario 
typedef struct {
    char nome[50];
    char login[50];
    char senha[20];
} Usuario;
// declaraco antecipadas-prototipos 
void cadastrar();
void fazerLogin();
void menuFilmes(char nomeUsuario[]);
void gerenciarFavoritos(char nomeUsuario[]);
void salvarFavorito(char nomeUsuario[], char filme[]);
void verFavoritos(char nomeUsuario[]);
void excluirFavorito(char nomeUsuario[]);
 
// usar do-while para manter o menu principal rodando até que escolha sair
int main() {
    int opcao;
    do { // variavel do menu
        printf("\nBEM VINDO AO FEI TV");
        //criar um loop para repetir menu 
        printf("\n1 - Cadastro");
        printf("\n2 - Login");
        printf("\n3 - Sair");
        printf("\nEscolha: ");
        if (scanf("%d", &opcao) != 1) return 0; //le a opcao escolhida do usuario
        setbuf(stdin, NULL); //Limpa o buffer do teclado,isso evita que o "Enter" que eu dei atrapalhe a leitura de textos (strings) nas próximas funções.
        if(opcao == 1) cadastrar();
        else if(opcao == 2) fazerLogin();
    } while(opcao != 3); //repete ate quer sair 
    return 0;
}

void cadastrar() { //funcao cadastrar- cria um novo usuario no arquivo
    Usuario u;
    FILE *arq = fopen("usuarios.txt", "a"); //abre o arquivo do tipo appende NAO ESQUECER DE FECHAR
    printf("\ncadastro");
    printf("\nDigite seu nome: ");
    fgets(u.nome, 50, stdin);//Lê o que você digita.
    u.nome[strcspn(u.nome, "\n")] = 0; //le o nome digitado - Remove \n do final para n quebrar a formatação do arquivo.
    printf("Crie um login: "); //le oq esta sendo digitado 
    fgets(u.login, 50, stdin);
    u.login[strcspn(u.login, "\n")] = 0;//le o nome digitado - Remove \n do final
    printf("Crie uma senha: ");
    fgets(u.senha, 20, stdin);
    u.senha[strcspn(u.senha, "\n")] = 0;
    if (arq != NULL) {
        fprintf(arq, "%s;%s;%s\n", u.nome, u.login, u.senha); //salva no arquivo - nome;login;senha
        fclose(arq); //ARQUIVO FECHADO
        printf("\nCadastro realizado com sucesso! Bem vindo ao seu FEI TV, %s!", u.nome);
        menuFilmes(u.nome); //Vai direto para o menu de filmes que criei
    }
}
//login - onde o programa vai conferir se vc tem acesso
void fazerLogin() {
    char logBusca[50], senBusca[20]; //dados digitados 
    char linha[150], nomeArq[50], logArq[50], senArq[20];
    int encontrou = 0;

    printf("\nlogin!");
    printf("\nLogin: ");
    fgets(logBusca, 50, stdin);
    logBusca[strcspn(logBusca, "\n")] = 0;

    printf("Senha: ");
    fgets(senBusca, 20, stdin);
    senBusca[strcspn(senBusca, "\n")] = 0;

    FILE *arq = fopen("usuarios.txt", "r"); //abre arquivo leitura - nao esquecer de fechar
    if (arq != NULL) {
        while (fgets(linha, 150, arq)) { //le linha por linha 
            if (strlen(linha) < 5) continue; // Pula linhas vazias ou corrompidas

            char *token = strtok(linha, ";"); //divide a linha por; - ele corta a linha no promeiro ;
            if (token != NULL) {
                strcpy(nomeArq, token); //primeito pedaço vira o nome 
                token = strtok(NULL, ";");
                if (token != NULL) {
                    strcpy(logArq, token); //o segundo vira o login
                    token = strtok(NULL, "\n");
                    if (token != NULL) {
                        strcpy(senArq, token); // o terceiro vira a senha
                        if (strcmp(logBusca, logArq) == 0 && strcmp(senBusca, senArq) == 0) { //compara login e senha 
                            encontrou = 1;
                            break;
                        }
                    }
                }
            }
        }
        fclose(arq);
    }

    if (encontrou) { // se encontar vai para filmes 
        printf("\nSeja bem vindo novamente ao seu FEI TV, %s!", nomeArq);
        menuFilmes(nomeArq);
    } else {
        // Se não existir, pergunta se quer cadastrar
        int op;
        printf("\nVoce nao possui cadastro. Deseja fazer cadastro? 1-Sim / 2-Nao: ");
        scanf("%d", &op);
        setbuf(stdin, NULL);
        if (op == 1) {
            cadastrar();
        } else {
            printf("\nate a proxima...desligando");
            exit(0); // Encerra o programa como você pediu[cite: 6]
        }
    }
} 

//criar a parte dos filems disponiveis 
void menuFilmes(char nomeUsuario[]) {
    int escolha, gostou, fav;
    char listaFilmes[4][30] = {"Gente Grande", "Homem Aranha", "Rapunzel", "Invocacao do Mal"}; // lista de filmes 
    //matriz de strings que guarda os títulos fixos dos filmes.
    printf("\n\nFILMES DISPONIVEIS PARA ASSISTIR");
    printf("\n1- Gente Grande (Comedia)");
    printf("\n2- Homem Aranha (Acao)");
    printf("\n3- Rapunzel (Romance)");
    printf("\n4- Invocacao do Mal (Terror)");
    printf("\n0- Voltar ao Menu Principal");

    printf("\n\nescolha o numero do filme que voce deseja assistir: ");
    scanf("%d", &escolha);
    setbuf(stdin, NULL);//serve para limpar o lixo do teclado.

    if(escolha == 0) return;

    if(escolha >= 1 && escolha <= 4) {
        // Mostra a sinopse baseada na escolha do filme 
        if(escolha == 1) printf("\nSinopse: Amigos se reunem apos anos para um fim de semana divertido.");
        if(escolha == 2) printf("\nSinopse: Peter Parker luta contra o crime apos ganhar superpoderes.");
        if(escolha == 3) printf("\nSinopse: Uma jovem de cabelos magicos foge da torre com um bandido.");
        if(escolha == 4) printf("\nSinopse: Investigadores paranormais enfrentam uma entidade sombria.");

        printf("\n\ndeseja curtir o filme escolhido %s? 1-Sim / 2-Nao: ", listaFilmes[escolha-1]);
        scanf("%d", &gostou);
        setbuf(stdin, NULL);
        if (gostou == 1) {
            printf("\nCurtido! Deseja adicionar aos favoritos? 1-Sim / 2-Nao: ");
            scanf("%d", &fav);
            setbuf(stdin, NULL);
            if (fav == 1) {
                salvarFavorito(nomeUsuario, listaFilmes[escolha-1]);//Salva no arquivo.
                //se curtir e favoritar, o programa abre favoritos.txt e salva seu nome junto com o nome do filme escolhido
                gerenciarFavoritos(nomeUsuario);
            }
        } else {
            printf("\nQue pena que voce nao gostou desse filme, mas temos outros disponiveis!\n");
            menuFilmes(nomeUsuario);
        }
    }
}

void salvarFavorito(char nomeUsuario[], char filme[]) {
    FILE *arq = fopen("favoritos.txt", "a"); //arquivo favorito sendo aberto
    if (arq != NULL) {
        fprintf(arq, "%s;%s\n", nomeUsuario, filme);
        fclose(arq);
        printf("\nFilme adicionado aos favoritos!");
    }
}
void gerenciarFavoritos(char nomeUsuario[]) { // criar um menu interno para a parte de favoritos 
    int op;
    do {
        printf("\n\nMEUS FAVORITOS");
        printf("\n1 - Ver lista de favoritos");
        printf("\n2 - Adicionar mais filmes");
        printf("\n3 - Excluir filmes dos favoritos");
        printf("\n4 - Voltar para lista de filmes");
        printf("\nEscolha: ");
        scanf("%d", &op);
        setbuf(stdin, NULL);//desativa o buffer do teclado para que o programa leia os dados diretamente, evitando que "restos" de comandos anteriores (como o \n do Enter) façam o código pular perguntas.

        if(op == 1) verFavoritos(nomeUsuario);
        else if(op == 2) menuFilmes(nomeUsuario);
        else if(op == 3) excluirFavorito(nomeUsuario);
        else if(op == 4) {
            menuFilmes(nomeUsuario);
            return; 
        }
    } while(op != 4);
}

void verFavoritos(char nomeUsuario[]) {
    FILE *arq = fopen("favoritos.txt", "r"); //abriu aquivo tivo ler - FECHAR DPS
    //(ponteiro para manipulacao de arquivo)
    char linha[100], userArq[50], filmeArq[50];
    int encontrou = 0;

    printf("\nSUA LISTA DE FAVORITOS");
    if (arq == NULL) { // Se n tiver nada salvo na lista de favoritos aparece alg mensagem 
        printf("\nNenhum favorito ainda.");
        return;
    }
    while (fgets(linha, 100, arq)) { //le linha por linha inteira do arquivo
        char copia[100]; //guarta ate 100 caract. na variavel linha
        strcpy(copia, linha); //criei uma copia da linha original 
        char *token = strtok(copia, ";"); 
        if(token != NULL) { //Se a função não encontrar o separador ; ou se a linha estiver vazia retorna nada
            strcpy(userArq, token); //copia o texto que o token esta apontando p dentro da variável userArq, salvando o nome do usuário permanentemente.
            token = strtok(NULL, "\n"); //O NULL função continuar de onde ela parou no corte anteriorç-agora ela vai até o final da linha (\n).
            if(token != NULL) {
                strcpy(filmeArq, token); //salva nome do filme
                if (strcmp(nomeUsuario, userArq) == 0) { //Compara o nome do usuário que está logado com o nome que acabamos de ler no arquivo,se for = o filme eh seu
                    printf("\n- %s", filmeArq);
                    encontrou = 1;
                }
            }
        }
    }
    if(!encontrou) printf("\nSua lista esta vazia."); 
    fclose(arq);
}
//criar a parte de excluir o filme dos favoritos 
//lembrar disso para criar essa parte do meu codigo 
//para excluir um dado em C, não "apagamos" uma linha diretamente. A lógica usada aqui é:
//Abrir o arquivo original para leitura ("r") e um arquivo temporário para escrita ("w").
//Ler todas as linhas do original.
//Se a linha NÃO for o filme que você quer excluir, copia ela para o arquivo temporário.
//Se a linha FOR o filme escolhido, o programa simplesmente não a copia.
//No final, o arquivo original é deletado (remove) e o temporário é renomeado para o nome oficial (rename).
void excluirFavorito(char nomeUsuario[]) {  
    char filmeExcluir[50]; //vai guardar o nome do filme que o usuário quer excluir
    printf("\nDigite o nome do filme exato para excluir: "); 
    fgets(filmeExcluir, 50, stdin);
    filmeExcluir[strcspn(filmeExcluir, "\n")] = 0;
//le o nome do film digitado
    FILE *arq = fopen("favoritos.txt", "r"); // le o arquivo original 
    FILE *temp = fopen("temp.txt", "w");  //Para excluir, você abre o original para leitura e cria um novo arquivo chamado temp.txt (temporário) para escrita

    if (arq != NULL && temp != NULL) { //confirmando se arquivo abriu ok
        char linha[100], userArq[50], filmeArq[50];
        while (fgets(linha, 100, arq)) { //strtok separa userArq e filmeArq
            char copiaLinha[100];
            strcpy(copiaLinha, linha);
            //Faz uma cópia da linha original strtok vai modificar linha
            
            char *token = strtok(linha, ";"); //divide a linah por;
            if(token != NULL) { //verifica se seu certo 
                strcpy(userArq, token); //guasrda nome do usuario
                token = strtok(NULL, "\n"); //aqui continua e pega o filem
                if(token != NULL) {//verfica se pegou 
                    strcpy(filmeArq, token);
                    if (!(strcmp(nomeUsuario, userArq) == 0 && strcmp(filmeExcluir, filmeArq) == 0)) { //Se não for o filme a excluir, copia pro novo arquivo.
                    //usuario eh o meso - filme eh o mesmo- eh extamente os registros q quer excluir 
                        fprintf(temp, "%s", copiaLinha); //copia a linha para um novo arquivo 
                    }
                }
            }
        }
        fclose(arq);
        fclose(temp);
        remove("favoritos.txt");//Substitui arquivo antigo pelo novo.
        rename("temp.txt", "favoritos.txt");//Renomeia o temporário para o nome original
        printf("\nFilme removido dos favoritos!");
    }
}
