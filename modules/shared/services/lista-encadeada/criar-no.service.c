#include "criar-no.service.h"

ListaRegistro *criar_no_lista_registro_simples(Registro registro) {
    ListaRegistro *novoNo = (ListaRegistro *)malloc(sizeof(ListaRegistro));
    if (novoNo == NULL) {
        return NULL;
    }
    novoNo->registro = registro;
    novoNo->next = NULL;
    return novoNo;
}