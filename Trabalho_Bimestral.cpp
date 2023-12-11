// Lívia Gomes de Souza
// Mary Adryany Duarte Gonçalves da Silva
#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

#define TF 10

// Structs

struct TpClientes
{
	char NomeCli[30];
	int QtdeCompras;
	char CPF[11];
	float ValorTotComprado;
	char Status;
};

struct TpFornecedores
{
	int CodForn;
	char NomeForn[30], CidadeForn[30], Status;
};

struct TpData 
{
	int Dia, Mes, Ano;
};

struct TpProdutos
{
	int CodProd, Estoque, CodForn;
	char Descr[30], Status;
	float Preco;
	TpData DtValidade;
};

struct TpVendas
{
	int CodVenda;
	TpData DataVenda;
	float TotVenda;
	char ClienteCPF[12];
	char Status;
};

struct TpVendasProd//Mexi nessa struct - M
{
	int Qtde, CodProd, CodVenda;
	float ValorUnitario;
	char Status;
};

void LimparSaida(void){
	int x1 = 37, x2 = 88, y1 = 7, y2 = 22, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}


void LimparMsg(void){
	int x1 = 14, x2 = 88, y1 = 25, y2 = 28, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}


void LimparMenu(void){
	int x1 = 4, x2 = 35, y1 = 7, y2 = 22, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}


int validarCPF(char cpf[11]) {
    int i, soma = 0, peso = 10, digito;

    if(strlen(cpf) != 11)
        return 0;

    // Verificação do primeiro dígito
    for(i = 0; i < 9; i++) {
        if(cpf[i] >= '0' && cpf[i] <= '9') {
            soma += (cpf[i] - '0') * peso;
            peso--;
        }
    }

    digito = 11 - (soma % 11);
    if (digito > 9) digito = 0;
    if (digito != cpf[9] - '0')
        return 0;

    // Verificação do segundo dígito
    soma = 0;
    peso = 11;

    for(i = 0; i < 10; i++) {
        if(cpf[i] >= '0' && cpf[i] <= '9') {
            soma += (cpf[i] - '0') * peso;
            peso--;
        }
    }

    digito = 11 - (soma % 11);
    if (digito > 9) digito = 0;
    if (digito != cpf[10] - '0')
        return 0;

    // CPF é válido
    return 1;
}


int validarData(TpData data) {
    if (data.Ano < 2000 || data.Mes <= 0 || data.Mes > 12 || data.Dia <= 0)
        return 0;

    if (data.Mes % 2 == 0) {
        if (data.Dia > 30)
            return 0;
    } else {
        if (data.Dia > 31)
            return 0;
    }

    if (data.Ano % 4 == 0) {
        if (data.Dia > 29)
            return 0;
    } else {
        if (data.Dia > 28)
            return 0;
    }

    // A data é válida
    return 1;
}

void SelecaoDireta(FILE *Ptr) 
{
    TpFornecedores FM, FP;
    int p,f,pos;
	
	fseek(Ptr,0,2);

    gotoxy(90,10);
	f=ftell(Ptr)/sizeof(TpFornecedores);
	//printf("f : %d", f);
			
//	getch();
	
    while (f > 0) 
	{
    	
		gotoxy(15,26);
		printf("f : %d", f);			
		getch();
		
        pos =0;
        rewind(Ptr);
       	fread(&FM, sizeof(TpFornecedores), 1, Ptr) ;

        for(p=1;p<f;p++) 
		{
		    fseek(Ptr,p*sizeof(TpFornecedores),0);
		    fread(&FP, sizeof(TpFornecedores), 1, Ptr);
		    
		    if(FP.CodForn > FM.CodForn)
			{
				//printf("\n%d > %d",FP.CodForn,FM.CodForn);				
				FM = FP;
				pos = p; 
				//printf("\npos - %d",pos);
				getch();
			}
		 
		}
		if(pos<f)
		{
			fseek(Ptr,pos*sizeof(TpFornecedores),0);
			fwrite(&FP,sizeof(TpFornecedores),1,Ptr);
			
			fseek(Ptr,(f-1)*sizeof(TpFornecedores),0);
		    fwrite(&FM,sizeof(TpFornecedores),1,Ptr);
		}
		
		f--;
		    
    }
    fseek(Ptr,0,2);
}

void insercao(FILE *Ptr)
{
	TpFornecedores FA,FB;
	fseek(Ptr,0,2);
	int i= ftell(Ptr)/sizeof(TpFornecedores),pos,p;
	
	gotoxy(90, 9);
	printf("Ptro - %d",i);
	
	if(i > 1)
	{
		pos = (i-1)*sizeof(TpFornecedores);
		fseek(Ptr,pos,0);
		fread(&FA,sizeof(TpFornecedores),1,Ptr);
		
		pos = (i-2)*sizeof(TpFornecedores);
		fseek(Ptr,pos,0);
		fread(&FB,sizeof(TpFornecedores),1,Ptr);
		
		 
		while(i > 1 && FA.CodForn < FB.CodForn)
		{
		  	pos = (i-1)*sizeof(TpFornecedores);
			fseek(Ptr,pos,0);
			fwrite(&FB,sizeof(TpFornecedores),1,Ptr);
			
			pos = (i-2)*sizeof(TpFornecedores);
			fseek(Ptr,pos,0);
			fwrite(&FA,sizeof(TpFornecedores),1,Ptr);
		  	i--;
		  	
		  	
		  	
		  	if(i>1)
		  	{
		  		pos = (i-1)*sizeof(TpFornecedores);
				fseek(Ptr,pos,0);
				fread(&FA,sizeof(TpFornecedores),1,Ptr);
				
				pos = (i-2)*sizeof(TpFornecedores);
				fseek(Ptr,pos,0);
				fread(&FB,sizeof(TpFornecedores),1,Ptr);
		  	}
		}
		fseek(Ptr,0,2);
	}
}


// Ordenação BUBBLE SORT
void ordenarProdutos() {
    FILE *Ptr = fopen("produtos.dat", "rb+"); // Abre o arquivo "produtos.dat" para leitura e escrita em modo binário

    if (Ptr == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }

    TpProdutos produtoAtual, proximoProduto;

    // Obter o número total de produtos no arquivo
    fseek(Ptr, 0, SEEK_END);
    long numProdutos = ftell(Ptr) / sizeof(TpProdutos);
    rewind(Ptr);

    // Bubble sort para ordenar os produtos
    for (int i = 0; i < numProdutos - 1; i++) {
        for (int j = 0; j < numProdutos - i - 1; j++) {
            // Ler dois produtos consecutivos
            fseek(Ptr, j * sizeof(TpProdutos), SEEK_SET);
            fread(&produtoAtual, sizeof(TpProdutos), 1, Ptr);

            fseek(Ptr, (j + 1) * sizeof(TpProdutos), SEEK_SET);
            fread(&proximoProduto, sizeof(TpProdutos), 1, Ptr);

            // Comparar os códigos e trocar se necessário
            if (produtoAtual.CodProd > proximoProduto.CodProd) {
                fseek(Ptr, j * sizeof(TpProdutos), SEEK_SET);
                fwrite(&proximoProduto, sizeof(TpProdutos), 1, Ptr);

                fseek(Ptr, (j + 1) * sizeof(TpProdutos), SEEK_SET);
                fwrite(&produtoAtual, sizeof(TpProdutos), 1, Ptr);
            }
        }
    }

    fclose(Ptr);
}


// - PESSOA PELO CPF
// BUSCA EXAUSTIVA
int BuscaCPF(FILE *PtrClientes, char cpf[11]) {
    TpClientes R;

    rewind(PtrClientes); // Posiciona o Ponteiro no Início
    fread(&R, sizeof(TpClientes), 1, PtrClientes);

    while (!feof(PtrClientes) && (stricmp(cpf, R.CPF) != 0 || R.Status != 'A'))
        fread(&R, sizeof(TpClientes), 1, PtrClientes);

//    if (stricmp(cpf, R.CPF) == 0 && R.Status == 'A')
	if (!feof(PtrClientes))
        return ftell(PtrClientes) - sizeof(TpClientes);
    else
        return -1;
}


// BUSCA SEQUENCIAL INDEXADA
int BuscaCod(int codForn) {
    FILE *PtrForn = fopen("fornecedores.dat", "rb+");
    TpFornecedores C;
    
    rewind(PtrForn);

    fread(&C, sizeof(TpFornecedores), 1, PtrForn);

    while (!feof(PtrForn) && (codForn != C.CodForn || C.Status != 'A')) {
        fread(&C, sizeof(TpFornecedores), 1, PtrForn);
    }

    if (codForn == C.CodForn && C.Status == 'A') {
        return ftell(PtrForn) - sizeof(TpFornecedores);
    } else {
        return -1;
    }
}


// BUSCA BINARIA
int BuscaCodProd(FILE *Ptr, int codprod)
{
	ordenarProdutos();
	TpProdutos R;
	
	fseek(Ptr,0,2);
	int inicio=0, fim, meio;
	
	fim = ftell(Ptr)/sizeof(TpProdutos);
	fim = fim - 1;
	meio = fim / 2;

	
	fseek(Ptr,meio*sizeof(TpProdutos),0);
	fread(&R,sizeof(TpProdutos),1,Ptr);
	
	while(inicio < fim && (R.CodProd != codprod || R.Status != 'A'))
	{
		if(R.CodProd > codprod)
			fim = meio - 1;
		else
			inicio = meio + 1;
			
		meio = (inicio + fim)/2;
		
		fseek(Ptr,meio*sizeof(TpProdutos),0);
		fread(&R,sizeof(TpProdutos),1,Ptr);
	}


	if(R.CodProd == codprod && R.Status != 'I')
//		return m*sizeof(TpProdutos);
		return meio;
	else
		return -1;
	
}


// BUSCA EXAUSTIVA COM SENTINELA
//int BuscaCodVenda(FILE *Ptr, char codvenda)
//{
//	int pos,TL;
//	TpVendas R;
//	
//	R.CodVenda = codvenda;
//	R.Status = 'A';
//	fseek(Ptr,0,2);
//	fwrite(&R,sizeof(TpVendas),1,Ptr);
//	
//	rewind(Ptr);  //Posiciona o Ponteiro no Início
//	fread(&R,sizeof(TpVendas),1,Ptr);
//	
//	while (codvenda != R.CodVenda)
//		fread(&R,sizeof(TpVendas),1,Ptr);
//		
//	if(!feof(Ptr) && R.Status == 'A')
//	 {
//		pos = ftell(Ptr)-sizeof(TpVendas);
//		
//		fseek(Ptr,0,2);
//		TL = ftell(Ptr)-sizeof(TpVendas); 
//		
//		if(pos == TL)
//			return -1;
//		else
//		{
//			fread(&R,TL*sizeof(TpVendas),1,Ptr);
//			R.Status = 'I';
//			fwrite(&R,sizeof(TpVendas),1,Ptr);
//			
//			return pos; 
//		}
//		
//		
//	}
//	else
//	{
//		fseek(Ptr,0,2);
//		TL = ftell(Ptr)-sizeof(TpVendas); 
//		fread(&R,TL*sizeof(TpVendas),1,Ptr);
//		R.Status = 'I';
//		fwrite(&R,sizeof(TpVendas),1,Ptr);
//		
//		return -1;
//	}
//};

int BuscaCodVenda(FILE *Ptr, char codvenda)
{
	TpVendas TA,TB;
	
	fseek(Ptr,0,2);
	int i,f = ftell(Ptr)/sizeof(TpVendas);
	
	
	TA.CodVenda = codvenda;
	TA.Status = 'A';
	fseek(Ptr,f*sizeof(TpVendas),0);
	fwrite(&TA,sizeof(TpVendas),1,Ptr);
	
	fseek(Ptr,0,0);
	fread(&TA,sizeof(TpVendas),1,Ptr);
	while((TA.CodVenda != codvenda || TA.Status != 'A'))		
		 fread(&TA,sizeof(TpVendas),1,Ptr);
	
 	i = ftell(Ptr) - sizeof(TpVendas);
 	
 	fseek(Ptr,0,2);
	f = ftell(Ptr) - sizeof(TpVendas);
	
	TB.Status = 'I';
	fseek(Ptr,f,0);
	fwrite(&TB,sizeof(TpVendas),1,Ptr);

	fseek(Ptr,i,0);
	fread(&TA,sizeof(TpVendas),1,Ptr);
		
	if(TA.Status == 'A')
		return i;
	else
 		return -1;	
}

int BuscaCodVenda2(FILE *Ptr, char codvenda)//função para não gerar conflito de posições caso não tenha feito a remoção física
{
	TpVendas R;
	rewind(Ptr);
	fread(&R,sizeof(TpVendas),1,Ptr);
	while(!feof(Ptr) && R.CodVenda!=codvenda)
		fread(&R,sizeof(TpVendas),1,Ptr);
	if(feof(Ptr) && R.Status=='I')
		return -1;
	else
		return ftell(Ptr)-sizeof(TpVendas);
}


void CadastroClientes(void) {
    FILE *PtrClientes = fopen("clientes.dat", "ab+");
    TpClientes Cliente;

    int pos;
    char op;
    LimparSaida();

    gotoxy(43, 7);
    printf("### CADASTRO DE PESSOAS ###\n");
    gotoxy(40, 9);
    printf("*CPF:");

    do {
        fflush(stdin);
        gets(Cliente.CPF);

        if (validarCPF(Cliente.CPF)) {
            pos = BuscaCPF(PtrClientes, Cliente.CPF);

            if (pos == -1) {
                Cliente.Status = 'A';
                Cliente.QtdeCompras = 0;
                Cliente.ValorTotComprado = 0;
                gotoxy(40, 10);
                printf("*Nome: ");
                fflush(stdin);
                fgets(Cliente.NomeCli, sizeof(Cliente.NomeCli), stdin);

                gotoxy(40, 11);
                fwrite(&Cliente, sizeof(TpClientes), 1, PtrClientes); // Salva o cliente no arquivo
            } else {
                LimparMsg();
                gotoxy(15, 26);
                printf("CLIENTE JA CADASTRADO !");
                Sleep(2000);
                LimparMsg();
                gotoxy(15, 23);
                printf("                        ");
                LimparMsg();
                gotoxy(15, 26);
                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
                op = toupper(getch());
            }
        } else {
            LimparMsg();
            gotoxy(15, 26);
            printf("CPF INVALIDO !");
            Sleep(2000);
            LimparMsg();
            gotoxy(15, 23);
            printf("                     ");
            gotoxy(15, 26);
            printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
            op = toupper(getch());
        }

        if (op != 27) {
            LimparSaida();
            gotoxy(39, 18);
            printf("                                    ");
            gotoxy(43, 8);
            gotoxy(43, 7);
            printf("### CADASTRO DE PESSOAS ###\n");
            gotoxy(40, 9);
            printf("*CPF:");
        }

    } while (op != 27); // Verifica a tecla ESC pressionada para sair

    fclose(PtrClientes);
    getch();
}


void ConsultaClientes(void)
{
	FILE *PtrCli = fopen("clientes.dat","rb");
	TpClientes Cliente;
	char CPF[11],op;
	int pos, linha = 8, coluna = 40;
	
		if(PtrCli==NULL)
		{
			LimparMsg();
            gotoxy(15, 26);
			printf("Erro de abertura :/  Pressione qualquer tecla para sair");
			op=toupper(getche());
		}
		else
		{
			//if(ordenado == 1)
			//{busca diferenciada}else{busca exaustiva}
			do
			{
				LimparSaida();
				gotoxy(43,7);
				printf("### CONSULTA DE CLIENTES ###\n");
				gotoxy(coluna,linha);
				printf("Informe o CPF: ");
				fflush(stdin);
				gets(CPF);
				pos = BuscaCPF(PtrCli,CPF);

				if(pos !=-1)
				{
					LimparSaida();
					fseek(PtrCli,pos,0);
					fread(&Cliente,sizeof(TpClientes),1,PtrCli);
					gotoxy(43,7);
					printf("### CONSULTA DE CLIENTES ###\n");
					gotoxy(coluna,linha+1);
					printf("Nome: %s",Cliente.NomeCli);
					gotoxy(coluna,linha+2);
					printf("CPF: %s",Cliente.CPF);
					gotoxy(coluna,linha+3);
					printf("Total Comprado: R$%.2f",Cliente.ValorTotComprado);
					gotoxy(coluna,linha+4);
					printf("Total de compras: %d",Cliente.QtdeCompras);
					LimparMsg();
					gotoxy(15,26);
					printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
				}
				else
				{
					LimparSaida();
					LimparMsg();
            		gotoxy(15, 26);
					printf("Cliente nao existente :/ [ENTER] - CONTINUAR & [ESQ] - SAIR");
				}
				
			op = toupper(getch());
			}while(op != 27);
			fclose(PtrCli);
		}
}

int BuscarProdVenda(FILE *PtrProd, int CodVenda, int CodProd)
{
	TpVendasProd Prod;
	TpVendas Venda;
	
	rewind(PtrProd);
		
	while(!feof(PtrProd) && (Prod.CodVenda != CodVenda || Prod.CodProd != CodProd))
	{
		fread(&Prod,sizeof(Prod),1,PtrProd);	
	}
	if(!feof(PtrProd))
		return ftell(PtrProd)-sizeof(Prod);
	else
		return -1;
}


void ConsultaFornecedores(void)
{
	int pos, linha=7, coluna=40, codAux;
	char op;
	TpFornecedores Fornecedor;
	FILE *PtrForn = fopen("fornecedores.dat","rb");
	
		if(PtrForn == NULL)
		{
			LimparMsg();
			gotoxy(15,26);
			printf("Erro de abertura :/ Presione qualquer tecla para sair");
			op=toupper(getche());
		}
		else
		{
			do
			{
				LimparSaida();
				gotoxy(43,7);
				printf("### CONSULTA DE FORNECEDORES ###\n");
				gotoxy(coluna,linha+2);
				printf("Informe o codigo do fornecedor: ");
				scanf("%d",&codAux);
				pos=BuscaCod(codAux);
				if(pos != -1)
				{
					LimparSaida();
					fseek(PtrForn,pos,0);
					fread(&Fornecedor,sizeof(TpFornecedores),1,PtrForn);
					gotoxy(43,7);
					printf("### CONSULTA DE FORNECEDORES ###\n");
					gotoxy(coluna,linha+2);
					printf("Codigo: %d",Fornecedor.CodForn);
					gotoxy(coluna,linha+3);
					printf("Nome: %s",Fornecedor.NomeForn);
					gotoxy(coluna,linha+4);
					printf("Cidade: %s",Fornecedor.CidadeForn);
					LimparMsg();
					gotoxy(15,26);
					printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
				}
				else
				{
					LimparMsg();
					gotoxy(15,26);
					printf("Fornecedor nao existente :/");
					gotoxy(15,27);
					printf("[ESC] Presione ESC para sair ou qualquer tecla para continuar");
				}
				
				op=toupper(getche());
				
			}while(op != 27);
			fclose(PtrForn);
		}		
}

void ConsultaProdutos(void)
{
    FILE *PtrProd = fopen("produtos.dat", "rb");
    TpProdutos Produto;
    char op;
    int pos, linha = 8, coluna = 40, codAux;

    if (PtrProd == NULL)
    {
    	LimparMsg();
        gotoxy(15, 26);
        printf("Erro de abertura :/ Pressione qualquer tecla para sair");
        op = toupper(getche());
    }
    else
    {
        do
        {
            LimparSaida();
            gotoxy(43, 7);
            printf("### CONSULTA DE PRODUTOS ###\n");
            gotoxy(coluna, linha);
            printf("Informe o codigo do produto: ");
            scanf("%d", &codAux); // Correção aqui

            pos = BuscaCodProd(PtrProd, codAux);
            if (pos != -1)
            {
                LimparSaida();
                fseek(PtrProd, pos * sizeof(TpProdutos), 0);
                fread(&Produto, sizeof(TpProdutos), 1, PtrProd);
                gotoxy(43, 7);
                printf("### CONSULTA DE PRODUTOS ###\n");
                gotoxy(coluna, linha + 1);
                printf("Codigo do Fornecedor: %d", Produto.CodForn);
                gotoxy(coluna, linha + 2);
                printf("Codigo do Produto: %d", Produto.CodProd);
                gotoxy(coluna, linha + 3);
                printf("Descricao: %s", Produto.Descr);
                gotoxy(coluna, linha + 4);
                printf("Estoque: %d", Produto.Estoque);
                gotoxy(coluna, linha + 5);
                printf("Preco: %.2f", Produto.Preco);
                gotoxy(15, 26);
                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
            }
            else
            {
                LimparSaida();
                LimparMsg();
                gotoxy(15, 26);
                printf("Produto nao existente :/ [ENTER] - CONTINUAR & [ESQ] - SAIR");
            }

            op = toupper(getch());
        } while (op != 27);
        fclose(PtrProd);
    }
}
void ExcluiFisVendaProdutos()
{
	FILE *ptr = fopen("vendaprod.dat","rb");
	FILE *temp = fopen("temp.dat","wb");
	TpVendasProd VendaProd;
	
	fread(&VendaProd,sizeof(TpVendasProd),1,ptr);
	
	if(ptr ==  NULL|| temp == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("Erro de abertura");
	}
	else
	{
		while(!feof(ptr))
		{
			if(VendaProd.Status != 'I')
			{
				fwrite(&VendaProd,sizeof(TpVendasProd),1,temp);
			}
			
			fread(&VendaProd,sizeof(TpVendasProd),1,ptr);	
		}
		fclose(ptr);
		fclose(temp);
		remove("vendaprod.dat");
		rename("temp.dat","vendaprod.dat");
		
//		LimparMsg();
//		gotoxy(15,26);
//		printf("Exclusao fisica feita com sucesso!");
//		getch();
	}
}

void ExcluiFisProdutos()
{
	FILE *Ptr = fopen("produtos.dat","rb");
	FILE *PtrNew = fopen("temp.dat","ab");
	
	if(Ptr == NULL || PtrNew == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("Erro de abertura");
	}
	else
	{
		TpProdutos Produtos;
		fread(&Produtos,sizeof(TpProdutos),1,Ptr);
		
		while(!feof(Ptr))
		{
			if(Produtos.Status != 'I')
			{
				fwrite(&Produtos,sizeof(TpProdutos),1,PtrNew);
			}
			fread(&Produtos,sizeof(TpProdutos),1,Ptr);
		}
		fclose(Ptr);
		fclose(PtrNew);	
		remove("produtos.dat");
		rename("temp.dat","produtos.dat");
		
		LimparMsg();
		gotoxy(15,26);
		printf("Exclusao fisica feita com sucesso!");
		getch();
	}
}

void ExcluiFisVendas()
{
	FILE *Ptr = fopen("vendas.dat","rb");
	FILE *PtrNew = fopen("temp.dat","wb");
	
	if(Ptr == NULL || PtrNew == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("Erro de abertura");
	}
	else
	{
		TpVendas Venda;
		fread(&Venda,sizeof(TpVendas),1,Ptr);
		
		while(!feof(Ptr))
		{
			if(Venda.Status == 'A')
			{
				fwrite(&Venda,sizeof(TpVendas),1,PtrNew);
			}
			fread(&Venda,sizeof(TpVendas),1,Ptr);
		}
		fclose(Ptr);
		fclose(PtrNew);	
		remove("vendas.dat");
		rename("temp.dat","vendas.dat");
		
		LimparMsg();
		gotoxy(15,26);
		printf("Exclusao fisica feita com sucesso!");
		getch();
	}
}

void ExcluiFisClientes()
{
	FILE *PtrClientes = fopen("clientes.dat","rb");
	FILE *PtrNew = fopen("temp.dat","wb");
	
	if(PtrClientes == NULL || PtrNew == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("Erro de abertura");
	}
	else
	{
		TpClientes Cliente;
		fread(&Cliente,sizeof(TpClientes),1,PtrClientes);
		
		while(!feof(PtrClientes))
		{
			if(Cliente.Status == 'A')
			{
				fwrite(&Cliente,sizeof(TpClientes),1,PtrNew);
			}
			fread(&Cliente,sizeof(TpClientes),1,PtrClientes);
		}
		fclose(PtrClientes);
		fclose(PtrNew);	
		remove("clientes.dat");
		rename("temp.dat","clientes.dat");
		
		LimparMsg();
		gotoxy(15,26);
		printf("Exclusao fisica feita com sucesso!");
		getch();
	}
}

void ExcluiFisFornecedores()
{
	FILE *PtrForn = fopen("fornecedores.dat","rb");
	FILE *PtrNew = fopen("temp.dat","wb");
	
	if(PtrForn == NULL || PtrNew == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("Erro de abertura");
	}
	else
	{
		TpFornecedores Forne;
		fread(&Forne,sizeof(TpFornecedores),1,PtrForn);
		
		while(!feof(PtrForn))
		{
			if(Forne.Status == 'A')
			{
				fwrite(&Forne,sizeof(TpFornecedores),1,PtrNew);
			}
			fread(&Forne,sizeof(TpFornecedores),1,PtrForn);
		}
		fclose(PtrForn);
		fclose(PtrNew);	
		remove("fornecedores.dat");
		rename("temp.dat","fornecedores.dat");
		
		LimparMsg();
		gotoxy(15,26);
		printf("Exclusao fisica feita com sucesso!");
		getch();
	}
}

void ExcluirProdutosVendaLog(int CodVenda)
{
    FILE *PtrProdutos = fopen("produtos.dat", "rb+");
    FILE *PtrVendaProd = fopen("vendaprod.dat", "rb+");
    TpProdutos Prod;
    TpVendasProd VendaProd;
    int posProd;

    if (PtrProdutos == NULL || PtrVendaProd == NULL)
    {
        gotoxy(15, 26);
        printf("Erro de abertura");
    }
    else
    {
        fread(&VendaProd, sizeof(TpVendasProd), 1, PtrVendaProd);
        while (!feof(PtrVendaProd))
        {
            if (VendaProd.CodVenda == CodVenda)
            {
                VendaProd.Status = 'I';
                posProd = BuscaCodProd(PtrProdutos, VendaProd.CodProd);
                posProd*=sizeof(TpProdutos);
                fseek(PtrProdutos, posProd, SEEK_SET);
                fread(&Prod, sizeof(TpProdutos), 1, PtrProdutos);
                Prod.Estoque += VendaProd.Qtde;
                fseek(PtrProdutos, posProd, SEEK_SET);
                fwrite(&Prod, sizeof(TpProdutos), 1, PtrProdutos);
            }
            fread(&VendaProd, sizeof(TpVendasProd), 1, PtrVendaProd);
        }
        fclose(PtrProdutos);
        fclose(PtrVendaProd);
        ExcluiFisVendaProdutos();
    }
}


void ExcluirVendasLogicamente(char CPF[11])//Mexi nessa parte - M 
{
	FILE *Ptr = fopen("vendas.dat","rb+");
	FILE *PtrCli = fopen("clientes.dat","rb+");
	TpVendas Venda;
	TpClientes Cliente;
	int posCli, posVendaProd;
	
	if(Ptr == NULL)
	{
		gotoxy(15,26);
		printf("Erro de abertura");
	}
	else
	{
		fread(&Venda,sizeof(TpVendas),1,Ptr);
		while(!feof(Ptr))
		{
			if(strcmp(Venda.ClienteCPF,CPF) == 0)
			{
				Venda.Status = 'I';
				
				posCli = BuscaCPF(PtrCli, Venda.ClienteCPF);
				fseek(PtrCli,posCli,SEEK_SET);
				fread(&Cliente,sizeof(TpClientes),1,PtrCli);
				Cliente.QtdeCompras-=1;
				Cliente.ValorTotComprado-=Venda.TotVenda;
				fseek(PtrCli,posCli,SEEK_SET);
				fwrite(&Cliente,sizeof(TpClientes),1,PtrCli);
				ExcluirProdutosVendaLog(Venda.CodVenda);
				
			}
			fread(&Venda,sizeof(TpVendas),1,Ptr);
		}
		fclose(Ptr);
		fclose(PtrCli);
	}
}

void ExcluiVendas() //essa vai para o menu
{
	int pos = 0, pos2;
	char op;
	TpVendas R;
	TpClientes C;
	
	FILE *Ptr = fopen("vendas.dat","rb+");
	FILE *PtrCli = fopen("clientes.dat","rb+");
	int aux;
	if (Ptr == NULL || PtrCli == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("\nErro de Abertura!\n");
	}
	else
	{
		do
		{
			LimparSaida();
			gotoxy(43,7);
			printf("### EXCLUSAO LOGICA DE VENDAS ###\n");
			gotoxy(40,9);
			printf("Codigo:"); 
			scanf("%d",&aux);
				
			if (aux > 0)
			{
			pos = BuscaCodVenda2(Ptr,aux);
				if(pos == -1)
					{
						LimparMsg();
						gotoxy(15,26);
						printf("Venda nao cadastrada!");
						Sleep(1500);
						LimparMsg();
		                gotoxy(15, 26);
		                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		                op = toupper(getch());
					}
				else
					{
						fseek(Ptr,pos,0); // Deslocando pos bytes a partir do início
						fread(&R,sizeof(TpVendas),1,Ptr);
						
						gotoxy(40,11);
						printf("Codigo: %d", R.CodVenda);
						gotoxy(40,12);
						printf("Cliente: %s",R.ClienteCPF);
						gotoxy(40, 13);
						printf("Data: %d/%d/%d", R.DataVenda.Dia,R.DataVenda.Mes,R.DataVenda.Ano);
						gotoxy(40, 14);
						printf("Total: R$ %.2f", R.TotVenda);
						gotoxy(40, 16);
						LimparMsg();
                		gotoxy(15, 26);
                		printf("Confirmar a exclusao (S/N)?");
						fflush(stdin);
						
						if (toupper(getche()) == 'S') {
	                    	
							ExcluirProdutosVendaLog(R.CodVenda);
							R.Status = 'I';
							fseek(Ptr,pos,0);
							fwrite(&R,sizeof(TpVendas),1,Ptr);		    
				
							pos2=BuscaCPF(PtrCli,R.ClienteCPF);
							if(pos2 == -1)
							{
								LimparMsg();
			                    gotoxy(15, 26);
			                    printf("Cliente nao encontrado!");
			                    Sleep(1500);
			                    
			                    LimparMsg();
				                gotoxy(15, 26);
				                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
				                op = toupper(getch());
							}
							else
							{
			                    
								fseek(PtrCli,pos2*sizeof(TpClientes),SEEK_SET);
								fread(&C,sizeof(TpClientes),1,PtrCli);
								
								C.ValorTotComprado -= R.TotVenda;
								C.QtdeCompras--;
								
								fseek(PtrCli,pos2*sizeof(TpClientes),SEEK_SET);
								fwrite(&C,sizeof(TpClientes),1,PtrCli);
	
								                    
			                    LimparMsg();
			                    gotoxy(15, 26);
			                    printf("Exclusao concluida!");
			                    Sleep(1500);
			                    
			                    LimparMsg();
				                gotoxy(15, 26);
				                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
				                op = toupper(getch());
							}
							
	                	}
						else
						{
							LimparMsg();
			                gotoxy(15, 26);
			                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
			                op = toupper(getch());
						}	
					}
				}
				else
				{
					gotoxy(15,26);
					printf("Codigo Invalido!");
					Sleep(1500);
					LimparMsg();
	                gotoxy(15, 26);
	                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
	                op = toupper(getch());
				}
			}while(op!=27);
			fclose(Ptr);
			fclose(PtrCli);
	}
}

void ExcluiLogClientes() {
    FILE *PtrClientes = fopen("clientes.dat", "rb+"); // Abre o arquivo de clientes para leitura e escrita binária
	TpClientes R; 
    int pos = 0; 
    char  op;


    if (PtrClientes == NULL) { 
        LimparMsg();
        gotoxy(15, 26);
		printf("Erro ao abrir o arquivo de clientes.");
    }
    else
    {
    	do {
	        LimparSaida(); // Limpa a tela
	        gotoxy(43, 7);
	        printf("### EXCLUSAO LOGICA DE CLIENTES ###\n");
	        gotoxy(40, 9);
	        printf("CPF (APENAS NUMEROS):");
	        fflush(stdin);
	        gets(R.CPF); // Solicita e lê o CPF do cliente
	
	        if (strlen(R.CPF) > 0) {
	            
	            pos = BuscaCPF(PtrClientes, R.CPF); // Encontra a posição do CPF no arquivo
	
	            if (pos == -1) { // Verifica se o cliente não está cadastrado
	                LimparMsg();
	                gotoxy(15, 26);
	                printf("Cliente nao cadastrado! Pos = %d",pos);
	                Sleep(1500);
	                LimparMsg();
	            } else {
	                fseek(PtrClientes, pos, 0);
					fread(&R, sizeof(TpClientes), 1, PtrClientes);
	
	                // Mostra os detalhes do cliente na tela
	                LimparSaida();
	                gotoxy(40, 7);
	                printf("Detalhes do cliente:");
	                gotoxy(40, 8);
	                printf("CPF: %s", R.CPF);
	                gotoxy(40, 9);
	                printf("Nome: %s", R.NomeCli);
	
	                // Confirma a exclusão do cliente
	                LimparMsg();
	                gotoxy(15, 26);
	                printf("Confirma a exclusao (S/N)?");
	
	                gotoxy(42, 26);
	                if (toupper(getche()) == 'S') {
	                    
						R.Status = 'I';
						fseek(PtrClientes,pos,0);
						fwrite(&R,sizeof(TpClientes),1,PtrClientes);
						ExcluirVendasLogicamente(R.CPF);
	                    
	                    LimparMsg();
	                    gotoxy(15, 26);
	                    printf("Exclusao concluida!");
	                    Sleep(1500);
	                    LimparMsg();
		                gotoxy(15, 26);
		                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		                op = toupper(getch());
	                }
	            }
	        } else {
	            LimparMsg();
	            gotoxy(15, 26);
	            printf("CPF invalido!");
	            Sleep(1500);
	            LimparMsg();
                gotoxy(15, 26);
                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
                op = toupper(getch());
	        }
			LimparMsg();
	        LimparSaida();
	        gotoxy(15, 26);
	        printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
	        Sleep(1500);
	        op = toupper(getch());
	    } while (op != 27);
    }

    fclose(PtrClientes); 
}

void ExcluirVendasProdForn(int codProd)//função para excluir produtos das vendas, dos produtos e descontar dos clientes
{
	FILE *ptrVendaProd = fopen("vendaprod.dat","rb+");
	FILE *ptrCli = fopen("clientes.dat","rb+");
	FILE *ptrVenda = fopen("vendas.dat","rb+");
	TpVendasProd VendaProd;
	TpVendas Venda;
	TpClientes Cliente;
	int pos, posAux, posCli, posVenda;
	float auxConta;
	
	if(ptrVendaProd == NULL || ptrCli == NULL || ptrVenda == NULL)
	{
		gotoxy(15,26);
		printf("Erro de abertura.");
		Sleep(1500);
	}
	else
	{
		fread(&VendaProd,sizeof(TpVendasProd),1,ptrVendaProd);
		while(!feof(ptrVendaProd))
		{
			if(VendaProd.CodProd == codProd && VendaProd.Status == 'A')
			{
				
				posVenda=BuscaCodVenda(ptrVenda,VendaProd.CodVenda);//descontar valor do cliente
				posVenda=posVenda*sizeof(TpVendasProd);
				fseek(ptrVenda,posVenda,SEEK_SET);//achar o CPF e descontar valor
				fread(&Venda,sizeof(TpVendas),1,ptrVenda);
				auxConta=VendaProd.Qtde*VendaProd.ValorUnitario;
				Venda.TotVenda-=auxConta;
				fseek(ptrVenda,posVenda,SEEK_SET);
				fwrite(&Venda,sizeof(TpVendas),1,ptrVenda);
				
				posCli=BuscaCPF(ptrCli,Venda.ClienteCPF);//Usar aqui
				fseek(ptrCli,posCli,SEEK_SET);
				fread(&Cliente,sizeof(TpClientes),1,ptrCli);
				Cliente.ValorTotComprado-=auxConta;
				fseek(ptrCli,posCli,SEEK_SET);
				fwrite(&Cliente,sizeof(TpClientes),1,ptrCli);
				
				VendaProd.Status = 'I';
				pos=BuscarProdVenda(ptrVendaProd, VendaProd.CodVenda, codProd);
				fseek(ptrVendaProd,pos,SEEK_SET);
				fwrite(&VendaProd,sizeof(TpVendasProd),1,ptrVendaProd);//inativar produto na venda
			}
			fread(&VendaProd,sizeof(TpVendasProd),1,ptrVendaProd);
		}
		fclose(ptrVendaProd);
		fclose(ptrCli);
		fclose(ptrVenda);
	}
	ExcluiFisVendaProdutos();
}
void ExcluiLogProdFornecedores(int codForn)
{
	FILE *PtrProdutos = fopen("produtos.dat", "rb+");
    TpProdutos Prod;
    int posProd,aux;

    if (PtrProdutos == NULL)
    {
        gotoxy(15, 26);
        printf("Erro de abertura");
    }
    else
    {
        fread(&Prod, sizeof(TpProdutos), 1, PtrProdutos);
        while (!feof(PtrProdutos))
        {
            if (Prod.CodForn == codForn && Prod.Status == 'A')
            {
            	ExcluirVendasProdForn(Prod.CodProd);
                Prod.Status = 'I';
                posProd = BuscaCodProd(PtrProdutos, Prod.CodProd);
                posProd=posProd*sizeof(TpProdutos);
                fseek(PtrProdutos, posProd, SEEK_SET);
                fwrite(&Prod, sizeof(TpProdutos), 1, PtrProdutos);
            }
            fread(&Prod, sizeof(TpProdutos), 1, PtrProdutos);
        }
        fclose(PtrProdutos); 
   }
}

void ExcluiLogFornecedores()
{
	int pos = 0, pos2;
	char op,resp;
	TpFornecedores R;
	FILE *PtrFunc = fopen("fornecedores.dat","rb+");
	
	if (PtrFunc == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("\nErro de Abertura!\n");
	}
	else
		{
			do
			{
				LimparSaida();
				gotoxy(43,7);
				printf("### EXCLUSAO LOGICA DE FORNECEDORES ###\n");
				gotoxy(40,9);
				printf("Codigo:"); 
				scanf("%d", &R.CodForn);
				
				if (R.CodForn > 0)
				{
					pos = BuscaCod(R.CodForn);
					if(pos == -1)
					{
						LimparMsg();
						gotoxy(15,26);
						printf("Fornecedor nao cadastrado!");
						Sleep(1500);
						LimparMsg();
		                gotoxy(15, 26);
		                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		                op = toupper(getch());
					}else{
						
						fseek(PtrFunc, pos,0); // Deslocando pos bytes a partir do início
						fread(&R,sizeof(TpFornecedores),1,PtrFunc);
						gotoxy(40,11);
						printf("Codigo: ");
						printf("%d", R.CodForn);
						gotoxy(40,12);
						printf("Nome: ");
						printf("%s",R.NomeForn);
						gotoxy(40, 13);
						printf("Cidade: "); 
						printf("%s", R.CidadeForn);
						gotoxy(43, 15);
						LimparMsg();
                		gotoxy(15, 26);
                		printf("Confirma a exclusao (S/N)?");
                		fflush(stdin);
						
						if (toupper(getch()) =='S') {
							
					
	                    	TpProdutos Prod;
	                    	FILE *ptrProd = fopen("produtos.dat","rb+");
	                    	if(ptrProd ==  NULL)
	                    	{
	                    		gotoxy(15,26);
	                    		printf("Erro de abertura :/");
	                    		Sleep(2000);
							}
							else
							{			

								ExcluiLogProdFornecedores(R.CodForn);
								R.Status = 'I';
								fseek(PtrFunc,pos,0);
								fwrite(&R,sizeof(TpFornecedores),1,PtrFunc);
				 
				                LimparMsg();
				                gotoxy(15, 26);
				                printf("Exclusao concluida!");
				                Sleep(1500);
				                LimparMsg();
					            gotoxy(15, 26);
					            printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
					            op = toupper(getch());
					            fclose(ptrProd);
							}
	                	}
					}
				}
				else
				{
					gotoxy(15,26);
					printf("Codigo Invalido!");
					Sleep(1500);
					LimparMsg();
	                gotoxy(15, 26);
	                printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
	                op = toupper(getch());
				}
			}while(op!=27);
			fclose(PtrFunc);
		}
}

void ExcluiLogProdutos()
{
	int pos = 0,pos2,aux;
	char op;
	
	TpProdutos R;
	FILE *Ptr = fopen("produtos.dat","rb+");
	
	if (Ptr == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("\nErro de Abertura!\n");
	}
		
	else
	{
		do
		{
			LimparSaida();
			gotoxy(43,7);
			printf("### EXCLUSAO LOGICA DE PRODUTOS ###\n");
			gotoxy(40,9);
			printf("Codigo:"); 
			scanf("%d", &R.CodProd);
			
			if (R.CodProd > 0)
			{
				pos = BuscaCodProd(Ptr,R.CodProd);
				if(pos == -1)
				{
					LimparMsg();
					gotoxy(15,26);
					printf("Produto nao cadastrado!");
					Sleep(1500);
					LimparMsg();
					printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
        			Sleep(1500);
        			getch();
				}else{
					
					fseek(Ptr, pos*sizeof(TpProdutos),0); 
					fread(&R,sizeof(TpProdutos),1,Ptr);
					gotoxy(40,11);
					printf("Codigo: ");
					printf("%d", R.CodProd);
					gotoxy(40,12);
					printf("Codigo do Fornecedor: ");
					printf("%d",R.CodForn);
					gotoxy(40, 13);
					printf("Descricao: "); 
					printf("%s", R.Descr);
					gotoxy(40, 14);
					printf("Data de Validade: "); 
					printf("%d/%d/%d", R.DtValidade.Dia, R.DtValidade.Mes, R.DtValidade.Ano);
					gotoxy(40, 15);
					printf("Estoque: "); 
					printf("%d", R.Estoque);
					gotoxy(40, 16);
					printf("Preco: "); 
					printf("%.2f", R.Preco);
					
					LimparMsg();
					gotoxy(15, 26);
					printf("Confirma a exclusao (S/N)?");
					fflush(stdin);
			
					if (toupper(getche()) == 'S') {
	                    
							R.Status = 'I';
							fseek(Ptr, pos*sizeof(TpProdutos),0); 
							fwrite(&R,sizeof(TpProdutos),1,Ptr);
		
		                    
		                    LimparMsg();
		                    gotoxy(15, 26);
		                    printf("Exclusao concluida! [ENTER] - CONTINUAR & [ESQ] - SAIR");
		                    op = toupper(getch());
		                    LimparMsg();               
	                	}
	                LimparMsg();
			        gotoxy(15, 26);
			        printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
			        op = toupper(getch());
			        LimparMsg();   
				}
			}
			else
			{
				gotoxy(15,26);
				printf("Codigo Invalido! [ENTER] - CONTINUAR & [ESQ] - SAIR");
				op = toupper(getch());
				LimparMsg();
			}
		}while(op!=27);
		fclose(Ptr);
	}	
}

//void ExcluiVendas(TpVendas Venda[], TpVendasProd VendaProd[], TpFornecedores Fornecedor[], TpProdutos Produto[], int &TLV, int &TLVP,int TLF, int TLP)
//{
//	int codAux, posVenda, op, linha=7, coluna=40, linhaMaxima = 19, posForn, posProd;
//	double totalItem;
//	do
//	{
//		if(TLV > 0)
//		{
//			LimparSaida();
//			gotoxy(43,7);
//			printf("### EXCLUSAO DE VENDAS ###\n");
//			gotoxy(40,9);
//			printf("Codigo:"); 
//			scanf("%d", &codAux);
//		
//			if(codAux >= 0)
//			{
//				posVenda = BuscaCodVenda(codAux, Venda, TLV);
//				if(posVenda == -1)
//				{
//					LimparMsg();
//					gotoxy(15,26);
//					printf("Venda nao cadastrado!");
//					Sleep(1500);
//					LimparMsg();
//				}
//			
//				else
//				{
//					LimparSaida();
//					gotoxy(coluna,linha);
//					linha+=2;
//					printf("Detalhes da Venda:");
//					gotoxy(coluna,linha);
//					printf("Codigo: %d", Venda[posVenda].CodVenda);
//					gotoxy(60,linha);
//					printf("CPF: %s",Venda[posVenda].ClienteCPF);
//					linha+=1;
//					gotoxy(coluna,linha);
//					linha+=2;
//					printf("Data: %d/%d/%d", Venda[posVenda].DataVenda.Dia, Venda[posVenda].DataVenda.Mes, Venda[posVenda].DataVenda.Ano);
//					gotoxy(coluna,linha);
//					printf("Produtos:");
//					for (int j = 0; j < TLVP; j++)
//	            {
//	            	if (linha >= linhaMaxima)
//		            {
//		                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
//		                LimparMsg();
//		                gotoxy(15, 26);
//		                printf("Pressione qualquer tecla para continuar...");
//		                Sleep(1500);
//		                getch();
//		                LimparSaida();
//		                LimparMsg();
//		                linha = 7;
//		            }
//	                if (VendaProd[j].CodVenda == codAux)
//	                {
//	                    linha += 1;
//	                    gotoxy(coluna, linha);
//	                    printf("%d", VendaProd[j].CodProd);
//	
//	                    posProd = BuscaCodProd(VendaProd[j].CodProd, Produto, TLP);
//	
//	                    coluna += 10;
//	                    gotoxy(coluna, linha);
//	                    printf("%s", Produto[posProd].Descr);
//	
//	                    coluna += 9;
//	                    gotoxy(coluna, linha);
//	                    printf("%d", VendaProd[j].Qtde);
//	
//	                    totalItem = VendaProd[j].Qtde * Produto[posProd].Preco;
//	                    coluna += 6;
//	                    gotoxy(coluna, linha);
//	                    printf("R$%.2f", totalItem);
//	
//	                    coluna += 10;
//	                    posForn = BuscaCod(Produto[posProd].CodForn, Fornecedor, TLF);
//	                    if (posForn != -1)
//	                    {
//	                        gotoxy(coluna, linha);
//	                        printf("%s", Fornecedor[posForn].NomeForn);
//	                    }
//	                    else
//	                    {
//	                        gotoxy(coluna, linha);
//	                        printf("Fornecedor nao encontrado");
//	                    }
//	
//	                    linha += 1; // Incrementa linha para o próximo produto
//	                    coluna = 40; // Reinicializa coluna para o próximo produto
//	                }
//	            }
//            
//					gotoxy(coluna,linha);
//					linha+=1;
//					printf("Total: R$%.2f", Venda[posVenda].TotVenda);
//					linha+=1;
//					gotoxy(coluna,linha);
//					printf("Confirma a exclusao (S/N)? ");
//	
//					if(toupper(getche()) == 'S'){
//						for(int i=0;i<TLVP;i++)
//						{
//							if(VendaProd[i].CodVenda ==  Venda[posVenda].CodVenda)
//							{
//								posProd=BuscaCodProd(VendaProd[i].CodProd, Produto, TLP);
//								Produto[posProd].Estoque += VendaProd[i].Qtde;
//							}
//						}
//						for(int i=0; i<TLVP;i++)
//						{
//							if(VendaProd[i].CodVenda ==  Venda[posVenda].CodVenda)
//							{
//								VendaProd[i] = VendaProd[i+1];
//								TLVP--;
//							}
//						}
//						
//						for( ; posVenda < TLV - 1; posVenda++)
//							Venda[posVenda] = Venda[posVenda + 1];
//						
//						
//						TLV--;
//						
//						LimparMsg();
//						gotoxy(15,26);
//						printf("Exclusao concluida!");
//						Sleep(1500);
//						LimparMsg();
//					}
//					else
//					{
//						linha=7;
//						coluna=40;
//					}
//				}
//			}else{
//				LimparMsg();
//				gotoxy(15,26);
//				printf("Codigo invalido!");
//				Sleep(1500);
//				LimparMsg();
//			}
//		}else{
//			LimparMsg();
//			gotoxy(15,26);
//			printf("Nao ha vendas cadastradas!");
//			Sleep(1500);
//			LimparMsg();
//		}
//		
//		
//		
//		LimparSaida();
//		gotoxy(15,26);
//		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
//		Sleep(1500);
//		op = toupper(getch());	
//	}while(op != 27);
//}


int RetornarCodigoVenda(FILE *Ptr)
{
	TpVendas Aux;
	fseek(Ptr,-1*sizeof(TpVendas),2);
	fread(&Aux,sizeof(TpVendas),1,Ptr);
	fseek(Ptr,0,2);
	
	return Aux.CodVenda + 1;
}

void CupomFiscal(FILE *ptrCli, FILE *ptrVenda, FILE *ptrVendaProd, FILE *ptrProd)
{
	int linha = 7, linhaMaxima = 19, coluna = 40, posVenda, posProd, posForn, k=1, posCli;
	double totalItem=0;
	LimparSaida();	
	TpClientes Cliente;
	TpVendas Venda;
	TpVendasProd VendaProd;
	TpProdutos produto;
	char auxCPF[11];
	
	fseek(ptrVenda,-1*sizeof(Venda),2);
	fread(&Venda,sizeof(TpVendas),1,ptrVenda);
	
	gotoxy(55, linha);
	printf("SUPERMERCADO LIMA");
	linha+=2;
	gotoxy(coluna,linha);
	printf("Rua Sao Francisco de Assis, 123. Centro.");
	linha++;
	gotoxy(coluna,linha);
	printf("Sao Paulo - SP.");
	linha++;
	gotoxy(coluna,linha);
	printf("CNPJ: 12.641.071/0001-98");
	gotoxy(coluna+30,linha);
	printf("%d/%d/%d",Venda.DataVenda.Dia,Venda.DataVenda.Mes, Venda.DataVenda.Ano);
	linha++;
	gotoxy(coluna,linha);
	posCli = BuscaCPF(ptrCli,Venda.ClienteCPF);
	fseek(ptrCli,posCli,SEEK_SET);
	fread(&Cliente,sizeof(TpClientes),1,ptrCli);
	printf("Cliente: %s",Cliente.NomeCli); 
	linha++;
	gotoxy(coluna,linha);
	printf("------------------------------------------"); 
	linha++;
	gotoxy(coluna,linha);
	printf("PRODUTOS: ");
	linha+=2;
	gotoxy(coluna,linha);
	printf("COD");
	gotoxy(coluna+5,linha);
	printf("ITEM");
	gotoxy(coluna+11,linha);
	printf("DESCRICAO");
	gotoxy(coluna+36,linha);
	printf("VALOR");
	//imprimir produtos e formatar
	fseek(ptrVendaProd,0,0);
	while(fread(&VendaProd,sizeof(TpVendasProd),1,ptrVendaProd)==1)
	{
	    if (linha >= linhaMaxima)
		{
		// Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
			LimparMsg();
		    gotoxy(15, 26);
		    printf("Pressione qualquer tecla para continuar...");
		    Sleep(1500);
		    getch();
		    LimparSaida();
		    LimparMsg();
		    linha = 7;
		}
	    if (VendaProd.CodVenda == Venda.CodVenda)
	    {
	        linha++;
	        gotoxy(coluna, linha);
	        printf("%d", k);
	        k++;
	        
	        posProd = BuscaCodProd(ptrProd,VendaProd.CodProd);
	        posProd=posProd*sizeof(TpProdutos);
	        fseek(ptrProd,posProd,SEEK_SET);
			fread(&produto,sizeof(TpProdutos),1,ptrProd);
	                    
			gotoxy(coluna+5,linha);
			printf("%d",VendaProd.CodProd);
						
	        gotoxy(coluna+11, linha);
	        printf("%s", produto.Descr);
	
	        gotoxy(coluna+22, linha);
	        printf("%.2f",produto.Preco);
	                    
	        gotoxy(coluna+28, linha);
	        printf("X");
	                    
	        gotoxy(coluna+30, linha);
	        printf("%d",VendaProd.Qtde);
	                    
	
	        totalItem = VendaProd.Qtde * produto.Preco;
	        gotoxy(coluna+36, linha);
	        printf("R$%.2f", totalItem);

	        coluna = 40; // Reinicializa coluna para o próximo produto          
	    }
	}
	linha++;
	if (linha >= linhaMaxima)
	{
		LimparMsg();
		gotoxy(15, 26);
		printf("Pressione qualquer tecla para continuar...");
		Sleep(1500);
		getch();
		LimparSaida();
		LimparMsg();
		linha = 7;
	}
	gotoxy(coluna, linha);
	printf("------------------------------------------"); 
	linha++;
	if (linha >= linhaMaxima)
	{
		LimparMsg();
		gotoxy(15, 26);
		printf("Pressione qualquer tecla para continuar...");
		Sleep(1500);
		getch();
		LimparSaida();
		LimparMsg();
		linha = 7;
	}
	gotoxy(coluna, linha+1);
	printf("TOTAL: R$%.2f",Venda.TotVenda);
	linha++;
	if (linha >= linhaMaxima)
	{
		LimparMsg();
		gotoxy(15, 26);
		printf("Pressione qualquer tecla para continuar...");
		Sleep(1500);
		getch();
		LimparSaida();
		LimparMsg();
		linha = 7;
	}
	gotoxy(coluna, linha+2);
	printf("Agradecemos a preferencia ;)");
	Sleep(3000);
}


void FazerVenda()
{
    char op, auxCPF[12];
    FILE *PtrCli = fopen("clientes.dat","rb+");
    FILE *PtrVenda = fopen("vendas.dat","rb+");
    FILE *PtrVendaProd = fopen("vendaprod.dat","rb+");
    FILE *PtrProd = fopen("produtos.dat", "rb+");
    
    fseek(PtrVenda,0,0);
    fseek(PtrVendaProd,0,0);
    
    TpClientes Cliente;
    TpVendas Venda;
    TpVendasProd VendasProd;
    TpProdutos Prod;

    int posVenda, posProd, posCli, posVendaProd, aux, prodAdd;
    float totItem;
	
	fseek(PtrVenda,0,2);
	int tam = ftell(PtrVenda) / sizeof(TpVendas);
	if(PtrCli == NULL || PtrVenda == NULL || PtrVendaProd == NULL || PtrProd == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("Erro de abertura");
		Sleep(1500);
	}
	else
	{
		do
	    {
	        LimparSaida();
	        gotoxy(43, 8);
	        printf("### VENDA ###\n");
	        gotoxy(40, 10);
	        printf("CPF do cliente (APENAS NUMEROS): ");
	        fflush(stdin);
	        scanf("%s",&auxCPF);
	        if (validarCPF(auxCPF) == 0)
	        {
	            LimparMsg();
	            gotoxy(15, 26);
	            printf("CPF invalido");
	            Sleep(1500);
	            LimparMsg();
	        }
	        else
	        {
	        	auxCPF[12]='\0';
	            posCli = BuscaCPF(PtrCli, auxCPF);
	            if (posCli == -1)
	            {
	                LimparMsg();
	                gotoxy(15, 26);
	                printf("Cliente nao cadastrado");
	                Sleep(1500);
	                LimparMsg();
	            }
	            else
	            {
	            	Venda.TotVenda = 0;
	            	
					if(tam == 0)
					{
						Venda.CodVenda = 1;
					}
					else
					{
						Venda.CodVenda = RetornarCodigoVenda(PtrVenda);
					}
	            	
	                strncpy(Venda.ClienteCPF, auxCPF,12);
	                do
					{
						gotoxy(58, 11);
						printf("                 ");
					    gotoxy(40, 11);
					    printf("Data(dd mm aaaa): ");
					    scanf("%d%d%d", &Venda.DataVenda.Dia, &Venda.DataVenda.Mes, &Venda.DataVenda.Ano);
					
					    if (validarData(Venda.DataVenda) != 1) {
					        // Exibe uma mensagem de erro
					        LimparMsg();
					        gotoxy(15,26);
					        printf("Data invalida. Digite novamente.");
					        Sleep(1500);
					        LimparMsg();
					    }
					} while (validarData(Venda.DataVenda) != 1);
	
	                do
					{
						Venda.Status='A';
						totItem = 0;
						VendasProd.CodVenda = Venda.CodVenda;
					    gotoxy(59, 13);
					    printf("                    ");
					    gotoxy(40, 13);
					    printf("Codigo do produto: ");
					    scanf("%d", &aux);
						prodAdd = BuscarProdVenda(PtrVendaProd,Venda.CodVenda,aux);
						if(prodAdd != -1)
						{
							LimparMsg();
							gotoxy(15,26);
							printf("Produto ja adicionado. Deseja editar a quantidade? S/N");
							fflush(stdin);
							if(toupper(getch())=='S')
							{
								LimparMsg();
								gotoxy(15,26);
								LimparMsg();
								
								posProd=BuscaCodProd(PtrProd,aux);
								posProd=posProd*sizeof(TpProdutos);
								
								fseek(PtrProd,posProd,SEEK_SET);
								fread(&Prod,sizeof(TpProdutos),1,PtrProd);
								
								fseek(PtrVendaProd, prodAdd, SEEK_SET);
    							fread(&VendasProd, sizeof(TpVendasProd), 1, PtrVendaProd);
    							
    							totItem = VendasProd.Qtde * VendasProd.ValorUnitario;
								Venda.TotVenda -= totItem;
								
								Prod.Estoque += VendasProd.Qtde;
								fseek(PtrProd,posProd,SEEK_SET);
								fwrite(&Prod,sizeof(TpProdutos),1,PtrProd);
								
								gotoxy(40, 13);
					    		printf("Codigo do produto: %d",VendasProd.CodProd);
					    		gotoxy(40, 14);
					    		printf("Valor Unitario: %.2f",VendasProd.ValorUnitario);
					    		gotoxy(40, 15);
					    		printf("                ");
					    		gotoxy(40, 15);
					    		printf("Quantidade: ");
					    		scanf("%d",&VendasProd.Qtde);
					    		
					    	    while(VendasProd.Qtde < 0)
					    	    {
					    	    	// Exibe uma mensagem de erro e apaga a saída
						            LimparMsg();
						            gotoxy(15, 26);
						            printf("Quantidade invalida. Digite novamente.");
						            Sleep(1500);
						            gotoxy(40, 15);
					    			printf("Quantidade: ");
					    			scanf("%d",VendasProd.Qtde);
								}
						        
					    		while(VendasProd.Qtde > Prod.Estoque)
						        {
						            LimparMsg();
						            gotoxy(15, 26);
						            printf("Nao ha estoque suficiente. Estoque total: %d", Prod.Estoque);
						            Sleep(1500);
						            gotoxy(15, 27);
						            printf("Digite novamente a quantidade desejada. ");
						            Sleep(1500);
						            gotoxy(40, 15);
					    			printf("Quantidade: ");
					    			scanf("%d",VendasProd.Qtde);
						        }
						        
						        VendasProd.Status='A';
						      
						        fseek(PtrVendaProd,prodAdd,0);
						        fwrite(&VendasProd,sizeof(TpVendasProd),1,PtrVendaProd);
						        fseek(PtrVendaProd,0,2);
						        
						        Prod.Estoque -= VendasProd.Qtde;
						        totItem = VendasProd.Qtde * VendasProd.ValorUnitario;
								Venda.TotVenda += totItem;
								
								fseek(PtrProd,posProd,SEEK_SET);
								fwrite(&Prod,sizeof(TpProdutos),1,PtrProd);
								fseek(PtrProd,0,2);

						        LimparMsg();
						        gotoxy(15,26);
						        printf("Quantidade atualizada com sucesso.");
						        Sleep(1500);
							}
						}
						else
						{
							posProd = BuscaCodProd(PtrProd, aux);
						
						    if (posProd == -1)
						    {
						        LimparMsg();
						        gotoxy(15, 26);
						        printf("Produto nao cadastrado");
						        Sleep(1500);
						        LimparMsg();
						    }
						    else
						    {
						        // Copia o código do produto para a estrutura de venda do produto
						        posProd=posProd*sizeof(TpProdutos);
						    	fseek(PtrProd,posProd,SEEK_SET);
						    	fread(&Prod,sizeof(TpProdutos),1,PtrProd);
								VendasProd.CodProd = Prod.CodProd;
								VendasProd.ValorUnitario = Prod.Preco;
								gotoxy(40, 14);
								printf("                              ");
								gotoxy(40, 14);
								printf("Valor unitario: %.2f", VendasProd.ValorUnitario);
						
						        do
						        {
						        	LimparMsg();
						            gotoxy(50, 15);
						            printf("              ");
						            gotoxy(40, 15);
						            printf("Quantidade: ");
						            scanf("%d", &VendasProd.Qtde);
						
						            if (VendasProd.Qtde < 0)
						            {
						                // Exibe uma mensagem de erro e apaga a saída
						                LimparMsg();
						                gotoxy(15, 26);
						                printf("Quantidade invalida. Digite novamente.");
						                Sleep(1500);
						            }
						
						            if (VendasProd.Qtde > Prod.Estoque)
						            {
						                LimparMsg();
						                gotoxy(15, 26);
						                printf("Nao ha estoque suficiente. Estoque total: %d", Prod.Estoque);
						                Sleep(1500);
						                gotoxy(15, 27);
						                printf("Digite novamente a quantidade desejada. ");
						                Sleep(1500);
						            }
						        } while (VendasProd.Qtde > Prod.Estoque);
						        
						            
				                // Atualiza o estoque do produto
				                Prod.Estoque -= VendasProd.Qtde;
				
				                // Calcula o total da venda
				                
								totItem = VendasProd.Qtde * VendasProd.ValorUnitario;
								Venda.TotVenda += totItem;
								
				                LimparMsg();
				                gotoxy(15, 26);
				                printf("Produto adicionado a venda com sucesso");
				                Sleep(1500);
				                
						                
						        fwrite(&VendasProd,sizeof(TpVendasProd),1,PtrVendaProd);//Adicionar produto na venda
						        fseek(PtrProd,posProd,SEEK_SET);
						        fwrite(&Prod,sizeof(TpProdutos),1,PtrProd);//Atualizar estoque do produto
						    }
							
					}
					
					    LimparMsg();
					    gotoxy(15, 26);
					    printf("[ENTER] - Adicionar outro produto & [ESQ] - Concluir venda.");
					    op = toupper(getch());
					    
					} while (op != 27);
					fseek(PtrCli,posCli,SEEK_SET);
					fread(&Cliente,sizeof(Cliente),1,PtrCli);
					Cliente.ValorTotComprado += Venda.TotVenda;
					Cliente.QtdeCompras += 1;
					fwrite(&Venda,sizeof(TpVendas),1,PtrVenda);//Terminar a venda
					fseek(PtrCli,posCli,SEEK_SET);
					fwrite(&Cliente,sizeof(TpClientes),1,PtrCli);
					LimparMsg();
					gotoxy(15, 26);
					printf("Gerando cupom fiscal...");
					Sleep(2000);
					CupomFiscal(PtrCli, PtrVenda, PtrVendaProd, PtrProd);
				}
			}
			LimparMsg();
			gotoxy(15, 26);
			printf("[ENTER] - Fazer outra venda & [ESQ] - Concluir venda.");
			op = toupper(getch());
		}while(op != 27);
		fclose(PtrCli);
		fclose(PtrProd);
		fclose(PtrVendaProd);
		fclose(PtrVenda);
	}
}



void CadastroFornecedores(void) 
{
    FILE *PtrFornecedores = fopen("fornecedores.dat", "rb+"); // Abre o arquivo "Fornecedores.dat" para leitura e escrita em modo binário

    if (PtrFornecedores == NULL) // Verifica se houve erro ao abrir o arquivo
	{ 
        LimparMsg();
        gotoxy(15, 26);
		printf("Erro ao abrir o arquivo de fornecedores.");
    }
	else
	{
	
	    TpFornecedores Fornecedor; 
	    char op;
	    int pos,f;
	
	    LimparSaida();
	
	    do 
		{
	      	
	        gotoxy(43, 7);
	        printf("### CADASTRO DE FORNECEDORES ###\n");
	        gotoxy(40, 9);
	        printf("Codigo do fornecedor:");
	        scanf("%d", &Fornecedor.CodForn); 
	
	        pos = BuscaCod(Fornecedor.CodForn); // Verifica se o fornecedor já está cadastrado no arquivo
			  
	        if (pos != -1) 
			{ 
	            LimparMsg();
	            gotoxy(15, 26);
	            printf("Esse fornecedor ja foi cadastrado");
	            Sleep(1500);
	            LimparMsg();
	        } 
			else 
			{
	
	            gotoxy(40, 10);
	            printf("Nome do fornecedor: ");
	            fflush(stdin);
	            gets(Fornecedor.NomeForn); 
	
	            gotoxy(40, 11);
	            printf("Cidade do fornecedor: ");
	            gets(Fornecedor.CidadeForn); 
				Fornecedor.Status = 'A';
				
	           	fseek(PtrFornecedores,0, SEEK_END); 
	            fwrite(&Fornecedor,sizeof(TpFornecedores),1,PtrFornecedores); // Escreve o registro no arquivo de fornecedores
				
				//fseek(PtrFornecedores,0,2);
//				insercao(PtrFornecedores); 
				
				LimparMsg();
	            gotoxy(15, 26);
	            printf("Fornecedor cadastrado.");
	            Sleep(1500);
	            LimparMsg();
	        }
	
	        LimparSaida(); // Limpa a tela
	        gotoxy(15, 26);
	        printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
	        Sleep(1500);
	        op = toupper(getch());
	    } while (op != 27);
		SelecaoDireta(PtrFornecedores);
		//selection_sort_fornecedores(PtrFornecedores);
	    fclose(PtrFornecedores); 
	}
}


void CadastroProdutos() {
    FILE *Ptr = fopen("produtos.dat", "ab+"); // Abre o arquivo "Fornecedores.dat" para leitura e escrita em modo binário

    if (Ptr == NULL) { // Verifica se houve erro ao abrir o arquivo
        LimparMsg();
        gotoxy(15, 26);
		printf("Erro ao abrir o arquivo de produtos.");
    }

    TpProdutos R; 
    char op;
    int pos,pos2,qtde,codForn;

    do {
        gotoxy(43, 7);
        printf("### CADASTRO DE PRODUTOS ###\n");
        gotoxy(40, 9);
        printf("Codigo do produto:");
        scanf("%d", &R.CodProd);
        
        if(R.CodProd > 0)
		{
	        pos = BuscaCodProd(Ptr, R.CodProd);
	        if (pos != -1) {
	        	LimparMsg();
	            gotoxy(15,26);
	            printf("Esse produto ja foi cadastrado, deseja adicionar no estoque? (S/N): "); 
	            op = getch();
				if(toupper(op) == 'S')
				{
					gotoxy(40, 9);
					printf("Codigo do produto: %d", R.CodProd);
					gotoxy(40, 10);
					printf("Digite a quantidade: ");
					scanf("%d", &qtde);
					R.Estoque += qtde;
					
					pos2 = BuscaCodProd(Ptr, R.CodProd);
					fseek(Ptr, pos2*sizeof(TpProdutos),0);
					fwrite(&R,sizeof(TpProdutos),1,Ptr);
					
					LimparMsg();
					gotoxy(15,26);
	            	printf("Produto adicionado ao estoque com sucesso!"); 
	            	Sleep(1500);
	            	LimparMsg();
				}
	        } else {
	            fseek(Ptr,0,2); // fim do arquivo

	            gotoxy(40, 10);
	            printf("Descricao: ");
	            fflush(stdin);
	            gets(R.Descr);
				
				do
				{
				    gotoxy(40, 11);
				    printf("Data de Validade(dd mm aaaa): ");
				    scanf("%d%d%d", &R.DtValidade.Dia, &R.DtValidade.Mes, &R.DtValidade.Ano);
				
				    if (validarData(R.DtValidade) != 1) {
				        LimparMsg();
				        gotoxy(70, 11);
				        printf("           ");
						gotoxy(15,26);
				        printf("Data invalida. Digite novamente.");
				        Sleep(1500);
				        LimparMsg();
				    }
				} while (validarData(R.DtValidade) != 1);

	            do
	            {
	            	gotoxy(40, 12);
	            	printf("Estoque: ");
	            	scanf("%d", &R.Estoque);
	            	if(R.Estoque < 0)
	            	{
	            			LimparMsg();
	            			gotoxy(15,26);
							printf("Estoque invalido");
							Sleep(1500);
							LimparMsg();
	            	}
	            }while(R.Estoque < 0);
	            
	            do
	            {
	            	gotoxy(40, 13);
	            	printf("Preco: ");
	            	scanf("%f", &R.Preco);
	            	if(R.Preco < 0)
	            	{
	            			LimparMsg();
	            			gotoxy(15,26);
							printf("Preco invalido");
							Sleep(1500);
							LimparMsg();
	            	}
	            }while(R.Preco < 0);
	            
	            do
	            {
	            	gotoxy(40, 14);
	            	printf("Codigo do Fornecedor: ");
	            	scanf("%d", &codForn);
	            	pos=BuscaCod(codForn);
	            	if(pos == -1)
	            	{
	            			LimparMsg();
	            			gotoxy(15,26);
							printf("Fornecedor nao cadastrado.");
							//talvez um "deseja cadastrar um novo?"
							Sleep(1500);
							LimparMsg();
	            	}
	            	else
	            	{
	            		R.CodForn = codForn;
					}
	            }while(pos == -1);
	            
				R.Status = 'A';
				fseek(Ptr, 0, 2);
				fwrite(&R,sizeof(TpProdutos),1,Ptr);
				
				LimparMsg();
	            gotoxy(15,26);
	            printf("Produto cadastrado.");
	            Sleep(1500);
	            LimparMsg();
	        }
        }else
        {
        	LimparMsg();
			gotoxy(15,26);
			printf("Codigo invalido");
			Sleep(1500);
			LimparMsg();
        }

        LimparSaida();
        LimparMsg();
        gotoxy(15,26);
        printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
        Sleep(1500);
        op = toupper(getch());
    } while (op != 27);
    fclose(Ptr);
}


void AlteraFornecedores(){
	int pos = 0, aux, pos2;
	char op;
	TpFornecedores R;
	FILE *PtrFunc = fopen("fornecedores.dat","rb+");
	
	if (PtrFunc == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("\nErro de Abertura!\n");
	}
	else
		{
			do
			{
				LimparSaida();
				gotoxy(43,7);
				printf("### ALTERACAO DE FORNECEDORES ###\n");
				gotoxy(40,9);
				printf("Codigo:"); 
				scanf("%d", &R.CodForn);
				
				if (R.CodForn > 0)
				{
					pos = BuscaCod(R.CodForn);
					if(pos == -1)
					{
						LimparMsg();
						gotoxy(15,26);
						printf("Fornecedor nao cadastrado!");
						Sleep(1500);
						LimparMsg();
					}else{
						do
						{
							fseek(PtrFunc, pos,0); // Deslocando pos bytes a partir do início
							fread(&R,sizeof(TpFornecedores),1,PtrFunc);
							gotoxy(40,11);
							printf("[A] - Codigo: ");
							printf("%d", R.CodForn);
							gotoxy(40,12);
							printf("[B] - Nome: ");
							printf("%s",R.NomeForn);
							gotoxy(40, 13);
							printf("[C] - Cidade: "); 
							printf("%s", R.CidadeForn);
							gotoxy(43, 15);
							printf("[ENTER] - SALVAR");
							gotoxy(43, 16);
							printf("[ESQ] - VOLTAR");
							gotoxy(43, 17);
							printf("OPCAO: ");
							fflush(stdin);
							op = toupper(getch());
							switch(op)
							{
							
								case 'A':
								gotoxy(54,11);
								printf("                      ");
								gotoxy(54,11);
								fflush(stdin);
								scanf("%d", &aux);
								
								if(aux > 0)
								{
									pos2 = BuscaCod(aux);
									if(pos2 == -1) 
									{
										R.CodForn = aux;
										fseek(PtrFunc,pos,0);
										fwrite(&R,sizeof(TpFornecedores),1,PtrFunc);
										gotoxy(15,26);
										printf("Codigo editado!");
										Sleep(1500);
										LimparMsg();
									}
									else
									{
										gotoxy(15,26);
										printf("Codigo ja esta em uso!");
										Sleep(1500);
										LimparMsg();
									}			
								}
								else
								{
									gotoxy(15,26);
									printf("Codigo Invalido!");
									Sleep(1500);
									LimparMsg();
								}	
							
								break;
								
								case 'B':
								gotoxy(52,12);
								printf("                      ");
								gotoxy(52,12);
								fflush(stdin);
								gets(R.NomeForn);
								fseek(PtrFunc,pos,0);
								fwrite(&R,sizeof(TpFornecedores),1,PtrFunc);
								gotoxy(15,26);
								printf("NOME EDITADO!");
								Sleep(1500);
								LimparMsg();
								break;
								
								case 'C':
								gotoxy(54,13);
								printf("                      ");
								gotoxy(54,13);
								fflush(stdin);
								gets(R.CidadeForn);
								fseek(PtrFunc,pos,0);
								fwrite(&R,sizeof(TpFornecedores),1,PtrFunc);
								
								gotoxy(15,26);
								printf("CIDADE EDITADA!");
								Sleep(1500);
								LimparMsg();
								break;
							}
						}while(op!=27);
					}
				}
				else
				{
					gotoxy(15,26);
					printf("Codigo Invalido!");
					Sleep(1500);
					LimparMsg();
				}
			}while(op!=27);
			fclose(PtrFunc);
		}
}

void AlteraProdutos()
{
	int pos = 0,pos2,aux;
	char op;
	
	TpProdutos R;
	FILE *Ptr = fopen("produtos.dat","rb+");
	
	if (Ptr == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("\nErro de Abertura!\n");
	}
		
	else
	{
		do
		{
			LimparSaida();
			gotoxy(43,7);
			printf("### ALTERACAO DE PRODUTOS ###\n");
			gotoxy(40,9);
			printf("Codigo:"); 
			scanf("%d", &R.CodProd);
			
			if (R.CodProd > 0)
			{
				pos = BuscaCodProd(Ptr,R.CodProd);
				if(pos == -1)
				{
					LimparMsg();
					gotoxy(15,26);
					printf("Produto nao cadastrado!");
					Sleep(1500);
					LimparMsg();
					printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
        			Sleep(1500);
        			getch();
				}else{
					do
					{
						fseek(Ptr, pos*sizeof(TpProdutos),0); 
						fread(&R,sizeof(TpProdutos),1,Ptr);
						gotoxy(40,11);
						printf("[A] - Codigo: ");
						printf("%d", R.CodProd);
						gotoxy(40,12);
						printf("[B] - Codigo do Fornecedor: ");
						printf("%d",R.CodForn);
						gotoxy(40, 13);
						printf("[C] - Descricao: "); 
						printf("%s", R.Descr);
						gotoxy(40, 14);
						printf("[D] - Data de Validade: "); 
						printf("%d/%d/%d", R.DtValidade.Dia, R.DtValidade.Mes, R.DtValidade.Ano);
						gotoxy(40, 15);
						printf("[E] - Estoque: "); 
						printf("%d", R.Estoque);
						gotoxy(40, 16);
						printf("[F] - Preco: "); 
						printf("%.2f", R.Preco);
						gotoxy(43, 18);
						printf("[ENTER] - SALVAR");
						gotoxy(43, 19);
						printf("[ESQ] - VOLTAR");
						gotoxy(43, 20);
						printf("OPCAO: ");
						fflush(stdin);
						op = toupper(getch());
						switch(op)
						{
						
							case 'A':
							gotoxy(54,11);
							printf("                      ");
							gotoxy(54,11);
							scanf("%d", &R.CodProd);
							
							if(R.CodProd > 0)
							{
								pos = BuscaCodProd(Ptr,R.CodProd);
								if(pos == -1) 
								{
									fseek(Ptr,pos*sizeof(TpProdutos),0);
									fwrite(&R,sizeof(TpProdutos),1,Ptr);
									gotoxy(15,26);
									printf("Codigo editado!");
									Sleep(1500);
									LimparMsg();
								}
								else
								{
									gotoxy(15,26);
									printf("Codigo ja esta em uso!");
									Sleep(1500);
									LimparMsg();
								}			
							}
							else
							{
								gotoxy(15,26);
								printf("Codigo Invalido!");
								Sleep(1500);
								LimparMsg();
							}	
						
							break;
							
							case 'B':
							gotoxy(68,12);
							printf("          ");
							gotoxy(68,12);
							scanf("%d", &R.CodForn);
							
							if(R.CodForn > 0)
							{
								pos = BuscaCod(R.CodForn);
								if(pos2 == -1) 
								{
									gotoxy(15,26);
									printf("Fornecedor nao cadastrado!");
									Sleep(1500);
									LimparMsg();
								}
								else
								{
									fseek(Ptr,pos*sizeof(TpProdutos),0);
									fwrite(&R,sizeof(TpProdutos),1,Ptr);
									gotoxy(15,26);
									printf("Codigo do Fornecedor editado!");
									Sleep(1500);
									LimparMsg();
								}			
							}
							else
							{
								gotoxy(15,26);
								printf("Codigo Invalido!");
								Sleep(1500);
								LimparMsg();
							}
							break;
							
							case 'C':
							gotoxy(57,13);
							printf("                    ");
							gotoxy(57,13);
							fflush(stdin);
							gets(R.Descr);
							fseek(Ptr,pos*sizeof(TpProdutos),0);
							fwrite(&R,sizeof(TpProdutos),1,Ptr);
							LimparMsg();
							gotoxy(15,26);
							printf("Descrico editada!");
							Sleep(1500);
							LimparMsg();
							break;
							
							case 'D':
							do
							{
								gotoxy(64,14);
								printf("                         ");
							    gotoxy(64,14);
							    fflush(stdin);
								scanf("%d%d%d", &R.DtValidade.Dia, &R.DtValidade.Mes, &R.DtValidade.Ano);
							
							    if (validarData(R.DtValidade) != 1) {
							        // Exibe uma mensagem de erro e apaga a saída
							        LimparMsg();
							        gotoxy(15,26);
							        printf("Data invalida. Digite novamente.");
							        Sleep(1500);
							        LimparMsg();
							    }
							    
							}while (validarData(R.DtValidade) != 1);
							fseek(Ptr,pos*sizeof(TpProdutos),0);
							fwrite(&R,sizeof(TpProdutos),1,Ptr);
							LimparMsg();
							gotoxy(15,26);
							printf("Data editada!");
							break;
							
							case 'E':
						    do
							{
								gotoxy(55,15);
								printf("               ");
							    gotoxy(55,15);
								scanf("%d", &R.Estoque);
							
							    if (R.Estoque < 0) {
							        // Exibe uma mensagem de erro e apaga a saída
							        gotoxy(15,26);
							        printf("Estoque invalido. Digite novamente.");
							        Sleep(1500);
							        LimparMsg();
							    }
							} while (R.Estoque < 0);
							fseek(Ptr,pos*sizeof(TpProdutos),0);
							fwrite(&R,sizeof(TpProdutos),1,Ptr);
							LimparMsg();
							gotoxy(15,26);
							printf("Estoque editado!");
							break;
						    
						    case 'F':
							do
							{
								gotoxy(53,16);
								printf("               ");
							    gotoxy(53,16);
								scanf("%f", &R.Preco);
							
							    if (R.Preco < 0) {
							        // Exibe uma mensagem de erro e apaga a saída
							        gotoxy(15,26);
							        printf("Preco invalido. Digite novamente.");
							        Sleep(1500);
							        LimparMsg();
							    }
							} while (R.Preco < 0);
							fseek(Ptr,pos*sizeof(TpProdutos),0);
							fwrite(&R,sizeof(TpProdutos),1,Ptr);
							LimparMsg();
							gotoxy(15,26);
							printf("Preco editado!");
							break;
							
						}
					}while(op!=27);
				}
			}
			else
			{
				gotoxy(15,26);
				printf("Codigo Invalido!");
				Sleep(1500);
				LimparMsg();
			}
		}while(op!=27);
		fclose(Ptr);
	}	
}

void AlteraClientes(){
	int pos = 0;
	char op;
	
	TpClientes R;
	FILE *Ptr = fopen("clientes.dat","rb+");
	
	if (Ptr == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("\nErro de Abertura!\n");
	}
		
	else
	{
		do
		{
			LimparSaida();
			gotoxy(43,7);
			printf("### ALTERACAO DE CLIENTES ###\n");
			gotoxy(40,9);
			printf("CPF (APENAS NUMEROS):"); 
			fflush(stdin);
			gets(R.CPF);
			
			if (R.CPF > 0)
			{
				pos = BuscaCPF(Ptr, R.CPF);
				if(pos == -1)
				{
					gotoxy(15,26);
					printf("Cliente nao cadastrado!");
					Sleep(1500);
					LimparMsg();
				}else{
					do
					{
						fseek(Ptr, pos,0); 
						fread(&R,sizeof(TpClientes),1,Ptr);
						gotoxy(40,11);
						printf("[A] - CPF: ");
						printf("%s", R.CPF);
						gotoxy(40,12);
						printf("[B] - Nome: ");
						printf("%s",R.NomeCli);
						gotoxy(40, 14);
						printf("[ENTER] - SALVAR");
						gotoxy(40, 15);
						printf("[ESQ] - VOLTAR");
						gotoxy(40, 16);
						printf("OPCAO: ");
						fflush(stdin);
						op = toupper(getch());
						switch(op)
						{
						
							case 'A':
							gotoxy(51,11);
							printf("                      ");
							gotoxy(51,11);
							fflush(stdin);
							gets(R.CPF);
							
								if(validarCPF(R.CPF))
								{
									if(BuscaCPF(Ptr,R.CPF) == -1) 
									{
										fseek(Ptr,pos,0);
										fwrite(&R,sizeof(TpClientes),1,Ptr);
										gotoxy(15,26);
										printf("CPF EDITADO!");
										Sleep(1500);
										LimparMsg();
									}
									else
									{
										gotoxy(15,26);
										printf("CPF JA ESTA EM USO !");
										Sleep(1500);
										LimparMsg();
									}			
								}
								else
								{
									gotoxy(15,26);
									printf("CPF INVALIDO!");
									Sleep(1500);
									LimparMsg();
								}	
						
							break;
							
							case 'B':
							gotoxy(51,12);
							printf("                      ");
							gotoxy(51,12);
							fflush(stdin);
							gets(R.NomeCli);
							fseek(Ptr,pos,0);
							fwrite(&R,sizeof(TpClientes),1,Ptr);
							gotoxy(15,26);
							printf("NOME EDITADO!");
							Sleep(1500);
							LimparMsg();
							break;
						}
					}while(op!=27);
				}
			}
		}while(op!=27);
		fclose(Ptr);
	}
	
	
	
}

//void FazerVenda(TpVendas Venda[], int &TLV, TpClientes Cliente[], int TLC, TpVendasProd VendaProduto[], int &TLVP, TpProdutos Produto[], int TLP)
//{
//    char auxCPF[11], op;
//    int pos, aux, cont = 0, posProd, posCli;
//    float totItem;
//	
//    do
//    {
//        LimparSaida();
//        gotoxy(43, 8);
//        printf("### VENDA ###\n");
//        gotoxy(40, 10);
//        printf("CPF do cliente (APENAS NUMEROS): ");
//        fflush(stdin);
//        gets(auxCPF);

//        if (validarCPF(auxCPF) == 0)
//        {
//            LimparMsg();
//            gotoxy(15, 26);
//            printf("CPF invalido");
//            Sleep(1500);
//            LimparMsg();
//        }
//        else
//        {
//            posCli = BuscaCPF(auxCPF, Cliente, TLC);
//            if (posCli == -1)
//            {
//                LimparMsg();
//                gotoxy(15, 26);
//                printf("Cliente nao cadastrado");
//                Sleep(1500);
//                LimparMsg();
//            }
//            else
//            {
//            	Venda[TLV].TotVenda = 0;
//                Venda[TLV].CodVenda = TLV; // Define o código da nova venda
//                VendaProduto[TLVP].CodVenda = Venda[TLV].CodVenda;
//                strcpy(Venda[TLV].ClienteCPF, Cliente[posCli].CPF);
//                
//                do
//				{
//					gotoxy(58, 11);
//					printf("                 ");
//				    gotoxy(40, 11);
//				    printf("Data(dd mm aaaa): ");
//				    scanf("%d%d%d", &Venda[TLV].DataVenda.Dia, &Venda[TLV].DataVenda.Mes, &Venda[TLV].DataVenda.Ano);
//				
//				    if (validarData(Venda[TLV].DataVenda) != 1) {
//				        // Exibe uma mensagem de erro
//				        LimparMsg();
//				        gotoxy(15,26);
//				        printf("Data invalida. Digite novamente.");
//				        Sleep(1500);
//				        LimparMsg();
//				    }
//				} while (validarData(Venda[TLV].DataVenda) != 1);

//                do
//				{
//					totItem = 0;
//					VendaProduto[TLVP].CodVenda = Venda[TLV].CodVenda;
//				    gotoxy(59, 13);
//				    printf("                    ");
//				    gotoxy(40, 13);
//				    printf("Codigo do produto: ");
//				    scanf("%d", &aux);
//				
//				    posProd = BuscaCodProd(aux, Produto, TLP);
//				
//				    if (posProd == -1)
//				    {
//				        LimparMsg();
//				        gotoxy(15, 26);
//				        printf("Produto nao cadastrado");
//				        Sleep(1500);
//				        LimparMsg();
//				    }
//				    else
//				    {
//				        // Copia o código do produto para a estrutura de venda do produto
//						VendaProduto[TLVP].CodProd = Produto[posProd].CodProd;
//						VendaProduto[TLVP].ValorUnitario = Produto[posProd].Preco;
//						gotoxy(40, 14);
//						printf("                              ");
//						gotoxy(40, 14);
//						printf("Valor unitario: %.2f", VendaProduto[TLVP].ValorUnitario);
//				
//				        do
//				        {
//				        	LimparMsg();
//				            gotoxy(50, 15);
//				            printf("              ");
//				            gotoxy(40, 15);
//				            printf("Quantidade: ");
//				            scanf("%d", &VendaProduto[TLVP].Qtde);
//				
//				            if (VendaProduto[TLVP].Qtde < 0)
//				            {
//				                // Exibe uma mensagem de erro e apaga a saída
//				                LimparMsg();
//				                gotoxy(15, 26);
//				                printf("Quantidade invalida. Digite novamente.");
//				                Sleep(1500);
//				            }
//				
//				            if (VendaProduto[TLVP].Qtde > Produto[posProd].Estoque)
//				            {
//				                LimparMsg();
//				                gotoxy(15, 26);
//				                printf("Nao ha estoque suficiente. Estoque total: %d", Produto[posProd].Estoque);
//				                Sleep(1500);
//				                gotoxy(15, 27);
//				                printf("Digite novamente a quantidade desejada. ");
//				                Sleep(1500);
//				            }
//				        } while (VendaProduto[TLVP].Qtde > Produto[posProd].Estoque);
//				        
//				            
//		                // Atualiza o estoque do produto
//		                Produto[posProd].Estoque -= VendaProduto[TLVP].Qtde;
//		
//		                // Calcula o total da venda
//		                
//						totItem = VendaProduto[TLVP].Qtde * VendaProduto[TLVP].ValorUnitario;
//						Venda[TLV].TotVenda += totItem;
//						
//		                LimparMsg();
//		                gotoxy(15, 26);
//		                printf("Produto adicionado a venda com sucesso");
//		                Sleep(1500);
//				                
//				        TLVP++;
//				    }
//				
//				    LimparMsg();
//				    gotoxy(15, 26);
//				    printf("[ENTER] - Adicionar outro produto & [ESQ] - Concluir venda.");
//				    op = toupper(getch());
//				    
//				} while (op != 27);
//				Cliente[posCli].ValorTotComprado += Venda[TLV].TotVenda;
//				Cliente[posCli].QtdeCompras += 1;
//				TLV++;
//				LimparMsg();
//				gotoxy(15, 26);
//				printf("Gerando cupom fiscal...");
//				Sleep(2000);
//				CupomFiscal(Venda[TLV-1].CodVenda, Cliente, Venda, VendaProduto, Produto, TLC, TLV, TLVP, TLP);
//			}
//		}
//		LimparMsg();
//		gotoxy(15, 26);
//		printf("[ENTER] - Fazer outra venda & [ESQ] - Concluir venda.");
//		op = toupper(getch());
//	}while(op != 27);
//}


void AumentarPreco()
{
    int CodFornecedor,pos;
    float aumento, aux;
    int percentualAumento;

    TpFornecedores RForn;
    TpProdutos RProd;

    FILE *PtrProd = fopen("produtos.dat", "rb+");
    FILE *PtrForn = fopen("fornecedores.dat", "rb");

    LimparSaida();
    gotoxy(43, 8);
    textcolor(10);
    printf("### AUMENTO DE PRECO ###\n");
    textcolor(7);

    if (PtrProd == NULL || PtrForn == NULL)
    {
    	LimparMsg();
		gotoxy(15, 26);
		printf("Erro de abertura!");
        Sleep(1500);
        getch();
    }
    else
    {
    	do
	    {
	        fflush(stdin);
	        gotoxy(72, 10);
	        printf("    ");
	        gotoxy(40, 10);
	        printf("Percentual de aumento (inteiro): ");
	        scanf("%f", &aux);
	
	        percentualAumento = aux;
	
	        if (percentualAumento != aux)
	        {
	            LimparMsg();
	            gotoxy(15, 26);
	            printf("Por favor, digite um valor inteiro.");
	            Sleep(1500);
	            LimparMsg();
	        }
	
	    } while (percentualAumento != aux);
	
	
	    gotoxy(40, 11);
	    printf("Codigo do Fornecedor: ");
	    scanf("%d", &CodFornecedor);
	    
	    pos =  BuscaCod(CodFornecedor);
	    
	    if (pos == -1) { 
	            LimparMsg();
	            gotoxy(15, 26);
	            printf("Esse fornecedor ja foi cadastrado");
	            Sleep(1500);
	            LimparMsg();
		}
	
	    fseek(PtrProd, 0, SEEK_SET);
	
	    while (fread(&RProd, sizeof(TpProdutos), 1, PtrProd) == 1)
	    {
	        if (RProd.CodForn == CodFornecedor)
	        {
	            aumento = RProd.Preco * (percentualAumento / 100.0);
                RProd.Preco += aumento;

                fseek(PtrProd, -sizeof(TpProdutos), SEEK_CUR);
                fwrite(&RProd, sizeof(TpProdutos), 1, PtrProd);
                fseek(PtrProd, 0, SEEK_CUR); // Volta para a posição atual para evitar problemas de leitura
	
	            LimparMsg();
	            gotoxy(15, 26);
	            printf("Aumento realizado com sucesso.");
	            Sleep(1500);
	            LimparMsg();
	        }
	    }
	
	    fclose(PtrProd);
	    fclose(PtrForn);
	}   
}


void RelatorioClientes(void) {
    int linha = 7;
    int linhaMaxima = 19; // Limite superior da área de saída
    int coluna = 40;
    
    TpClientes R;
    LimparSaida();
    
    FILE *PtrCli = fopen("clientes.dat", "rb"); 
    
    if (PtrCli == NULL) {
        LimparMsg();
		gotoxy(15, 26);
		printf("Erro de abertura!");
        Sleep(1500);
        getch();
    } else {
        while (fread(&R, sizeof(TpClientes), 1, PtrCli) == 1) {
            if (linha >= linhaMaxima) {
                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
                gotoxy(15, 26);
                printf("Pressione qualquer tecla para continuar...");
                Sleep(1500);
                getch();
                LimparSaida();
                LimparMsg();
                linha = 7;
            }
            if(R.Status == 'A')
            {
            	gotoxy(coluna, linha);
	            printf("CPF: %s", R.CPF);
	            gotoxy(coluna, linha + 1);
	            printf("Nome: %s", R.NomeCli);
	            gotoxy(coluna, linha + 2);
	            printf("Qtde de compras: %d", R.QtdeCompras);
	            gotoxy(coluna, linha + 3);
	            printf("Valor total comprado: %.2f", R.ValorTotComprado);
	
	            linha += 5;
            }

            
        }
        fclose(PtrCli);
    }
    getch();
}


void RelatorioFornecedores() {
    int linha = 7;
    int linhaMaxima = 19; // Limite superior da área de saída
    int coluna = 40;
    
    TpFornecedores R;
    LimparSaida();
    
    FILE *PtrForn = fopen("fornecedores.dat","rb+"); 
    
    
    if(PtrForn == NULL){
		LimparMsg();
		gotoxy(15, 26);
		printf("Erro de abertura!");
        Sleep(1500);
        getch();
	}
	else
	{
		fread(&R, sizeof(TpFornecedores),1,PtrForn);
		while(!feof(PtrForn))
		{	
			if (linha >= linhaMaxima) {
                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
                gotoxy(15, 26);
                printf("Pressione qualquer tecla para continuar...");
                Sleep(1500);
                getch();
                LimparSaida();
                LimparMsg();
                linha = 7;
            }
            
            if(R.Status == 'A')
            {
            	gotoxy(coluna, linha);
	            printf("Codigo: %d", R.CodForn);
	            gotoxy(coluna, linha + 1);
	            printf("Nome: %s", R.NomeForn);
	            gotoxy(coluna, linha + 2);
	            printf("Cidade: %s", R.CidadeForn);
	
	            linha += 4; 
				
            }
            fread(&R, sizeof(TpFornecedores),1,PtrForn);

            
        }
		fclose(PtrForn);
	}
	getch();
}

void RelatorioProdutos() 
{
    int linha = 7;
    int linhaMaxima = 19; // Limite superior da área de saída
    int coluna = 40;
    int pos;
    
    TpFornecedores RF;
    TpProdutos R;
    LimparSaida();
    
    
    FILE *Ptr = fopen("produtos.dat", "rb"); 
    FILE *PtrForn = fopen("fornecedores.dat", "rb"); 

	
	
    if (Ptr == NULL || PtrForn == NULL) {
        LimparMsg();
		gotoxy(15, 26);
		printf("Erro de abertura!");
        Sleep(1500);
        getch();
    } else {
        while (fread(&R, sizeof(TpProdutos), 1, Ptr) == 1)
        {	
            if (linha >= linhaMaxima) {
                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
                gotoxy(15, 26);
                printf("Pressione qualquer tecla para continuar...");
                Sleep(1500);
                getch();
                LimparSaida();
                LimparMsg();
                linha = 7;
            }
			
			if(R.Status == 'A')
			{
				gotoxy(coluna, linha);
	            printf("Codigo: %d", R.CodProd);
	            gotoxy(coluna, linha + 1);
	            printf("Descricao: %s", R.Descr);
	            gotoxy(coluna, linha + 2);
	            printf("Data de Validade: %d/%d/%d", R.DtValidade.Dia, R.DtValidade.Mes, R.DtValidade.Ano);
	            gotoxy(coluna, linha + 3);
	            printf("Estoque: %d", R.Estoque);
	            gotoxy(coluna, linha + 4);
	            printf("Preco: %.2f", R.Preco);
	            gotoxy(coluna, linha + 5);
	            printf("Codigo do fornecedor: %d", R.CodForn);
	            gotoxy(coluna, linha + 6);
	            
	            pos = BuscaCod(R.CodForn);
	            fseek(PtrForn, pos, 0);
	            fread(&RF, sizeof(TpFornecedores), 1, PtrForn);
				
	            printf("Nome do fornecedor: %s", RF.NomeForn);
	
	            linha += 8;
			}
             
        }

        fclose(PtrForn);
        fclose(Ptr);
    }
    getch();
}


void RelatorioVendas()
{
    int linha = 7, pos, posForn;
    int linhaMaxima = 19; // Limite superior da área de saída
    int coluna = 40;
    float totalItem;
    double totalVenda = 0;
    
    TpFornecedores RForn;
    TpProdutos RProd;
    TpVendas RVendas;
    TpVendasProd RVendasProd;
    LimparSaida();
    
    FILE *PtrProd = fopen("produtos.dat", "rb"); 
    FILE *PtrForn = fopen("fornecedores.dat", "rb"); 
    FILE *PtrVenda = fopen("vendas.dat", "rb"); 
    FILE *PtrVendaProd = fopen("vendaprod.dat", "rb");

    if (PtrProd == NULL || PtrForn == NULL || PtrVenda == NULL || PtrVendaProd == NULL) {
        LimparMsg();
		gotoxy(15, 26);
		printf("Erro de abertura!");
        Sleep(1500);
        getch();
    } else {
    	if (fread(&RVendas, sizeof(TpVendas), 1, PtrVenda) != 1) {
            LimparMsg();
			gotoxy(15, 26);
			printf("Nenhuma venda cadastrada.");
			Sleep(1500);
            fclose(PtrForn);
            fclose(PtrProd);
            fclose(PtrVenda);
            fclose(PtrVendaProd);
            getch();
        }
        else
        {
        	fseek(PtrVenda, 0, SEEK_SET);
        	while (fread(&RVendas, sizeof(TpVendas), 1, PtrVenda) == 1)
	        {
	
	            if(RVendas.Status == 'A')
	            {
	                if (linha >= linhaMaxima) {
	                    // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
	                    gotoxy(15, 26);
	                    printf("Pressione qualquer tecla para continuar...");
	                    Sleep(1500);
	                    getch();
	                    LimparSaida();
	                    LimparMsg();
	                    linha = 7;
	                }
	
	                gotoxy(coluna, linha);
	                printf("Codigo da venda: %d", RVendas.CodVenda);
	                linha += 1; // Incrementa linha duas vezes
	                gotoxy(coluna, linha);
	                printf("Produtos:");
	                
	                fseek(PtrVendaProd, 0, SEEK_SET); // Reinicializa o ponteiro do arquivo de produtos de venda
	                
	                while (fread(&RVendasProd, sizeof(TpVendasProd), 1, PtrVendaProd) == 1)
	                {
	                    if(RVendas.CodVenda == RVendasProd.CodVenda)
	                    {
	                        linha += 1;
	                        if (linha >= linhaMaxima) {
	                            // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
	                            gotoxy(15, 26);
	                            printf("Pressione qualquer tecla para continuar...");
	                            Sleep(1500);
	                            getch();
	                            LimparSaida();
	                            LimparMsg();
	                            linha = 7;
	                        }
	                        gotoxy(coluna, linha);
	                        printf("%d", RVendasProd.CodProd);
	    
	                        pos = BuscaCodProd(PtrProd, RVendasProd.CodProd);
	                        fseek(PtrProd, pos * sizeof(TpProdutos), SEEK_SET);
	                        fread(&RProd, sizeof(TpProdutos), 1, PtrProd);
	    
	                        coluna += 10;
	                        gotoxy(coluna, linha);
	                        printf("%s", RProd.Descr);
	                        
	                        coluna += 9;
	                        gotoxy(coluna, linha);
	                        printf("%d", RVendasProd.Qtde);
	    
	                        totalItem = RVendasProd.Qtde * RProd.Preco;
	                        coluna += 6;
	                        gotoxy(coluna, linha);
	                        printf("R$%.2f", totalItem);
	    
	                        coluna += 10;
	                        posForn = BuscaCod(RProd.CodForn);
	                        fseek(PtrForn, pos*sizeof(TpFornecedores), SEEK_SET);
	                        fread(&RForn, sizeof(TpFornecedores), 1, PtrForn);
	                        
	                        gotoxy(coluna, linha);
	                        printf("%s", RForn.NomeForn);
	                        
	                        linha += 1; // Incrementa linha para o próximo produto
	                        coluna = 40; // Reinicializa coluna para o próximo produto
	                    }
	                }
	    
	                linha += 1;
	                coluna = 40;
	                gotoxy(coluna, linha);
	                printf("Total: R$%.2f", RVendas.TotVenda);
	    
	                linha += 1;
	                gotoxy(coluna, linha);
	                printf("............................................");
	                linha = linha + 2; // Ajuste o espaço entre cada venda.
	            }
	        }
	        fclose(PtrForn);
	        fclose(PtrProd);
	        fclose(PtrVenda);
	        fclose(PtrVendaProd);
	    }
    }
    getch();  
}





char Menu(void)
{
	char op;
	LimparMsg();
	LimparSaida();
	gotoxy(8,8);
	textcolor(10);
	printf("###  M E N U  ###");
	gotoxy(8,10);
	textcolor(7);
	printf("[A] Fazer cadastro");
	gotoxy(8,11);
	printf("[B] Fazer consulta");
    gotoxy(8,12);
	printf("[C] Fazer alteracao");
	gotoxy(8,13);
	printf("[D] Fazer exclusao logica");
	gotoxy(8,14);
	printf("[E] Fazer venda");
	gotoxy(8,15);
	printf("[F] Relatorios");
	gotoxy(8,16);
	printf("[G] Aumento de precos");
	gotoxy(8,17);
	printf("[H] Fazer exclusao fisica");
	gotoxy(8,18);
	printf("[ESC] Sair");
	gotoxy(8,20);
	printf("Opcao desejada: ");
	fflush(stdin);
	op = toupper(getch());
}



char MenuCadastro()
{
	LimparMenu();
	char opCadastro;
	LimparSaida();
	
	do
	{
		gotoxy(8,8);
		textcolor(10);
		printf("### CADASTRO ###");
		gotoxy(8,10);
		textcolor(7);
		printf("[A] Cadastrar cliente"); 
		gotoxy(8,11);
		printf("[B] Cadastrar fornecedor"); 
	    gotoxy(8,12);
		printf("[C] Cadastrar produto"); 
		gotoxy(8,13);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,15);
		printf("Opcao desejada: ");
		fflush(stdin);
		opCadastro = toupper(getch());
		switch(opCadastro)
			{
				case 'A': CadastroClientes();
						  break;
				case 'B': CadastroFornecedores();
					  break;
				case 'C': CadastroProdutos();
						  break;	
			}
	}while(opCadastro!=27);
}

char MenuConsulta()
{
	LimparMenu();
	LimparSaida();
	char opConsulta;
	do
	{
		gotoxy(8,8);
		textcolor(10);
		printf("### CONSULTA ###");
		gotoxy(8,10);
		textcolor(7);
		printf("[A] Consultar cliente"); 
		gotoxy(8,11);
		printf("[B] Consultar fornecedor"); 
	    gotoxy(8,12);
		printf("[C] Consultar produto"); 
		gotoxy(8,13);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,15);
		printf("Opcao desejada: ");
		fflush(stdin);
		opConsulta = toupper(getch());
		switch(opConsulta)
			{
				case 'A': ConsultaClientes();
						  break;
				case 'B': ConsultaFornecedores();
						  break;
				case 'C': ConsultaProdutos();
						  break;	
			}
	}while(opConsulta != 27);
}

char MenuAlteracao()
{
	LimparMenu();
	char opAlteracao;
	LimparSaida();
	
	do
	{
		gotoxy(8,8);
		textcolor(10);
		printf("### ALTERACAO ###");
		gotoxy(8,10);
		textcolor(7);
		printf("[A] Alterar cliente"); 
		gotoxy(8,11);
		printf("[B] Alterar fornecedor"); 
	    gotoxy(8,12);
		printf("[C] Alterar produto"); 
		gotoxy(8,13);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,15);
		printf("Opcao desejada: ");
		fflush(stdin);
		opAlteracao = toupper(getch());
		switch(opAlteracao)
			{
				case 'A': AlteraClientes();
						  break;
				case 'B': AlteraFornecedores();
						  break;
				case 'C': AlteraProdutos();
						  break;	
			}
	}while(opAlteracao!=27);
}

char MenuExclusaoLogica()
{
	LimparMenu();
	char opExclusao;
	LimparSaida();
	
	do
	{
		gotoxy(8,8);
		textcolor(10);
		printf("### EXCLUSAO LOGICA ###");
		gotoxy(8,10);
		textcolor(7);
		printf("[A] Excluir cliente"); 
		gotoxy(8,11);
		printf("[B] Excluir fornecedor"); 
	    gotoxy(8,12);
		printf("[C] Excluir produto"); 
		gotoxy(8,13);
		printf("[D] Excluir venda"); 
		gotoxy(8,14);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,16);
		printf("Opcao desejada: ");
		fflush(stdin);
		opExclusao = toupper(getch());
		switch(opExclusao)
			{
				case 'A': ExcluiLogClientes();
						  break;
				case 'B': ExcluiLogFornecedores();
						  break;
				case 'C': ExcluiLogProdutos();
						  break;
				case 'D': ExcluiVendas();
						  break;	
			}
	}while(opExclusao!=27);
}

char MenuExclusaoFisica()
{
	LimparMenu();
	char opExclusao;
	LimparSaida();
	
	do
	{
		gotoxy(8,8);
		textcolor(10);
		printf("### EXCLUSAO FISICA ###");
		gotoxy(8,10);
		textcolor(7);
		printf("[A] Excluir cliente"); 
		gotoxy(8,11);
		printf("[B] Excluir fornecedor"); 
	    gotoxy(8,12);
		printf("[C] Excluir produto"); 
		gotoxy(8,13);
		printf("[D] Excluir venda"); 
		gotoxy(8,14);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,16);
		printf("Opcao desejada: ");
		fflush(stdin);
		opExclusao = toupper(getch());
		switch(opExclusao)
			{
				case 'A': ExcluiFisClientes();
						  break;
				case 'B': ExcluiFisFornecedores();
						  break;
				case 'C': ExcluiFisProdutos();
						  break;
				case 'D': ExcluiFisVendas();
						  break;	
			}
	}while(opExclusao!=27);
}

char MenuRelatorios()
{
	LimparMenu();
	char opRelatorio;
	LimparSaida();
	
	do
	{
		gotoxy(8,8);
		textcolor(10);
		printf("### RELATORIO ###");
		gotoxy(8,10);
		textcolor(7);
		printf("[A] Relatorio clientes"); 
		gotoxy(8,11);
		printf("[B] Relatorio fornecedores"); 
	    gotoxy(8,12);
		printf("[C] Relatorio produtos"); 
		gotoxy(8,13);
		printf("[D] Relatorio de vendas"); 
		gotoxy(8,14);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,16);
		printf("Opcao desejada: ");
		fflush(stdin);
		opRelatorio = toupper(getch());
		switch(opRelatorio)
			{
				case 'A': RelatorioClientes();
						  break;
				case 'B': RelatorioFornecedores();
						  break;
				case 'C': RelatorioProdutos();
						  break;
				case 'D': RelatorioVendas();
						  break;	
			}
	}while(opRelatorio!=27);
};

void Moldura(int CI, int LI, int CF, int LF, int cor)
{
	int i;
	textcolor(cor);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	
	for(i=CI+1;i<CF;i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
		gotoxy(i,LF);
		printf("%c",205);
	}
	
	for(i=LI+1;i<LF;i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		gotoxy(CF,i);
		printf("%c",186);
	}
	
	textcolor(7);
};

void MoldPrincipal(void)
{
	clrscr();
	Moldura(1,1,90,30,5); // MOLDURA DE FORA
    Moldura(3,2,85,4,10); // MOLDURA TÍTULO
    
	
	gotoxy(19,3);
	printf("###  S I S T E M A   D E   V E N D A S  ###");
	Moldura(3,6,35,22,5); // MOLDURA MENU
	Moldura(36,6,88,22,5); // MOLDURA SAÍDA
	Moldura(3,24,88,28,10); // MOLDURA MENSAGEM
	
	gotoxy(5,26);
	printf("Mensagem: ");
};


int main(void)
{
	char opcao;
	
	LimparSaida();

		
	textbackground(0); // (preto) 0..7 (cinza)
	
	do
	{
		MoldPrincipal();
		opcao = Menu();
		switch(opcao)
		{
			case 'A': MenuCadastro();
					  break;
			case 'B': MenuConsulta();
					  break;
			case 'C': MenuAlteracao();
					  break;
			case 'D': MenuExclusaoLogica();
					  break;
			case 'E': FazerVenda();
					  break;
			case 'F': MenuRelatorios();
					  break;
			case 'G': AumentarPreco();
					  break;	
			case 'H': MenuExclusaoFisica();
					  break;			
		}
	}while(opcao!=27);
	
	gotoxy(15,30);
	return 0;
}


