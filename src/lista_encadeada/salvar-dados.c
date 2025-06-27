#include "salvar-dados.h"	
#include <stdio.h>
#include "../types/registro.type.h"

void salvar_dados(Registros *lista){
	FILE *pont_arq;
	Registros *atual = lista;
	int contador = 0;
	
	pont_arq = fopen("dados.txt", "w");
	
	if(pont_arq == NULL){
		printf("Erro na abertura do arquivo");
		return;	
	} 
	
	while(atual != NULL) {
		fprintf(pont_arq, "%s,%s,%s,%s,%s,%d,%s,%s,%s,%d\n", atual->registro.renamaut, atual->registro.fab, atual->registro.mod, atual->registro.cat, atual->registro.apl, atual->registro.ano, atual->registro.resp, atual->registro.cidade, atual->registro.uf, atual->registro.status);
		atual = atual -> next;
		contador ++;
	}
	
	printf("%d registros salvos com sucesso!", contador);
	
	fclose(pont_arq);
	
}
