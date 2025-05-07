#include "change-machine-status.h"

Registro *change_machine_status(Registro *registro, RegistroStatusEnum status)
{
  registro->status = status;

  return registro;
}