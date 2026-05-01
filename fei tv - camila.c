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
// Protótipo 
void cadastrar();
void fazerLogin();
void menuFilmes(char nomeUsuario[]);
void gerenciarFavoritos(char nomeUsuario[]);
void salvarFavorito(char nomeUsuario[], char filme[]);
void verFavoritos(char nomeUsuario[]);
void excluirFavorito(char nomeUsuario[]);

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
        setbuf(stdin, NULL); //Limpa buffer do teclado (evita bugs com fgets).
        if(opcao == 1) cadastrar();
        else if(opcao == 2) fazerLogin();
    } while(opcao != 3); //repete ate quer sair 
    return 0;
}

void cadastrar() { //funcao cadastrar
    Usuario u;
    FILE *arq = fopen("usuarios.txt", "a"); //abre o arquivo do tipo appende NAO ESQUECER DE FECHAR
    printf("\ncadastro");
    printf("\nDigite seu nome: ");
    fgets(u.nome, 50, stdin);
    u.nome[strcspn(u.nome, "\n")] = 0; //le o nome digitado - Remove \n do final.
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
//login 
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

            char *token = strtok(linha, ";"); //divide a linha por;
            if (token != NULL) {
                strcpy(nomeArq, token);
                token = strtok(NULL, ";");
                if (token != NULL) {
                    strcpy(logArq, token);
                    token = strtok(NULL, "\n");
                    if (token != NULL) {
                        strcpy(senArq, token);
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

    printf("\n\nFILMES DISPONIVEIS PARA ASSISTIR");
    printf("\n1- Gente Grande (Comedia)");
    printf("\n2- Homem Aranha (Acao)");
    printf("\n3- Rapunzel (Romance)");
    printf("\n4- Invocacao do Mal (Terror)");
    printf("\n0- Voltar ao Menu Principal");

    printf("\n\nescolha o numero do filme que voce deseja assistir: ");
    scanf("%d", &escolha);
    setbuf(stdin, NULL);

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
        setbuf(stdin, NULL);

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
    FILE *arq = fopen("favoritos.txt", "r");
    char linha[100], userArq[50], filmeArq[50];
    int encontrou = 0;

    printf("\nSUA LISTA DE FAVORITOS");
    if (arq == NULL) { // Se n tiver nada salvo na lista de favoritos aparece alg mensagem 
        printf("\nNenhum favorito ainda.");
        return;
    }
    while (fgets(linha, 100, arq)) { //le linha por linha
        char copia[100];
        strcpy(copia, linha);
        char *token = strtok(copia, ";");
        if(token != NULL) {
            strcpy(userArq, token);
            token = strtok(NULL, "\n");
            if(token != NULL) {
                strcpy(filmeArq, token);
                if (strcmp(nomeUsuario, userArq) == 0) {
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
void excluirFavorito(char nomeUsuario[]) { 
    char filmeExcluir[50];
    printf("\nDigite o nome do filme exato para excluir: "); 
    fgets(filmeExcluir, 50, stdin);
    filmeExcluir[strcspn(filmeExcluir, "\n")] = 0;

    FILE *arq = fopen("favoritos.txt", "r"); // le o arquivo original 
    FILE *temp = fopen("temp.txt", "w");

    if (arq != NULL && temp != NULL) {
        char linha[100], userArq[50], filmeArq[50];
        while (fgets(linha, 100, arq)) {
            char copiaLinha[100];
            strcpy(copiaLinha, linha);
            
            char *token = strtok(linha, ";");
            if(token != NULL) {
                strcpy(userArq, token);
                token = strtok(NULL, "\n");
                if(token != NULL) {
                    strcpy(filmeArq, token);
                    if (!(strcmp(nomeUsuario, userArq) == 0 && strcmp(filmeExcluir, filmeArq) == 0)) { //Se não for o filme a excluir, copia pro novo arquivo.
                        fprintf(temp, "%s", copiaLinha);
                    }
                }
            }
        }
        fclose(arq);
        fclose(temp);
        remove("favoritos.txt");//Substitui arquivo antigo pelo novo.
        rename("temp.txt", "favoritos.txt");
        printf("\nFilme removido dos favoritos!");
    }
}
